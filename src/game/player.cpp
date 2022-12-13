#include "player.h"
#include "../game.h"

using Tmpl8::Game;

void Player::Update(const unsigned long frame) {
	(this->*anim)();
}

void Player::MoveWithAnimation(const i16 dx, const i16 dy) {
	if (Entity::Move(dx, dy)) {
		anim = &Player::anim_move;
	} else {
		ox = dx * 2;
		oy = dy * 2;
		anim = &Player::anim_bump;
	}
}

void Player::Move(const cdir dir) {
	// Don't move if we're still animating.
	if (ox != 0 || oy != 0) return;

	Game::instance()->enemies->StepAll();

	switch (dir)
	{
	case cdir::up: MoveWithAnimation   ( 0, -1); break;
	case cdir::right: MoveWithAnimation( 1,  0); break;
	case cdir::down: MoveWithAnimation ( 0,  1); break;
	case cdir::left: MoveWithAnimation (-1,  0); break;
	}
}

void Player::anim_move() {
	// Remove a bit of the offset each frame:
	// Idea was Sourced from the Pork-like game.
	if (ox > 0) ox--;
	if (ox < 0) ox++;
	if (oy > 0) oy--;
	if (oy < 0) oy++;
}

void Player::anim_bump() {
	// Remove a bit of the offset each frame:
	// Idea was Sourced from the Pork-like game.
	if (ox > 0) ox -= 0.25;
	if (ox < 0) ox += 0.25;
	if (oy > 0) oy -= 0.25;
	if (oy < 0) oy += 0.25;
}