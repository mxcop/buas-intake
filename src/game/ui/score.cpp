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

	screen->Print(oss.str().c_str(), 100, 100, 0xFFFFFF);
}
