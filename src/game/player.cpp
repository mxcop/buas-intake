#include "player.h"
#include <stdexcept>

/* Half Width  */ #define HALF_W static_cast<float>(w >> 1)
/* Half Height */ #define HALF_H static_cast<float>(h >> 1)

Player::Player(shared_ptr<Sprite> sprite, shared_ptr<Sprite> attack, float x, float y)
{
	if (sprite->Frames() != 4) {
		throw std::invalid_argument("player plane sprite should have 4 frames");
	}

	this->sprite = sprite;
	attackSprite = attack;
	this->x = x;
	this->y = y;
	w = sprite->GetWidth();
	h = sprite->GetHeight();

	/* The colliders aren't owned by the player so it's fine to be a raw pointer */
	collider = Collider::New(
		x - HALF_W + 4,
		y - HALF_H + 4,
		w - 8, h - 8, CollisionTags::Player,
		&Collidable::onCollision
	);
	areaOfAttack = Collider::New(
		x - HALF_W * 1.5,
		y - h,
		w * 1.5, HALF_H, CollisionTags::PlayerAtck,
		&Collidable::onCollision
	);
}

void Player::Move(float dx, float dy)
{
	if (shrink) {
		x += dx * 1.5;
		y += dy * 1.5;
	} else {
		x += dx;
		y += dy;
	}

	if (shrink) collider->SetPos(x - HALF_W * 0.4 + 3, y - HALF_H * 0.4 + 3);
	else collider->SetPos(x - HALF_W + 4, y - HALF_H + 4);

	areaOfAttack->SetPos(x - HALF_W * 1.5, y - h);
}

void Player::Attack()
{
	if (shrink == false) {
		attackTimer = 2.5;
	}
}

void Player::Draw(Tmpl8::Surface* screen) const
{
	/* Use the center position */
	mat3x3 translation = mat3x3::translation(
		x - HALF_W,
		y - HALF_H
	);

	/* Flash the player sprite when immune */
	if (immunityTimer <= 0 || static_cast<int>(ceilf(immunityTimer * 4)) % 2) {
		/* Scale the sprite if the player has shrunk */
		if (shrink) {
			translation = mat3x3::translation(
				x - HALF_W * 0.4,
				y - HALF_H * 0.4
			);
			translation = mat3x3::multiply(translation, mat3x3::scaled(0.4, 0.4));
		}

		sprite->DrawWithMatrix(screen, translation);
	}

	translation = mat3x3::translation(
		x - HALF_W - 4,
		y - HALF_H - 11
	);

	/* Draw the attack animation */
	if (attackTimer > 0) {
		attackSprite->SetFlags(Sprite::FLARE);
		attackSprite->DrawWithMatrix(screen, translation);
	}
}

void Player::Tick(const u64 frame, const float deltatime)
{
	sprite->SetFrame(frame % 8 / 2);

	/* Briefly enable the area of attack collider */
	areaOfAttack->enabled = attackTimer >= 2;
	/* Play the attack animation */
	attackSprite->SetFrame(3 - ceilf(attackTimer));

	if (shrink) collider->SetSize(3, 3);
	else collider->SetSize(w - 8, h - 8);

	collider->Tick(this);
	areaOfAttack->Tick(this);

	/* Decrement the timers */
	if (immunityTimer > 0) immunityTimer -= deltatime / 1000;
	if (attackTimer > 0) attackTimer -= deltatime / 100;
}

void Player::onCollision(u16 emitter, CollisionTags tags)
{
	/* Only listen for collisions to the player's hitbox */
	if (emitter != collider->id) return;

	/* If we're hit while not immune take damage */
	if (immunityTimer <= 0 && tags & CollisionTags::EnemyProj) {
		health--;
		immunityTimer = IMMUNITY_TIME;
	}
}

float2 Player::GetPosition() const
{
	return float2(x, y);
}
