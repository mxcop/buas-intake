#include "arm.h"
#include <string>

Bone::Bone(float x, float y, float len, Bone* child)
{
	a = float2(x, y);
	b = float2(0, 0);
	angle = 0;
	this->len = len;
	this->child = child;
}

void Bone::Draw(Tmpl8::Surface* screen, float2 p)
{
	screen->Line(a.x + p.x, a.y + p.y, a.x + p.x + cos(angle) * len, a.y + p.y + sin(angle) * len, 0xffffff);
    if (child != nullptr) child->Draw(screen, float2(a.x + p.x + cos(angle) * len, a.y + p.y + sin(angle) * len));
}

float2 RotatePoint(float2 p, float angle) {
    return float2(
        p.x * cos(angle) - p.y * sin(angle),
        p.x * sin(angle) + p.y * cos(angle)
    );
}

float2 Bone::Update(float2 target)
{
    // Convert from parent to local coordinates.
    float2 local = RotatePoint(target - a, -angle);

    if (child != nullptr) {
        b = child->Update(local);
    }
    else {
        // Edge case: The end point is the end of the current bone.
        b = float2(len, 0);
    }

    // Point towards the endpoint.
    float deltaAngle = atan2(local.y, local.x) - atan2(b.y, b.x);
    angle += deltaAngle;

    // Convert back to parent coordinate space.
    return a + RotatePoint(b, angle);
}

Bone::~Bone()
{
    delete child;
}
