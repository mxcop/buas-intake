#include "turret.h"
#include "../player.h"

Turret::Turret(
	float x, float y, 
	shared_ptr<Sprite> sprite, 
	shared_ptr<Player> target
	) : Enemy(x, y)
{
	this->sprite = sprite;
	this->target = target;
	w = sprite->GetWidth();
	h = sprite->GetHeight();
}

void Turret::Draw(Tmpl8::Surface* screen) const
{
	mat3x3 rotation = mat3x3::rotation(angle);

	float half_w = static_cast<float>(w >> 1);
	float half_h = static_cast<float>(h >> 1);

	mat3x3 translation = mat3x3::translation(x + half_w, y + half_h);
	mat3x3 center = mat3x3::translation(-half_w, -half_h);

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
}
