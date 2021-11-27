#pragma once

#include <vector>

using namespace std;

namespace EC
{
    class Node {
		float x, y, vx, vy, prevX, prevY, pvx, pvy, m, f, value, valueToBe;
		int operation, axon1, axon2;
		bool safeInput;
		float pressure;

		public:
		Node(float tx, float ty, float tvx, float tvy, float tm, float tf, float val, int op, int a1, int a2);
		void applyForces();
		void applyGravity();
		void pressAgainstGround(float groundY);
		void hitWalls();
		void doMath(int i, vector<Node> n);
		void realizeMathValues(int i);
		Node copyNode();
		Node modifyNode(float mutability, int nodeNum);

		int getAxon1() { return axon1; }
		int getAxon2() { return axon2; }
		int getM() { return m; }
		int getOperation() { return operation; }
		bool getSafeInput() { return safeInput; }
		float getValue() { return value; }
		int getX() { return x; }
		int getY() { return y; }

		void setAxon1(int i) { axon1 = i; }
		void setAxon2(int i) { axon2 = i; }
		void setOperation(int i) { operation = i; }
		void setSafeInput(bool b) { safeInput = b; }
		void setValue(float f) { value = f; }
		void setVx(float f) { vx = f; }
		void setVy(float f) { vy = f; }

		void incrementVx(int i) { vx += i; }
		void incrementVy(int i) { vy += i; }
		void incrementX(float f) { x += f; }
		void incrementY(float f) { y += f; }
	};
}
