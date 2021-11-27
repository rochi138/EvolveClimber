#include <stdlib.h> 
#include "HelperFunctions.h"

using namespace std;

namespace EC{
	float inter(int a, int b, float offset) {
		return float(a)+(float(b)-float(a))*offset;
	}
	int rInt(int min, int max) {
		return rand() %max + min;
	}
	float rFloat(float min, float max) {
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return r*(max-min) + min;
	}
	float r() {
		return pow(rFloat(-1, 1), 19);
	}
	int getNewMuscleAxon(int nodeNum){
		if(rFloat(0,1) < 0.5){
			return rand() %nodeNum;
		}else{
			return -1;
		}
	}
	float dist(float x1, float y1, float x2, float y2)
	{
		return sqrt( pow(x1-x2, 2.0) + pow(y1-y2, 2.0) );
	}
	float toMuscleUsable(float f){
		return fminf(fmaxf(f,0.5f),1.5f);
	}
}
