#include "enemy.h"

Enemy::Enemy(float x, float y, int w, int h, CollisionTags tags)
{
	this->x = x;
	this->y = y;

	/* The colliders aren't owned by the enemy so it's fine to be a raw pointer */
	collider = Collider::New(x, y, w, h, tags, &Collidable::onCollision);
}
