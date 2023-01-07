#pragma once
#include "pool/pool.h"
#include <memory>

using std::shared_ptr;
using std::unique_ptr;

enum class CollisionTags
{
	None       = 0b00000000,
	/* Player Tag */
	Player     = 0b00000001,
	/* Enemy Tag */
	Enemy      = 0b00000010,
	/* Enemy Projectile Tag */
	EnemyProj  = 0b00000100,
	/* Player Bounced Projectile Tag */
	PlayerProj = 0b00001000,
	/* Player Attack Tag */
	PlayerAtck = 0b00010000,
};

inline CollisionTags operator|(CollisionTags a, CollisionTags b)
{
	return static_cast<CollisionTags>(static_cast<int>(a) | static_cast<int>(b));
}

inline u8 operator&(CollisionTags a, CollisionTags b)
{
	return static_cast<u8>(static_cast<int>(a) & static_cast<int>(b));
}

/// <summary>
/// Abstract class for a collidable object
/// </summary>
class Collidable {
public:
	virtual void onCollision(u16 emitter, CollisionTags tags) = 0;
};

/// <summary>
/// Rectangle Collider
/// </summary>
class Collider : public Poolable {
public:
	Collider(float x, float y, float w, float h, CollisionTags tags, void (Collidable::*onCollision)(u16, CollisionTags));

	void Tick(const u64 frame, const float deltatime) override { /* Colliders don't tick (unreachable) */ }
	void Draw(Tmpl8::Surface* screen) override { /* Colliders are not visible (unreachable) */ }

	/// <summary>
	/// Used for debbuging, will draw the bounds of the collider.
	/// And it will change color if it's colliding.
	/// </summary>
	void Debug(Tmpl8::Surface* screen) const;

	/// <summary>
	/// Static function for creating a new collider.
	/// </summary>
	/// <returns>A raw pointer to the collider. (because I'm uncertain about smart pointer behaviour)</returns>
	static Collider* New(float x, float y, float w, float h, CollisionTags tags, void (Collidable::*onCollision)(u16, CollisionTags));
	static Collider* New(Collider collider);

	/// <summary>
	/// Perform collision checks.
	/// </summary>
	void Tick(Collidable* owner);

	/// <summary>
	/// Set the position of the collider.
	/// </summary>
	void SetPos(const float x, const float y);

	/// <summary>
	/// Set the size of the collider.
	/// </summary>
	void SetSize(const float w, const float h);

	/// <returns>If this collider is currently intersecting with another collider.</returns>
	bool IsColliding() const;

	/// <summary>
	/// Deactivate this collider.
	/// </summary>
	void Deactivate();

	CollisionTags tags = CollisionTags::None;
	bool enabled = true;

private:
	shared_ptr<Pool<Collider>> pool = nullptr;
	float x, y, w, h;
	void (Collidable::*onCollision)(u16, CollisionTags);
};
