#pragma once

#include <vector>
#include "../types.h"
#include "../../game/enemy.h"

class EnemyArena {
public:
	EnemyArena(u16 capacity = 32) { arena.reserve(capacity); }

	void Add(Enemy val);
	void Delete(const u16 id);

	/// Get an enemy by their id (nullptr if not found)
	Enemy* Get(const u16 id);
	/// Get an enemy by their position (nullptr if not found)
	Enemy* Get(const u8 x, const u8 y);

private:
	u16 idn = 0;
	std::vector<Enemy> arena;
};