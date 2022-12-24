#include "player.h"

Player::Player(shared_ptr<Sprite> sprite, float x, float y)
{
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	w = sprite->GetWidth();
	h = sprite->GetHeight();
}

void Player::Move(float dx, float dy)
{
	x += dx;
	y += dy;
}

void Player::Draw(Tmpl8::Surface* screen) const
{
	/* Use the center position */
	mat3x3 translation = mat3x3::translation(
		x - static_cast<float>(w >> 1), 
		y - static_cast<float>(h >> 1)
	);

	sprite->DrawWithMatrix(screen, translation);
}

void Player::Tick(const u64 frame)
{
	sprite->SetFrame(frame % 8 / 2);
}

float2 Player::GetPosition() const
{
	return float2(x, y);
}
