#pragma once
#include "pool/pool.h"
#include <memory>

using std::shared_ptr;
using std::unique_ptr;

class Collider : public Poolable {
public:
	Collider(float x, float y, float w, float h);

	static Collider* New(float x, float y, float w, float h);

	void Tick(const u64 frame, const float deltatime) override { /* Colliders don't tick (unreachable) */ }
	void Draw(Tmpl8::Surface* screen) override; //{ /* Colliders are not visible (unreachable) */ }

	/// <summary>
	/// Set the position of the collider.
	/// </summary>
	void SetPos(const float x, const float y);

	/// <returns>If this collider is currently intersecting with another collider.</returns>
	bool IsColliding();

	/// <summary>
	/// Deactivate this collider.
	/// </summary>
	void Deactivate();

private:
	shared_ptr<Pool<Collider>> pool = nullptr;
	float x, y, w, h;
};