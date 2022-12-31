#include "player.h"

/* Half Width  */ #define HALF_W static_cast<float>(w >> 1)
/* Half Height */ #define HALF_H static_cast<float>(h >> 1)

Player::Player(shared_ptr<Sprite> sprite, float x, float y)
{
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	w = sprite->GetWidth();
	h = sprite->GetHeight();

	/* The collider isn't owned by the player so it's fine to be a raw pointer */
	collider = Collider::New(
		x - HALF_W + 4,
		y - HALF_H + 4,
		w - 8, h - 8, CollisionTags::Player
	);
	areaOfAttack = Collider::New(
		x - HALF_W,
		y - h,
		w, HALF_H, CollisionTags::PlayerAtck
	);
}

void Player::Move(float dx, float dy)
{
	x += dx;
	y += dy;

	collider->SetPos(x - HALF_W + 4, y - HALF_H + 4);
	areaOfAttack->SetPos(x - HALF_W, y - h);
}

void Player::Draw(Tmpl8::Surface* screen) const
{
	/* Use the center position */
	mat3x3 translation = mat3x3::translation(
		x - HALF_W,
		y - HALF_H
	);

	sprite->DrawWithMatrix(screen, translation);

	areaOfAttack->Debug(screen);
	collider->Debug(screen);
}

void Player::Tick(const u64 frame)
{
	sprite->SetFrame(frame % 8 / 2);
}

float2 Player::GetPosition() const
{
	return float2(x, y);
}
