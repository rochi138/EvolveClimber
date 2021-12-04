#pragma once

namespace EC{
	float inter(int a, int b, float offset);
	int rInt(int min = -1, int max = 1);
	float rFloat(float min, float max);
	float r();
	int getNewMuscleAxon(int nodeNum);
	float dist(float x1, float y1, float x2 = 0.0f, float y2 = 0.0f);
	float toMuscleUsable(float f);
	bool isItContracted(float rtime1, float rtime2);
}
