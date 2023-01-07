#include "button.h"
#include "../../game.h"

using Tmpl8::Game;

/* Mouse X    */ #define MOUSE_X Game::mouse_x
/* Mouse Y    */ #define MOUSE_Y Game::mouse_y
/* Mouse Down */ #define MOUSE_DOWN Game::mouse_down

Button::Button(float x, float y, u16 w, u16 h, const char* label, shared_ptr<Signal> onClick)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->label = label;
	this->onClick = onClick;
}

/// <summary>
/// Simple AABB Point2Rect collision check.
/// </summary>
bool AABB(
	float x1, float x2,
	float y1, float y2,
	float w2,
	float h2
) {
	return x1 < x2 + w2 &&
		x1 > x2 &&
		y1 < y2 + h2 &&
		y1 > y2;
}

void Button::Tick()
{
	mouse_over = AABB(MOUSE_X, x, MOUSE_Y, y, w, h);

	if (!mouse_down && MOUSE_DOWN && mouse_over && onClick != nullptr) {
		(*onClick)();
	}

	mouse_down = MOUSE_DOWN && mouse_over;
}

void Button::Draw(Tmpl8::Surface* screen)
{
	screen->Box(x, y, x + w - 1, y + h - 1, mouse_down ? 0x0000ff : mouse_over ? 0x00ff00 : 0xffffff);
	
	int tx = x + (w - 6 * strlen(label)) / 2.0 + 1;
	int ty = y + (h - 6) / 2.0;

	screen->Print(label, tx, ty, 0xffffff);
}
