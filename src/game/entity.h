#pragma once

#include <cstdint>
#include "../engine/surface.h"
#include "../utils/types.h"
#include "../graphics/tilemap.h"

/// <summary>
/// Base class for all entities in the game.
/// </summary>
class Entity {
public:
	Entity(Tmpl8::Sprite* sprite, u16 x, u16 y);

	/// <summary>
	/// Draw the entity to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen) const;

	/// <summary>
	/// Move the entity using a vector. (returns true if moved)
	/// </summary>
	virtual bool Move(const Tilemap& map, const i16 dx, const i16 dy);

	virtual ~Entity() { /* base entity has no pointers to owned memory */ }

private:
	/// The sprite is not owned by the entity.
	Tmpl8::Sprite* spr = nullptr;

protected:
	u16 x = 0, y = 0;
	f32 ox = 0, oy = 0;

	bool flip = false;
};