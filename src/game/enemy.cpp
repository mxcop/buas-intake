#include "enemy.h"


void Enemy::Update(unsigned long frame)
{
	SetFrame(frame % 16 / 4);
}
