#pragma once

#include "types.h"
#include "../surface.h"

class KinematicArm {

};

class KinematicSegment {
public:
	KinematicSegment(float x, float y, float len);

	void Follow(float2 t, bool move = false);
	void CalculateB();
	void SetA(float2 a);

	void Draw(Tmpl8::Surface* screen);
	float2 GetJoint();

private:
	float2 a;
	float len;
	float angle;
	float2 b;
};