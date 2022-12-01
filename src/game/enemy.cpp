#include "enemy.h"
#include "arena/arena.h"
#include "../game.h"

Enemy::Enemy(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y)
	: Entity(enemies, sprite, x, y) 
{
	hitpoints = 6;
}

Enemy& Enemy::New(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y)
{
	Enemy enemy = Enemy(enemies, sprite, x, y);
	enemies->Add(enemy);
	return enemy;
}

void Enemy::Hit(const u8 dmg, const u16 dx, const u16 dy)
{
	hitpoints -= dmg;

	Entity::Move(dx, dy);
	
	if (hitpoints <= 0) {
		enemies->Delete(id);
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