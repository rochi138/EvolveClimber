#pragma once

using namespace std;

namespace EC
{
    class Node {
		float x, y, vx, vy, prevX, prevY, pvx, pvy, m, f, value, valueToBe;
		int operation, axon1, axon2;
		bool safeInput;
		float pressure;
		Node(float tx, float ty, float tvx, float tvy, float tm, float tf, float val, int op, int a1, int a2) {
			prevX = x = tx;
			prevY = y = ty;
			pvx = vx = tvx;
			pvy = vy = tvy;
			m = tm;
			f = tf;
			value = valueToBe = val;
			operation = op;
			axon1 = a1;
			axon2 = a2;
			pressure = 0;
		}
	};
}
