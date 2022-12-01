#pragma once
#include "../engine/surface.h"
#include "../utils/int2.hpp"
#include "../graphics/tilemap.h"
#include "entity.h"

class Player : public Entity {
public:
	Player(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y) : Entity(enemies, sprite, x, y) { }

	/// <summary>
	/// Update the player's animation.
	/// </summary>
	/// <param name="frame"></param>
	void Update(unsigned long frame);

	/// <summary>
	/// Move the player one tile into the given direction.
	/// </summary>
	void Move(const std::shared_ptr<Tilemap> map, const cdir dir);

private:
	/// Abstraction for moving the player with an animation.
	void MoveWithAnimation(const std::shared_ptr<Tilemap> map, const i16 dx, const i16 dy);

	/// Animation function pointer.
	void (Player::*anim)() = &Player::anim_move;

	// Animation functions :
	void anim_move();
	void anim_bump();
};