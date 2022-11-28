#include "player.h"
#include "../game.h"

void Player::Draw(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, pos.x * Tmpl8::TileSize, pos.y * Tmpl8::TileSize);
}

void Player::Move(Direction dir)
{
	switch (dir)
	{
	case Direction::UP:
		if (pos.y > 0) pos.y -= 1;
		break;
	case Direction::RIGHT:
		if (pos.x < Tmpl8::TilemapWidth - 1) pos.x += 1;
		break;
	case Direction::DOWN:
		if (pos.y < Tmpl8::TilemapHeight - 1) pos.y += 1;
		break;
	case Direction::LEFT:
		if (pos.x > 0) pos.x -= 1;
		break;
	}
}
