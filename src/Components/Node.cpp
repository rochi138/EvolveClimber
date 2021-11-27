#include "../consts.h"
#include "../HelperFunctions.h"
#include "Node.h"

using namespace std;

namespace EC
{
	Node::Node(float tx, float ty, float tvx, float tvy, float tm, float tf, float val, int op, int a1, int a2) {
		prevX = x = tx;
		prevY = y = ty;
		pvx = vx = tvx;
		pvy = vy = tvy;
		m = tm;
		f = tf;
		value = valueToBe = val;
		operation = op;
		axon1 = a1;
		axon2 = a2;
		pressure = 0;
	}
	void Node::applyForces() {
		vx *= airFriction;
		vy *= airFriction;
		y += vy;
		x += vx;
		float acc = dist(vx,vy,pvx,pvy);
		totalNodeNausea += acc*acc*nauseaUnit;
		pvx = vx;
		pvy = vy;		
	}
	void Node::applyGravity() {
		vy += gravity;
	}
	void Node::pressAgainstGround(float groundY){
		float dif = y-(groundY-m/2);
		pressure += dif*pressureUnit;
		y = (groundY-m/2);
		vy = 0;
		x -= vx*f;
		if (vx > 0) {
			vx -= f*dif*FRICTION;
			if (vx < 0) {
			vx = 0;
			}
		} else {
			vx += f*dif*FRICTION;
			if (vx > 0) {
			vx = 0;
			}
		}
	}
	void Node::hitWalls() {
		pressure = 0;
		float dif = y+m/2;
		if (dif >= 0 && haveGround) {
			pressAgainstGround(0);
		}
		if(y > prevY && hazelStairs >= 0){
			float bottomPointNow = y+m/2;
			float bottomPointPrev = prevY+m/2;
			int levelNow = (int)(ceil(bottomPointNow/hazelStairs));
			int levelPrev = (int)(ceil(bottomPointPrev/hazelStairs));
			if(levelNow > levelPrev){
			float groundLevel = levelPrev*hazelStairs;
			pressAgainstGround(groundLevel);
			}
		}
		// for (int i = 0; i < rects.size(); i++) {
		// 	Rectangle r = rects.get(i);
		// 	bool flip = false;
		// 	float px, py;
		// 	if (abs(x-(r.x1+r.x2)/2) <= (r.x2-r.x1+m)/2 && abs(y-(r.y1+r.y2)/2) <= (r.y2-r.y1+m)/2) {
		// 	if (x >= r.x1 && x < r.x2 && y >= r.y1 && y < r.y2) {
		// 		float d1 = x-r.x1;
		// 		float d2 = r.x2-x;
		// 		float d3 = y-r.y1;
		// 		float d4 = r.y2-y;
		// 		if (d1 < d2 && d1 < d3 && d1 < d4) {
		// 		px = r.x1;
		// 		py = y;
		// 		}else if (d2 < d3 && d2 < d4) {
		// 		px = r.x2;
		// 		py = y;
		// 		}else if (d3 < d4) {
		// 		px = x;
		// 		py = r.y1;
		// 		} else {
		// 		px = x;
		// 		py = r.y2;
		// 		}
		// 		flip = true;
		// 	} else {
		// 		if (x < r.x1) {
		// 		px = r.x1;
		// 		}else if (x < r.x2) {
		// 		px = x;
		// 		}else {
		// 		px = r.x2;
		// 		}
		// 		if (y < r.y1) {
		// 		py = r.y1;
		// 		}else if (y < r.y2) {
		// 		py = y;
		// 		}else {
		// 		py = r.y2;
		// 		}
		// 	}
		// 	float distance = dist(x, y, px, py);
		// 	float rad = m/2;
		// 	float wallAngle = atan2(py-y, px-x);
		// 	if (flip) {
		// 		wallAngle += PI;
		// 	}
		// 	if (distance < rad || flip) {
		// 		dif = rad-distance;
		// 		pressure += dif*pressureUnit;
		// 		float multi = rad/distance;
		// 		if (flip) {
		// 		multi = -multi;
		// 		}
		// 		x = (x-px)*multi+px;
		// 		y = (y-py)*multi+py;
		// 		float veloAngle = atan2(vy, vx);
		// 		float veloMag = dist(0, 0, vx, vy);
		// 		float relAngle = veloAngle-wallAngle;
		// 		float relY = sin(relAngle)*veloMag*dif*FRICTION;
		// 		vx = -sin(relAngle)*relY;
		// 		vy = cos(relAngle)*relY;
		// 	}
		// 	}
		// }
		prevY = y;
		prevX = x;
	}
	void Node::doMath(int i, vector<Node> n){
		float axonValue1 = n.at(axon1).getValue();
		float axonValue2 = n.at(axon2).getValue();

		switch (operation)
		{
			case 0: break; // constant
			case 1: valueToBe = simulationTimer/60.0; break; // time
			case 2: valueToBe = x*0.2; break; // x - coordinate
			case 3: valueToBe = -y*0.2; break; // y - coordinate
			case 4: valueToBe = axonValue1+axonValue2; break; // plus
			case 5: valueToBe = axonValue1-axonValue2; break; // minus
			case 6: valueToBe = axonValue1*axonValue2; break; // times
			case 7: valueToBe = axonValue1/axonValue2; break; // divide
			case 8: valueToBe = fmod(axonValue1, axonValue2); break; // modulus
			case 9: valueToBe = sin(axonValue1); break; // sin
			case 10: valueToBe = 1/(1+pow(2.71828182846,-axonValue1)); break; // sig
			case 11: valueToBe = pressure; break; // pressure
		}
	}
	void Node::realizeMathValues(int i){
		value = valueToBe;
	}
	Node Node::copyNode() {
		Node newNode(x, y, 0, 0, m, f, value, operation, axon1, axon2);
		return newNode;
	}
	Node Node::modifyNode(float mutability, int nodeNum) {
		float newX = x+r()*0.5*mutability;
		float newY = y+r()*0.5*mutability;
		float newM = m+r()*0.1*mutability;
		newM = min(max(newM, 0.3f), 0.5f);
		newM = 0.4;
		
		float newV = value*(1+r()*0.2*mutability);
		int newOperation = operation;
		int newAxon1 = axon1;
		int newAxon2 = axon2;
		if(rFloat(0,1)<bigMutationChance*mutability){
			newOperation = rand() %operationCount;
		}
		if(rFloat(0,1)<bigMutationChance*mutability){
			newAxon1 = rand() %nodeNum;
		}
		if(rFloat(0,1)<bigMutationChance*mutability){
			newAxon2 = rand() %nodeNum;
		}
		
		if(newOperation == 1){ // time
			newV = 0;
		}else if(newOperation == 2){ // x - coordinate
			newV = newX*0.2;
		}else if(newOperation == 3){ // y - coordinate
			newV = -newY*0.2;
		}
		
		Node newNode(newX, newY, 0, 0, newM, min(max(f+r()*0.1*mutability, 0.0), 1.0), newV, newOperation, newAxon1, newAxon2); //max(m+r()*0.1,0.2),min(max(f+r()*0.1,0),1)
		return newNode;
	}
}
