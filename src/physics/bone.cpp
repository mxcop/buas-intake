#include "bone.h"
#include <string>

Bone::Bone(float x, float y, float angle, float len, Bone* child)
{
	offset = float2(x, y);
	this->angle = angle;
	this->len = len;
	this->child = child;
}

void Bone::Draw(Tmpl8::Surface* screen, float2 p, float w_angle, bool origin)
{
    w_angle += angle;

    if (origin) {
        screen->Line(offset.x + p.x, offset.y + p.y, offset.x + p.x + cos(w_angle) * len, offset.y + p.y + sin(w_angle) * len, 0xffffff);
        if (child != nullptr) child->Draw(screen, float2(offset.x + p.x + cos(w_angle) * len, offset.y + p.y + sin(w_angle) * len), w_angle);
    }
    else {
        screen->Line(p.x, p.y, p.x + cos(w_angle) * len, p.y + sin(w_angle) * len, 0xffffff);
        if (child != nullptr) child->Draw(screen, float2(p.x + cos(w_angle) * len, p.y + sin(w_angle) * len), w_angle);
    }
}

float2 Bone::Update(float2 target)
{
    // Convert from parent to local coordinates.
    float2 local = (target - offset).rotate(-angle);

    float2 end;
    if (child != nullptr) {
        end = child->Update(local);
    }
    else {
        // Default endpoint for the last bone in the sequence.
        end = float2(len, 0);
    }

    // Point towards the endpoint.
    float deltaAngle = atan2(local.y, local.x) - atan2(end.y, end.x);
    angle += deltaAngle;

    // Convert back to parent coordinate space.
    return offset + end.rotate(angle);
}

Bone::~Bone()
{
    delete child;
}
