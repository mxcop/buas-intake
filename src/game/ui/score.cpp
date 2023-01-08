#include "score.h"
#include "../../game.h"
#include <string>
#include <sstream>

using Tmpl8::Game;

/* Score */ #define SCORE Game::score

void Score::Draw(Tmpl8::Surface* screen) const
{
	std::ostringstream oss;
	oss << SCORE;

	screen->Print(oss.str().c_str(), screen->GetWidth() - strlen(oss.str().c_str()) * 6 - 6, 6, 0xFFFFFF);
}

void Score::Add(const int score)
{
	SCORE += score;
}
