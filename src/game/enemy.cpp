#include "enemy.h"
#include "arena/arena.h"
#include "../game.h"
#include <random>
#include <chrono>

using Tmpl8::Game;

Enemy::Enemy(std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y)
	: Entity(sprite, x, y) 
{
	hitpoints = 6;
}

Enemy& Enemy::New(std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y)
{
	Enemy enemy = Enemy(sprite, x, y);
	Game::instance()->enemies->Add(enemy);
	return enemy;
}

void Enemy::Hit(const u8 dmg, const u16 dx, const u16 dy)
{
	hitpoints -= dmg;

	Entity::Move(dx, dy);
	
	if (hitpoints <= 0) {
		Game::instance()->enemies->Delete(id);
	}
}

void Enemy::Update(const unsigned long frame)
{
	SetFrame(frame % 16 / 4);

	// Animate the movement:
	if (ox > 0) ox--;
	if (ox < 0) ox++;
	if (oy > 0) oy--;
	if (oy < 0) oy++;
}

void Enemy::Step()
{
	// Move randomly every turn.
	std::mt19937 mt{ static_cast<unsigned int>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };
	std::uniform_int_distribution<> move_dist{ -1, 1 };
	std::uniform_int_distribution<> move_axis{ 1, 2 };

	/* Diff Number */
	int dn = move_dist(mt);
	/* Diff Axis */
	int da = move_axis(mt);

	if (dn != 0) {
		Entity::Move(da == 1 ? dn : 0, da == 2 ? dn : 0);
	}
}
