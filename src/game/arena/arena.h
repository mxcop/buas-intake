#pragma once

#include <vector>
#include "types.h"
#include "../../engine/surface.h"
#include "../../graphics/tilemap.h"
#include "../enemy.h"

/// <summary>
/// An efficient way of storing a large amount of enemies.
/// </summary>
class EnemyArena {
public:
	EnemyArena(u16 capacity = 32) { arena.reserve(capacity); }

	/// Call the Update function on all enemies in the arena.
	void UpdateAll(u64 frame);
	/// Call the Draw function on all enemies in the arena.
	void DrawAll(Tmpl8::Surface* screen);

	/// Add an enemy to an arena.
	void Add(Enemy enemy);
	/// Delete an enemy from the arena.
	void Delete(const u16 id);

	/// Get an enemy by their id (nullptr if not found)
	Enemy* Get(const u16 id);
	/// Get an enemy by their position (nullptr if not found)
	Enemy* Get(const u8 x, const u8 y);

private:
	u16 idn = 0;
	std::vector<Enemy> arena;
};