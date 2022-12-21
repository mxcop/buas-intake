#include "entity.h"
#include "arena/arena.h"
#include "../game.h"

using Tmpl8::Game;

Entity::Entity(std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y)
{
	spr = sprite;
	enemies = Game::instance()->enemies;

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

void Entity::Hit(const u8 dmg, const u16 dx, const u16 dy)
{
	wasHit = true;
	hitpoints -= dmg;
}

bool Entity::Move(const i16 dx, const i16 dy)
{
	if (wasHit) {
		wasHit = false;
		return false;
	}

	bool moved = false;
	Enemy* enemy = enemies->Get(x + dx, y + dy);

	// Update the sprite facing direction:
	if (dx < 0) flip = true;
	if (dx > 0) flip = false;

	if (enemy != nullptr) {
		enemy->Hit(1, dx, dy);
		return false;
	}

	if (Game::instance()->tilemap->IsWalkable(x + dx, y + dy)) {
		x += dx; y += dy;
		ox += dx * -8;
		oy += dy * -8;
		return true;
	}

	return false;
}
