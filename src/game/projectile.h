#pragma once
#include <float2.hpp>
#include "pool/pool.h"
#include "collider.h"
#include <memory>

using std::shared_ptr;
using std::unique_ptr;
using Tmpl8::Sprite;

class Projectile : public Poolable {
public:
	Projectile(shared_ptr<Sprite> sprite, float x, float y, float2 dir, shared_ptr<Pool<Projectile>> pool);

	void Tick(const u64 frame, const float deltatime) override;
	void Draw(Tmpl8::Surface* screen) override;

private:
	shared_ptr<Pool<Projectile>> pool = nullptr;
	shared_ptr<Sprite> sprite = nullptr;
	Collider* collider = nullptr;
	float x, y;
	float2 dir;
	bool deflected = false;
};