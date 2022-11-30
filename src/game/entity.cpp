#include "entity.h"
#include "../game.h"

Entity::Entity(Tmpl8::Sprite* sprite, u16 x, u16 y)
{
	spr = sprite;
	this->x = x;
	this->y = y;
	flip = false;
}

void Entity::Draw(Tmpl8::Surface* screen) const
{
	spr->Draw(screen, 
		x * Tmpl8::TileSize + roundf(ox),
		y * Tmpl8::TileSize + roundf(oy),
	true, flip);
}

/// <summary>
/// Check if a position on the tilemap is walkable.
/// </summary>
bool isWalkable(const Tilemap& map, const u16 x, const u16 y) {
	// Check if the position is walkable & within bounds.
	return map.Bounds(x, y)
		&& map.Get(x, y) <= 1;
}

bool Entity::Move(const Tilemap& map, const i16 dx, const i16 dy)
{
	bool moved = false;

	if (isWalkable(map, x + dx, y + dy)) {
		x += dx; y += dy;
		ox = dx * -8;
		oy = dy * -8;
		moved = true;
	}

	// Update the sprite facing direction:
	if (dx < 0) flip = true;
	if (dx > 0) flip = false;

	return moved;
}
