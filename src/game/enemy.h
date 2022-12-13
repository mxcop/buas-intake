#pragma once
#include <cstdint>
#include "entity.h"

class Enemy : public Entity {
public:
	Enemy(std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y);

	static Enemy& New(std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y);
	
	void Hit(const u8 dmg, const u16 dx, const u16 dy) override;

	/// <summary>
	/// Update the enemies animation.
	/// </summary>
	/// <param name="frame"></param>
	void Update(const unsigned long frame);

	/// <summary>
	/// Step forwards by one turn.
	/// </summary>
	void Step();

	u16 id = NULL;
};