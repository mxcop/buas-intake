#pragma once

#include <memory>
#include <tuple>
#include "../engine/surface.h"
#include "../utils/types.h"
#include "../graphics/tilemap.h"

class EnemyArena;

/// <summary>
/// Base class for all entities in the game.
/// </summary>
class Entity {
public:
	Entity(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y);

	std::tuple<u16, u16> GetPosition() const { return std::make_tuple(x, y); }

	/// <summary>
	/// Draw the entity to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen) const;

	/// <summary>
	/// Move the entity using a vector. (returns true if moved)
	/// </summary>
	virtual bool Move(const Tilemap& map, const i16 dx, const i16 dy);

	virtual ~Entity() {}

private:
	std::shared_ptr<Tmpl8::Sprite> spr = nullptr;
	std::shared_ptr<EnemyArena> enemies = nullptr;

protected:
	/// Set the animation frame for the entities sprite.
	void SetFrame(u32 frame) { spr->SetFrame(frame); }

	u16 hitpoints = 6;
	u16 x = 0, y = 0;
	f32 ox = 0, oy = 0;

	bool flip = false;
};