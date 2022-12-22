#pragma once
#include <types.h>
#include "../../engine/surface.h"

using Tmpl8::Surface;

/* Generic enemy class */
class Enemy {
public:
	Enemy(float x, float y);

	/// <summary>
	/// Draw the enemy to the screen.
	/// </summary>
	virtual void Draw(Surface* screen) const = 0;

	/// <summary>
	/// Execute one tick of enemy behaviour.
	/// </summary>
	/// <param name="frame"></param>
	virtual void Tick(const u64 frame) = 0;

protected:
	float x, y;
};