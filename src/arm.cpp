#include "arm.h"

KinematicSegment::KinematicSegment(float x, float y, float len) {
	KinematicSegment::a = float2(x, y);
	KinematicSegment::len = len;
	KinematicSegment::angle = 0;

	KinematicSegment::b = float2(0, 0);
	CalculateB();
}

void KinematicSegment::CalculateB() {
	float dx = len * cos(angle);
	float dy = len * sin(angle);
	KinematicSegment::b.set(a.x + dx, a.y + dy);
}

void KinematicSegment::SetA(float2 a) {
	KinematicSegment::a = a;
}

void KinematicSegment::Follow(float2 t, bool move) {
	float2 dir = (t - a).normalized();
	angle = atan2(dir.y, dir.x);
	if (move) a = t - dir * len;
}

void KinematicSegment::Draw(Tmpl8::Surface* screen) {
	screen->Line(a.x, a.y, b.x, b.y, 0xffffff);
}

float2 KinematicSegment::GetJoint() {
	return a;
}
