#include "player.h"
#include "../game.h"

void Player::Draw(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, pos.x * Tmpl8::TileSize, pos.y * Tmpl8::TileSize);
}

bool isOpen(const Tilemap* map, const int2 pos) {
	// Check if the position is walkable & within bounds.
	return map->Bounds(pos) && map->Get(pos.x, pos.y) == 0;
}

void Player::Move(const Tilemap* map, const Direction dir)
{
	switch (dir)
	{
	case Direction::UP:
		if (isOpen(map, pos + int2(0, -1))) pos.y -= 1;
		break;
	case Direction::RIGHT:
		if (isOpen(map, pos + int2(1, 0))) pos.x += 1;
		break;
	case Direction::DOWN:
		if (isOpen(map, pos + int2(0, 1))) pos.y += 1;
		break;
	case Direction::LEFT:
		if (isOpen(map, pos + int2(-1, 0))) pos.x -= 1;
		break;
	}
}
