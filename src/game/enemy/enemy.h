#pragma once
#include <types.h>
#include "../../engine/surface.h"
#include "../collider.h"

using Tmpl8::Surface;

/* Generic enemy class */
class Enemy : public Poolable, public Collidable {
public:
	Enemy(float x, float y, int w, int h, CollisionTags tags);

	/// <summary>
	/// Draw the enemy to the screen.
	/// </summary>
	virtual void Draw(Surface* screen) override = 0;

	/// <summary>
	/// Execute one tick of enemy behaviour.
	/// </summary>
	virtual void Tick(const u64 frame, const float deltatime) override = 0;

	/// <summary>
	/// Called on collision.
	/// </summary>
	virtual void onCollision(u16 emitter, CollisionTags tags) override = 0;

protected:
	Collider* collider = nullptr;
	float x, y;
};