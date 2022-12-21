#include <memory>
#include "../engine/surface.h"

class Player {
public:
	Player(std::shared_ptr<Tmpl8::Sprite> sprite, float x, float y);

	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	void Move(float dx, float dy);

	/// <summary>
	/// Draw the player to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen);

private:
	std::shared_ptr<Tmpl8::Sprite> sprite = nullptr;
	float x, y;
};