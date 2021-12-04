#pragma once

#include <vector>
#include <iostream>

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

		void setVx(float f) { vx = f; if (isnan(vx))
		{    
			// std::cout << "setVx vx: " << vx << std::endl;
		}}
		void setVy(float f) { vy = f; }

		void incrementVx(float i) { vx += i; if (isnan(vx))
		{    
			// std::cout << "incrementVx vx: " << vx << std::endl;
			// std::cout << "incrementVx i: " << i << std::endl;
		}}
		void incrementVy(float i) { vy += i; }
		void incrementX(float f) { x += f; if (isnan(x))
		{    
			// std::cout << "incrementX x: " << x << std::endl;
		}}
		void incrementY(float f) { y += f; }
	};
}
