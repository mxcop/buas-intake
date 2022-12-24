#pragma once
#include <float2.hpp>
#include "pool/pool.h"
#include <memory>

using std::shared_ptr;
using Tmpl8::Sprite;

template<class T>
class Arena;

class Projectile : public Poolable {
public:
	Projectile(shared_ptr<Sprite> sprite, float x, float y, float2 dir, shared_ptr<Pool<Projectile>> arena);

	/// <summary>
	/// Should be called every tick.
	/// </summary>
	void Tick(const u64 frame, const float deltatime) override;

	void Draw(Tmpl8::Surface* screen) override;

private:
	shared_ptr<Pool<Projectile>> arena = nullptr;
	shared_ptr<Sprite> sprite = nullptr;
	float x, y;
	float2 dir;
};