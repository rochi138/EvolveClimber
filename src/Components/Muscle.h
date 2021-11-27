#pragma once

#include "Node.h"

namespace EC
{
    class Muscle {
		int axon, c1, c2;
		float len;
		float rigidity;
		float previousTarget;

		public:
		Muscle(int taxon, int tc1, int tc2, float tlen, float trigidity);
		void applyForce(int i, vector<Node> n);
		Muscle copyMuscle();
		Muscle modifyMuscle(float mutability, int nodeNum);

		int getAxon() { return axon; };
		int getC1() { return c1; };
		int getC2() { return c2; };

		void setC1(int i) { c1 = i; };
		void setC2(int i) { c2 = i; };
		void setAxon(int i) { axon = i; };
	};
}
