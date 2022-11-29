#include "game.h"
#include "engine/surface.h"
#include "utils.h"
#include "physics/bone.h"
#include <cstdio> // printf
#include <string>
#include <sstream>
#include "game/player.h"
#include "graphics/tilemap.h"
#include "utils/files/csv.cpp"

namespace Tmpl8
{
	static Sprite s_tileset(new Surface("assets/tiles.png"), 6);
	static Sprite s_player(new Surface("assets/player.png"), 1);

	static Player* player;
	static Tilemap* tilemap;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(SDL_Window* win)
	{
		f_mouse = float2();
		mouse = int2();

		window = win;
		player = new Player(int2(1, 1), &s_player);
		tilemap = new Tilemap(16, 16, ldcsv("assets/maps/test.csv"), &s_tileset);

		view = new Camera();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// Clear the graphics window.
		screen->Clear(0);

		// Update the window title with the frame count:
		std::ostringstream oss;
		oss << " Delta : " << deltaTime << " Mouse : " << mouse.x << ", " << mouse.y;
		SDL_SetWindowTitle(window, oss.str().c_str());

		// Draw the cursor.
		screen->Circle(mouse.x, mouse.y, 2, 0xffffff);

		// Draw the tilemap.
		tilemap->Draw(screen, int2(0, 0));

		// Draw the player character.
		player->Draw(screen);
	}

	void Game::KeyDown(int key) 
	{
		//printf("key pressed : %d.\n", key);

		/* Player cardinal movement */
		if (key == 79 || key == 7 ) player->Move(tilemap, Direction::RIGHT);
		if (key == 80 || key == 4 ) player->Move(tilemap, Direction::LEFT);
		if (key == 81 || key == 22) player->Move(tilemap, Direction::DOWN);
		if (key == 82 || key == 26) player->Move(tilemap, Direction::UP);
	}

	void Game::MouseMove(int dx, int dy) 
	{
		f_mouse.x += dx / static_cast<float>(ScreenScalingFactor);
		f_mouse.y += dy / static_cast<float>(ScreenScalingFactor);

		mouse.x = floor(f_mouse.x);
		mouse.y = floor(f_mouse.y);
	}
};