#pragma once
#include <cstdint>
#include "entity.h"

class Enemy : public Entity {
public:
	Enemy(Tmpl8::Sprite* sprite, u16 x, u16 y, u16 id)
		: Entity(sprite, x, y) {
		hitpoints = 2; this->id = id;
	}

	/// <summary>
	/// Update the enemies animation.
	/// </summary>
	/// <param name="frame"></param>
	void Update(unsigned long frame);

	u16 id = NULL;
};