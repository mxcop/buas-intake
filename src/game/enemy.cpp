#include "enemy.h"
#include "arena/arena.h"

Enemy::Enemy(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y)
	: Entity(enemies, sprite, x, y) 
{
	hitpoints = 2;
}

Enemy& Enemy::New(std::shared_ptr<EnemyArena> enemies, std::shared_ptr<Tmpl8::Sprite> sprite, u16 x, u16 y)
{
	Enemy enemy = Enemy(enemies, sprite, x, y);
	enemies->Add(enemy);
	return enemy;
}

void Enemy::Hit(const u8 dmg)
{
	Entity::Hit(dmg);

	if (hitpoints <= 0) {
		enemies->Delete(id);
	}
}

void Enemy::Update(unsigned long frame)
{
	SetFrame(frame % 16 / 4);
}
