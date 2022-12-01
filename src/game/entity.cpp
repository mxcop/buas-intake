#include "entity.h"
#include "arena/arena.h"
#include "../game.h"

Entity::Entity(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y)
{
	spr = sprite;
	this->enemies = enemies;

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
	hitpoints -= dmg;
}

bool Entity::Move(const std::shared_ptr<Tilemap> map, const i16 dx, const i16 dy)
{
	bool moved = false;
	Enemy* enemy = enemies->Get(x + dx, y + dy);

	if (enemy != nullptr) {
		enemy->Hit(1, dx, dy);
	} else if (map->IsWalkable(x + dx, y + dy)) {
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
