#include "../consts.h"
#include "../HelperFunctions.h"
#include "Muscle.h"
#include "Node.h"

using namespace std;

namespace EC
{
	Muscle::Muscle(int taxon, int tc1, int tc2, float tlen, float trigidity) {
		axon  = taxon;
		previousTarget = len = tlen;
		c1 = tc1;
		c2 = tc2;
		rigidity = trigidity;
	}

	void Muscle::applyForce(vector<Node>* n) {
		float target = previousTarget;
		if(energyDirection == 1 || energy >= 0.0001){
			if(axon >= 0 && axon < n->size()){
				target = len*toMuscleUsable(n->at(axon).getValue());
			}else{
				target = len;
			}
		}
		Node ni1 = n->at(c1);
		Node ni2 = n->at(c2);
		float distance = dist(ni1.getX(), ni1.getY(), ni2.getX(), ni2.getY());
		float angle = atan2(ni1.getY()-ni2.getY(), ni1.getX()-ni2.getX());
		force = min(max(1-(distance/target), -0.4f), 0.4f);
		ni1.incrementVx(cos(angle)*force*rigidity/ni1.getM());
		ni1.incrementVy(sin(angle)*force*rigidity/ni1.getM());
		ni2.incrementVx(-cos(angle)*force*rigidity/ni2.getM());
		ni2.incrementVy(-sin(angle)*force*rigidity/ni2.getM());
		energy = max(energy+energyDirection*abs(previousTarget-target)*rigidity*energyUnit,0.0f);
		previousTarget = target;
	}
	Muscle Muscle::copyMuscle() {
		Muscle newMuscle(axon, c1, c2, len, rigidity);
		return newMuscle;
	}
	Muscle Muscle::modifyMuscle(float mutability, int nodeNum) {
		int newc1 = c1;
		int newc2 = c2;
		int newAxon = axon;
		if(rFloat(0,1)<bigMutationChance*mutability){
			newc1 = rand() %nodeNum;
		}
		if(rFloat(0,1)<bigMutationChance*mutability){
			newc2 = rand() %nodeNum;
		}
		if(rFloat(0,1)<bigMutationChance*mutability){
			newAxon = getNewMuscleAxon(nodeNum);
		}
		float newR = min(max(rigidity*(1+r()*0.9*mutability),0.01),0.08);
		float newLen = min(max(len+r()*mutability,0.4f),1.25f);

		Muscle newMuscle(newAxon, newc1, newc2, newLen, newR);
		return newMuscle;
	}
}
