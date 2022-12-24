#include "projectile.h"

Projectile::Projectile(shared_ptr<Sprite> sprite, float x, float y, float2 dir, shared_ptr<Pool<Projectile>> arena)
{
	this->arena = arena;
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->dir = dir;
}

void Projectile::Tick(const u64 frame, const float deltatime)
{
	x += dir.x * deltatime;
	y += dir.y * deltatime;
}

/* Half of PI or 90 Degrees */
constexpr float HALF_PI = 1.5707;

void Projectile::Draw(Tmpl8::Surface* screen)
{
	/* Check if we're offscreen (cannot be done within tick because screen isn't available) */
	if (x < -5 || y < -5 || x > screen->GetWidth() + 5 || y > screen->GetHeight() + 5) {
		arena->Deactivate(id);
		return;
	}

	mat3x3 rotation = mat3x3::rotation(atan2f(-dir.y, dir.x) - HALF_PI);

	float half_w = static_cast<float>(sprite->GetWidth() >> 1);
	float half_h = static_cast<float>(sprite->GetHeight() >> 1);

	mat3x3 translation = mat3x3::translation(x + half_w, y + half_h - 2);
	mat3x3 center = mat3x3::translation(-half_w, -half_h + 2);

	mat3x3 mat_a = mat3x3::multiply(rotation, center);
	mat3x3 final = mat3x3::multiply(translation, mat_a);

	sprite->DrawWithMatrix(screen, final);
}
