#pragma once

#include <memory>
#include "../engine/surface.h"
#include <types.h>
#include "collider.h"

using std::shared_ptr;
using Tmpl8::Sprite;

/* Size of a full health bar */
constexpr int FULL_HEALTH = 5;
/* Time of immunity after being hit in seconds */
constexpr float IMMUNITY_TIME = 1.5;

class Player : public Collidable {
public:
	Player(shared_ptr<Sprite> sprite, shared_ptr<Sprite> attack, float x, float y);

	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	void Move(const float dx, const float dy);

	void Attack();

	/// <summary>
	/// Draw the player to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen) const;

	/// <summary>
	/// Should be called every tick.
	/// </summary>
	void Tick(const u64 frame, const float deltatime);

	/// <summary>
	/// Called on collision.
	/// </summary>
	void onCollision(u16 emitter, CollisionTags tags) override;

	/// <returns>Get the current position of the player.</returns>
	float2 GetPosition() const;

	/// <returns>The number of hearts left.</returns>
	int GetHealth() const { return health; }

	bool shrink = false;

private:
	shared_ptr<Sprite> sprite = nullptr;
	shared_ptr<Sprite> attackSprite = nullptr;
	Collider* collider = nullptr;
	Collider* areaOfAttack = nullptr;
	float x, y;
	u16 w, h;
	int health = FULL_HEALTH;
	float immunityTimer = IMMUNITY_TIME;
	float attackTimer = 0;
};