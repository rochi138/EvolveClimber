#pragma once

#include <vector>

using namespace std;

namespace EC
{
    class Node {
		float x, y, vx, vy, m, f;

		public:
		Node(float tx, float ty, float tvx, float tvy, float tm, float tf);
		void applyForces();
		void applyGravity();
		void hitWalls();
		Node copyNode();
		Node modifyNode(float mutability, int nodeNum);

		float getM() { return m; }
		float getX() { return x; }
		float getY() { return y; }

		void setVx(float f) { vx = f; }
		void setVy(float f) { vy = f; }

		void incrementVx(float i) { vx += i; }
		void incrementVy(float i) { vy += i; }
		void incrementX(float f) { x += f; }
		void incrementY(float f) { y += f; }
	};
}
