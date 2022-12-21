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
	mat3x3 final_mat = mat3x3();
	mat3x3 trans_mat = mat3x3();
	trans_mat.rotate(x / 10.0);
	final_mat.translate(x, y);
	final_mat.multiply(trans_mat);
	sprite->DrawWithMatrix(screen, final_mat);
}
