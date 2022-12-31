#include <memory>
#include "../engine/surface.h"
#include <types.h>
#include "collider.h"

using std::shared_ptr;
using Tmpl8::Sprite;

class Player {
public:
	Player(shared_ptr<Sprite> sprite, float x, float y);

	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	void Move(const float dx, const float dy);

	/// <summary>
	/// Draw the player to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen) const;

	/// <summary>
	/// Should be called every tick.
	/// </summary>
	void Tick(const u64 frame);

	/// <returns>Get the current position of the player.</returns>
	float2 GetPosition() const;

private:
	shared_ptr<Sprite> sprite = nullptr;
	Collider* collider = nullptr;
	Collider* areaOfAttack = nullptr;
	float x, y;
	u16 w, h;
};