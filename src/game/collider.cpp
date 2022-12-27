#include "collider.h"
#include "../game.h"

Collider::Collider(float x, float y, float w, float h)
{
	pool = Tmpl8::Game::instance()->colliders;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Collider* Collider::New(float x, float y, float w, float h)
{
	shared_ptr<Pool<Collider>> pool = Tmpl8::Game::instance()->colliders;

	u16 id = pool->Add(Collider(x, y, w, h));

	return pool->Get(id);
}

void Collider::Draw(Tmpl8::Surface* screen)
{
	if (IsColliding()) {
		screen->Box(x, y, x + w, y + h, 0x00ff00);
	}
	else {
		screen->Box(x, y, x + w, y + h, 0xffffff);
	}
}

void Collider::SetPos(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

/// <summary>
/// Simple AABB Rect2Rect collision check.
/// </summary>
bool AABB(
	float x1, float x2,
	float y1, float y2,
	float w1, float w2,
	float h1, float h2
) {
	return x1 < x2 + w2 &&
		   x1 + w1 > x2 &&
		   y1 < y2 + h2 &&
		   y1 + h1 > y2;
}

bool Collider::IsColliding()
{
	auto vec = pool->Vec();
	for (const Collider& e : vec) {
		if (e.id != id && e.active && AABB(x, e.x, y, e.y, w, e.w, h, e.h)) {
			return true;
		}
	}

	return false;
}

void Collider::Deactivate()
{
	pool->Deactivate(id);
}
