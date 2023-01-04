#include "plane.h"
#include <stdexcept>

Plane::Plane(
	float x, float y, 
	shared_ptr<Sprite> sprite, 
	shared_ptr<Sprite> bullet_sprite, 
	shared_ptr<Player> target, 
	shared_ptr<Pool<Projectile>> projectiles
) : Enemy(x, y, w, h, CollisionTags::Enemy) {
	if (sprite->Frames() != 4) {
		throw std::invalid_argument("enemy plane sprite should have 4 frames");
	}

	this->sprite = sprite;
	this->bullet_sprite = bullet_sprite;
	this->target = target;
	this->projectiles = projectiles;
	w = sprite->GetWidth();
	h = sprite->GetHeight();
	collider->SetSize(w, h);
}

constexpr float PI = 3.141592;

void Plane::Draw(Tmpl8::Surface* screen)
{
	if (y > screen->GetHeight() + h) {
		y = -h;
		return;
	}

	/* Rotate the plane 180 degrees */
	mat3x3 rotation = mat3x3::rotation(PI);

	float half_w = static_cast<float>(w >> 1);
	float half_h = static_cast<float>(h >> 1);

	mat3x3 translation = mat3x3::translation(x + half_w, y + half_h - 2);
	mat3x3 center = mat3x3::translation(-half_w, -half_h + 2);

	mat3x3 mat_a = mat3x3::multiply(rotation, center);
	mat3x3 final = mat3x3::multiply(translation, mat_a);

	sprite->DrawWithMatrix(screen, final);

	collider->Debug(screen);
}

void Plane::Tick(u64 frame, float deltatime)
{
	sprite->SetFrame(frame % 8 / 2);

	y += deltatime / 50;
	collider->SetPos(x, y - 4);

	if (frame % 100 == 0) {
		projectiles->Add(Projectile(bullet_sprite, x + static_cast<float>(w >> 1) - 3, y + static_cast<float>(h >> 1), float2(0, 0.08), projectiles));
	}

	collider->Tick(this);
}

void Plane::onCollision(u16 emitter, CollisionTags tags)
{
	if (tags & CollisionTags::PlayerProj) {
		printf("enemy plane got hit!\n");
	}
}
