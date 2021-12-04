#include "../consts.h"
#include "../HelperFunctions.h"
#include "Node.h"

#include <iostream>

using namespace std;

namespace EC
{
	Node::Node(float tx, float ty, float tvx, float tvy, float tm, float tf) {
		x = tx;
		y = ty;
		vx = tvx;
		vy = tvy;
		m = tm;
		f = tf;
	}
	void Node::applyForces() {
		if (isnan(vx*airFriction))
		{    
			// std::cout << "applyForces vx: " << vx << std::endl;
		}
		vx *= airFriction;
		vy *= airFriction;
		y += vy;
		x += vx;				
	}
	void Node::applyGravity() {
		vy += gravity;
	}

	void Node::hitWalls() {
		float dif = y+m/2.0f;
		if (dif >= 0.0f && haveGround) {
			y = -m/2.0f;
			vy = 0.0f;
			x -= vx*f;	
			if (vx > 0.0f) {
				vx -= f*dif*FRICTION;
				if (vx < 0.0f) {
					vx = 0.0f;
				}
			} else {
				vx += f*dif*FRICTION;
				if (vx > 0.0f) {
					vx = 0.0f;
				}
			}
		}
		if (isnan(vx))
		{    
			std::cout << "hitWalls vx: " << vx << std::endl;
		}
	}
	Node Node::copyNode() {
		Node newNode(x, y, 0.0f, 0.0f, m, f);
		return newNode;
	}
	Node Node::modifyNode(float mutability, int nodeNum) {
		float newX = x+r()*0.5f*mutability;
		float newY = y+r()*0.5f*mutability;
		float newM = m+r()*0.1f*mutability;
		newM = min(max(newM, 0.3f), 0.5f);
		newM = 0.4f;
		
		Node newNode(newX, newY, 0.0f, 0.0f, newM, min(max(f+r()*0.1f*mutability, 0.0f), 1.0f)); //max(m+r()*0.1,0.2),min(max(f+r()*0.1,0),1)
		return newNode;
	}
}
