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

bool Entity::Move(const Tilemap& map, const i16 dx, const i16 dy)
{
	bool moved = false;

	if (map.IsWalkable(x + dx, y + dy)) {
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