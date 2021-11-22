#include "../consts.h"
#include "Muscle.h"
#include "Node.h"

using namespace std;

namespace EC
{
    class Muscle {
		void applyForce(int i, vector<Node> n) {
			float target = previousTarget;
			if(energyDirection == 1 || energy >= 0.0001){
			if(axon >= 0 && axon < n.size()){
				target = len*toMuscleUsable(n.get(axon).value);
			}else{
				target = len;
			}
			}
			Node ni1 = n.get(c1);
			Node ni2 = n.get(c2);
			float distance = dist(ni1.x, ni1.y, ni2.x, ni2.y);
			float angle = atan2(ni1.y-ni2.y, ni1.x-ni2.x);
			force = min(max(1-(distance/target), -0.4), 0.4);
			ni1.vx += cos(angle)*force*rigidity/ni1.m;
			ni1.vy += sin(angle)*force*rigidity/ni1.m;
			ni2.vx -= cos(angle)*force*rigidity/ni2.m;
			ni2.vy -= sin(angle)*force*rigidity/ni2.m;
			energy = max(energy+energyDirection*abs(previousTarget-target)*rigidity*energyUnit,0);
			previousTarget = target;
		}
		Muscle copyMuscle() {
			return new Muscle(axon, c1, c2, len, rigidity);
		}
		Muscle modifyMuscle(int nodeNum, float mutability) {
			int newc1 = c1;
			int newc2 = c2;
			int newAxon = axon;
			if(random(0,1)<bigMutationChance*mutability){
			newc1 = int(random(0,nodeNum));
			}
			if(random(0,1)<bigMutationChance*mutability){
			newc2 = int(random(0,nodeNum));
			}
			if(random(0,1)<bigMutationChance*mutability){
			newAxon = getNewMuscleAxon(nodeNum);
			}
			float newR = min(max(rigidity*(1+r()*0.9*mutability),0.01),0.08);
			float newLen = min(max(len+r()*mutability,0.4),1.25);

			return new Muscle(newAxon, newc1, newc2, newLen, newR);
		}
	};
}
