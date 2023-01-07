#pragma once

#include <memory>
#include "./enemy.h"
#include "../../engine/surface.h"
#include "../pool/pool.h"
#include "../projectile.h"

using std::shared_ptr;
using Tmpl8::Sprite;

class Player;

/*
	Enemy description :
	A semi-mobile enemy that moves in a pattern while shooting forwards.
*/
class Plane : public Enemy {
public:
	Plane(float x, float y, shared_ptr<Sprite> sprite, shared_ptr<Sprite> bullet_sprite, shared_ptr<Player> target, shared_ptr<Pool<Projectile>> projectiles);

	void Draw(Tmpl8::Surface* screen) override;
	void Tick(const u64 frame, const float deltatime) override;
	void onCollision(u16 emitter, CollisionTags tags) override;

private:
	shared_ptr<Pool<Plane>> planes = nullptr;
	shared_ptr<Sprite> sprite = nullptr;
	shared_ptr<Sprite> bullet_sprite = nullptr;
	shared_ptr<Player> target = nullptr;
	shared_ptr<Pool<Projectile>> projectiles = nullptr;

	u16 w, h;
};