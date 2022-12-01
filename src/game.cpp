#include "game.h"
#include "engine/surface.h"
#include "physics/bone.h"
#include <memory>
#include <cstdio> // printf
#include <string>
#include <sstream>
#include "game/player.h"
#include "game/enemy.h"
#include "graphics/tilemap.h"
#include "utils/files/csv.cpp"
#include "engine/template.h"
#include "game/arena/arena.h"

// The game is inspired by Pork-like & Deep Rock Galactic
// https://krystman.itch.io/porklike
// https://store.steampowered.com/app/548430/Deep_Rock_Galactic/

namespace Tmpl8
{
	static Sprite s_tileset(new Surface("assets/tiles.png"), 6);
	static Sprite s_ghost(new Surface("assets/ghost.png"), 4);
	static Sprite s_player(new Surface("assets/player.png"), 1);

	static Player* player = nullptr;
	static Tilemap* tilemap = nullptr;
	static EnemyArena* enemies = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(SDL_Window* win)
	{
		window = win;

		enemies = new EnemyArena();

		// Create the player and the tilemap:
		player = new Player(enemies, &s_player, 1, 1);

		tilemap = new Tilemap(16, 16, ldcsv("assets/maps/test.csv"), s_tileset);
		enemies->Add(&s_ghost, 8, 8);
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
		player->Update(frame);
		player->Draw(screen);

		// Draw the enemies.
		enemies->UpdateAll(frame);
		enemies->DrawAll(screen);

		// Increment the frame counter.
		frame++;
	}

	void Game::KeyDown(int key) 
	{
		//printf("key pressed : %d.\n", key);

		/* Player cardinal movement */
		if (key == 79 || key == 7 ) player->Move(*tilemap, cdir::right);
		if (key == 80 || key == 4 ) player->Move(*tilemap, cdir::left);
		if (key == 81 || key == 22) player->Move(*tilemap, cdir::down);
		if (key == 82 || key == 26) player->Move(*tilemap, cdir::up);
	}

	void Game::MouseMove(int dx, int dy) 
	{
		float sx = static_cast<float>(ScreenWidth) / BufferWidth;
		float sy = static_cast<float>(ScreenHeight) / BufferHeight;

		f_mouse.x += dx / sx;
		f_mouse.y += dy / sy;

		mouse.x = floor(f_mouse.x);
		mouse.y = floor(f_mouse.y);
	}
};