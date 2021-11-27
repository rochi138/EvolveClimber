#pragma once

namespace EC{
	float inter(int a, int b, float offset);
	int rInt();
	float rFloat(float min, float max);
	float r();
	int getNewMuscleAxon(int nodeNum);
	float dist(float x1, float y1, float x2 = 0.0f, float y2 = 0.0f);
	float toMuscleUsable(float f);
}
