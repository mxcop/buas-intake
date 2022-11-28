#pragma once
#include "../engine/surface.h"
#include "../utils/int2.hpp"

enum class Direction { UP, RIGHT, DOWN, LEFT };

class Player {
public:
	Player(int2 pos, Tmpl8::Sprite* sprite) : pos(pos), sprite(sprite) {}
	void Draw(Tmpl8::Surface* screen);
	void Move(Direction dir);

private:
	Tmpl8::Sprite* sprite;
	int2 pos = int2(0, 0);
};