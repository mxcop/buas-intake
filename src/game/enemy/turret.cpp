#include "turret.h"
#include "../player.h"

Turret::Turret(
	float x, float y, 
	shared_ptr<Sprite> sprite, 
	shared_ptr<Sprite> bullet_sprite,
	shared_ptr<Player> target,
	shared_ptr<Pool<Projectile>> projectiles
	) : Enemy(x, y)
{
	this->sprite = sprite;
	this->bullet_sprite = bullet_sprite;
	this->target = target;
	this->projectiles = projectiles;
	w = sprite->GetWidth();
	h = sprite->GetHeight();
}

void Turret::Draw(Tmpl8::Surface* screen) const
{
	mat3x3 rotation = mat3x3::rotation(angle);

	float half_w = static_cast<float>(w >> 1);
	float half_h = static_cast<float>(h >> 1);

	mat3x3 translation = mat3x3::translation(x + half_w, y + half_h - 2);
	mat3x3 center = mat3x3::translation(-half_w, -half_h + 2);

	mat3x3 mat_a = mat3x3::multiply(rotation, center);
	mat3x3 final = mat3x3::multiply(translation, mat_a);

	sprite->DrawWithMatrix(screen, final);
}

/* Half of PI or 90 Degrees */
constexpr float HALF_PI = 1.5707;

void Turret::Tick(u64 frame)
{
	float2 target_pos = target->GetPosition();
	float2 dir = (target_pos - float2(x, y)).normalized();

	angle = atan2f(-dir.y, dir.x) + HALF_PI;

	if (frame % 10 == 0) {
		float2 dir_right = float2(sinf(angle - HALF_PI / 4), cosf(angle - HALF_PI / 4));
		float2 dir_left = float2(sinf(angle + HALF_PI / 4), cosf(angle + HALF_PI / 4));

		projectiles->Add(Projectile(bullet_sprite, x + dir.x * 16, y + dir.y * 16, dir * 0.08, projectiles));
		projectiles->Add(Projectile(bullet_sprite, x + dir_left.x * 16, y + dir_left.y * 16, dir_left * 0.08, projectiles));
		projectiles->Add(Projectile(bullet_sprite, x + dir_right.x * 16, y + dir_right.y * 16, dir_right * 0.08, projectiles));
	}
}
