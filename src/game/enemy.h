#pragma once
#include <cstdint>
#include "entity.h"

class Enemy : public Entity {
public:
	Enemy(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y);

	static Enemy& New(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y);

	/// <summary>
	/// Update the enemies animation.
	/// </summary>
	/// <param name="frame"></param>
	void Update(unsigned long frame);

	u16 id = NULL;
};