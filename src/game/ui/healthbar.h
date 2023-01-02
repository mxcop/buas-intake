#pragma once
#include <memory>
#include "../player.h"

using std::shared_ptr;
using Tmpl8::Sprite;

class HealthBar {
public:
	HealthBar(shared_ptr<Sprite> heart, shared_ptr<Player> player);

	void Draw(Tmpl8::Surface* screen) const;

private:
	shared_ptr<Player> player;
	shared_ptr<Sprite> heart;
};