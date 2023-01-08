#pragma once
#include "../../engine/surface.h"

class Score {
public:
	Score() {}

	void Draw(Tmpl8::Surface* screen) const;

	/// <summary>
	/// Add some points to the score.
	/// </summary>
	static void Add(const int score);
};