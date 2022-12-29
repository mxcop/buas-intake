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
	PlayerProj = 0b00001000
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
/// Rectangle Collider
/// </summary>
class Collider : public Poolable {
public:
	Collider(float x, float y, float w, float h, CollisionTags tags);

	void Tick(const u64 frame, const float deltatime) override { /* Colliders don't tick (unreachable) */ }
	void Draw(Tmpl8::Surface* screen) override { /* Colliders are not visible (unreachable) */ }

	/// <summary>
	/// Static function for creating a new collider.
	/// </summary>
	/// <returns>A raw pointer to the collider. (because I'm uncertain about smart pointer behaviour)</returns>
	static Collider* New(float x, float y, float w, float h, CollisionTags tags = CollisionTags::None);

	/// <summary>
	/// Set the position of the collider.
	/// </summary>
	void SetPos(const float x, const float y);

	/// <returns>If this collider is currently intersecting with another collider.</returns>
	bool IsColliding();

	/// <summary>
	/// Check if collider is colliding with respect to the given mask (e.g. `CollisionTags::Player | CollisionTags::Enemy`)
	/// </summary>
	bool IsCollidingWithMask(CollisionTags mask);

	/// <summary>
	/// Deactivate this collider.
	/// </summary>
	void Deactivate();

	CollisionTags tags = CollisionTags::None;

private:
	shared_ptr<Pool<Collider>> pool = nullptr;
	float x, y, w, h;
};