#pragma once
#include <types.h>
#include "../../engine/surface.h"
#include "signals.hpp"

using Signal = sig::signal<void()>;
using std::shared_ptr;

class Button {
public:
	Button(float x, float y, u16 w, u16 h, const char* label, shared_ptr<Signal> onClick = nullptr);

	/// <summary>
	/// Called every tick.
	/// </summary>
	void Tick();

	/// <summary>
	/// Draw the button to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen);

private:
	shared_ptr<Signal> onClick = nullptr;
	float x, y;
	u16 w, h;
	const char* label = nullptr;

	bool mouse_over = false;
	bool mouse_down = false;
};