#pragma once

#include "types.h"
#include "../surface.h"

//class KinematicArm {
//
//};

//class KinematicSegment {
//public:
//	KinematicSegment(float x, float y, float len);
//
//	void Follow(float2 t, bool move = false);
//	void CalculateB();
//	void SetA(float2 a);
//
//	void Draw(Tmpl8::Surface* screen);
//	float2 GetJoint();
//
//private:
//	float2 a;
//	float len;
//	float angle;
//	float2 b;
//};

class Bone {
public:
	Bone(float x, float y, float len, Bone* child = nullptr);

	void Draw(Tmpl8::Surface* screen, float2 p);
	float2 Update(float2 target);

	~Bone();

private:
	float2 a;
	float2 b;
	float len;
	float angle = 0;
	Bone* child = nullptr;
};