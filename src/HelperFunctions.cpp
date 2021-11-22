#include <stdlib.h> 

using namespace std;

namespace EC{
	float inter(int a, int b, float offset) {
		return float(a)+(float(b)-float(a))*offset;
	}
	int rInt() {
		return rand() %2 -1;
	}
	float rFloat(float min, float max) {
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return r*(max-min) + min;
	}
	float r() {
		return pow(rFloat(-1, 1), 19);
	}
}
