#pragma once

using namespace std;

namespace EC
{
    class Muscle {
		int axon, c1, c2;
		float len;
		float rigidity;
		float previousTarget;
		Muscle(int taxon, int tc1, int tc2, float tlen, float trigidity) {
			axon  = taxon;
			previousTarget = len = tlen;
			c1 = tc1;
			c2 = tc2;
			rigidity = trigidity;
		}
	};
}
