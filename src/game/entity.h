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
	Entity(std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y);

	std::tuple<u16, u16> GetPosition() const { return std::make_tuple(x, y); }

	/// <summary>
	/// Draw the entity to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen) const;

	/// <summary>
	/// Hit the entity.
	/// </summary>
	/// <param name="dx">Direction X axis</param>
	/// <param name="dy">Direction Y axis</param>
	virtual void Hit(const u8 dmg, const u16 dx, const u16 dy);

	/// <summary>
	/// Move the entity using a vector. (returns true if moved)
	/// </summary>
	virtual bool Move(const i16 dx, const i16 dy);

	virtual ~Entity() {}

private:
	std::shared_ptr<Tmpl8::Sprite> spr = nullptr;
	bool wasHit = false;

protected:
	std::shared_ptr<EnemyArena> enemies = nullptr;

	/// Set the animation frame for the entities sprite.
	void SetFrame(u32 frame) { spr->SetFrame(frame); }

	u16 hitpoints = 6;
	u16 x = 0, y = 0;
	f32 ox = 0, oy = 0;

	bool flip = false;
};