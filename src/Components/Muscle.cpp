#include "../consts.h"
#include "../HelperFunctions.h"
#include "Muscle.h"
#include "Node.h"

#include <math.h>
#include <type_traits>

using namespace std;

namespace EC
{
	Muscle::Muscle(int tperiod, int tc1, int tc2, float tcontractTime, float textendTime, float tcontractLength, float textendLength, bool tcontracted, float trigidity) {
		period  = tperiod;
		c1 = tc1;
		c2 = tc2;
		contractTime = tcontractTime;
		extendTime = textendTime;
		contractLength = tcontractLength;
		extendLength = textendLength;
		contracted = tcontracted;
		rigidity = trigidity;
	}

	void Muscle::applyForce(vector<Node> &n, float target) {
		vector<Node>::iterator ni1 = n.begin() + c1;
		vector<Node>::iterator ni2 = n.begin() + c2;
		float distance = dist(ni1->getX(), ni1->getY(), ni2->getX(), ni2->getY());
		float angle = atan2(ni1->getY()-ni2->getY(), ni1->getX()-ni2->getX());
		float force = min(max(1.0f-(distance/target), -0.4f), 0.4f);
		ni1->incrementVx(cos(angle)*force*rigidity/ni1->getM());
		ni1->incrementVy(sin(angle)*force*rigidity/ni1->getM());
		ni2->incrementVx(-cos(angle)*force*rigidity/ni2->getM());
		ni2->incrementVy(-sin(angle)*force*rigidity/ni2->getM());
	}
	Muscle Muscle::copyMuscle() {
		Muscle newMuscle(period,c1,c2,contractTime,extendTime, contractLength,extendLength,contracted,rigidity);
		return newMuscle;
	}
	Muscle Muscle::modifyMuscle(float mutability, int nodeNum) {
		int newc1 = c1;
		int newc2 = c2;
		if(rFloat(0.0f,1.0f)<bigMutationChance*mutability){
			newc1 = rand() %nodeNum;
		}
		if(rFloat(0.0f,1.0f)<bigMutationChance*mutability){
			newc2 = rand() %nodeNum;
		}
		float newR = min(max(rigidity*(1.0f+r()*0.9f*mutability),0.01f),0.08f);
		float maxMuscleChange = 1.0f+0.025f/newR;
		float newCL = min(max(contractLength+r()*mutability,0.4f),2.0f);
		float newEL = min(max(extendLength+r()*mutability,0.4f),2.0f);
		float newCL2 = min(newCL,newEL);
		float newEL2 = min(max(newCL,newEL),newCL2*maxMuscleChange);

		bool isContractTimeChanged = rFloat(0.0f, 1.0f) >= 0.5f;
		float newCT = isContractTimeChanged ? contractTime : fmod(((contractTime-extendTime)*r()*mutability+contractTime+1.0f), 1.0f);
		float newET = isContractTimeChanged ? extendTime : fmod(((extendTime-contractTime)*r()*mutability+extendTime+1.0f), 1.0f);

		Muscle newMuscle(max(period+rInt(),0), newc1,newc2,newCT,newET,newCL2,newEL2,isItContracted(newCT,newET),newR);
		return newMuscle;
	}
}
