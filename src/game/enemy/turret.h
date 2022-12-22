#pragma once
#include <memory>
#include "./enemy.h"
#include "../../engine/surface.h"

using std::shared_ptr;
using Tmpl8::Sprite;

class Player;

/* 
	Enemy description :
	A stationary enemy that aims and fires at the player.
*/
class Turret : public Enemy {
public:
	Turret(float x, float y, shared_ptr<Sprite> sprite, shared_ptr<Player> target);

	void Draw(Tmpl8::Surface* screen) const override;
	void Tick(const u64 frame) override;

private:
	shared_ptr<Sprite> sprite = nullptr;
	shared_ptr<Player> target = nullptr;

	float angle = 0;
	u16 w, h;
};