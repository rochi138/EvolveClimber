#pragma once

#include "Node.h"

namespace EC
{
    class Muscle {
		int period, c1, c2;
		float contractTime, contractLength, extendTime, extendLength;
		float thruPeriod;
		bool contracted;
		float rigidity;

		public:
		Muscle(int tperiod, int tc1, int tc2, float tcontractTime,
  float textendTime, float tcontractLength, float textendLength, bool tcontracted, float trigidity);
		void applyForce(vector<Node> &n, float target);
		Muscle copyMuscle();
		Muscle modifyMuscle(float mutability, int nodeNum);

		// not 100% sure what this condition is for
		bool getCondition() { return (thruPeriod <= extendTime && extendTime <= contractTime) ||
       (contractTime <= thruPeriod && thruPeriod <= extendTime) ||
       (extendTime <= contractTime && contractTime <= thruPeriod); }
		int getC1() { return c1; }
		int getC2() { return c2; }
		bool getContracted() { return contracted; }
		float getContractLength() { return contractLength; }
		float getExtendLength() { return extendLength; }
		int getPeriod() { return period; }

		void setC1(int i) { c1 = i; }
		void setC2(int i) { c2 = i; }
		void setContracted(bool b) { contracted = b; }
		void setThruPeriod(float f) { thruPeriod = f; }
	};
}
