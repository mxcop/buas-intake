#include "player.h"

Player::Player(std::shared_ptr<Tmpl8::Sprite> sprite, float x, float y)
{
	this->sprite = sprite;
	this->x = x;
	this->y = y;
}

void Player::Move(float dx, float dy)
{
	x += dx;
	y += dy;
}

void Player::Draw(Tmpl8::Surface* screen)
{
	mat3x3 translation = mat3x3::translation(x, y);

	sprite->DrawWithMatrix(screen, translation);
}
