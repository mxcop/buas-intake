#pragma once

#include "types.h"
#include "../surface.h"

class Bone {
public:
	Bone(float x, float y, float len, Bone* child = nullptr);

	/// <summary>
	/// Draw the sequence of bones.
	/// </summary>
	/// <param name="screen">The screen surface.</param>
	/// <param name="p">The parent position (0,0 if origin)</param>
	/// <param name="w_angle">The world angle (all previous bone angles summed up)</param>
	/// <param name="origin">Whether this is the first bone in the sequence.</param>
	void Draw(Tmpl8::Surface* screen, float2 p, float w_angle = 0, bool origin = false);

	/// <summary>
	/// Recursively update angle of each bone in the sequence.
	/// </summary>
	/// <param name="target">The end effector.</param>
	float2 Update(float2 target);

	~Bone();

private:
	float2 offset;
	float len;
	float angle = 0;
	Bone* child = nullptr;
};