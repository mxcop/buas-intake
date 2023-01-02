#include "collider.h"
#include "../game.h"
#include "projectile.h"

Collider::Collider(float x, float y, float w, float h, CollisionTags tags, void (Collidable::*onCollision)(u16, CollisionTags))
{
	pool = Tmpl8::Game::instance()->colliders;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->tags = tags;
	this->onCollision = onCollision;
}

void Collider::Debug(Tmpl8::Surface* screen) const
{
	if (enabled == false) {
		screen->Box(x, y, x + w, y + h, 0xff0000);
	} else if (IsColliding()) {
		screen->Box(x, y, x + w, y + h, 0x00ff00);
	} else {
		screen->Box(x, y, x + w, y + h, 0xffffff);
	}
}

Collider* Collider::New(float x, float y, float w, float h, CollisionTags tags, void (Collidable::*onCollision)(u16, CollisionTags))
{
	shared_ptr<Pool<Collider>> pool = Tmpl8::Game::instance()->colliders;

	u16 id = pool->Add(Collider(x, y, w, h, tags, onCollision));

	Collider* res = pool->Get(id);

	return res;
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

void Collider::Tick(Collidable* owner)
{
	auto& vec = pool->Vec();
	for (const Collider& e : vec) {
		if (e.id != id && e.active && e.enabled &&
			AABB(x, e.x, y, e.y, w, e.w, h, e.h)
			) {
			(*owner.*onCollision)(id, e.tags);
		}
	}
}

void Collider::SetPos(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

void Collider::SetSize(const float w, const float h)
{
	this->w = w;
	this->h = h;
}

bool Collider::IsColliding() const
{
	auto vec = pool->Vec();
	for (const Collider& e : vec) {
		if (e.id != id && e.active && e.enabled && AABB(x, e.x, y, e.y, w, e.w, h, e.h)) {
			return true;
		}
	}

	return false;
}

//bool Collider::IsCollidingWithMask(CollisionTags mask) const
//{
//	auto vec = pool->Vec();
//	for (const Collider& e : vec) {
//		if (e.id != id && e.active && 
//			e.tags & mask && 
//			AABB(x, e.x, y, e.y, w, e.w, h, e.h)
//		) {
//			return true;
//		}
//	}
//
//	return false;
//}

void Collider::Deactivate()
{
	pool->Deactivate(id);
}
