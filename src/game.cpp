#include "game.h"
#include "engine/surface.h"
#include "physics/bone.h"
#include <memory>
#include <cstdio> // printf
#include <string>
#include <sstream>
#include "game/enemy.h"
#include "utils/files/csv.cpp"
#include "engine/template.h"

// The game is inspired by Pork-like & Deep Rock Galactic
// https://krystman.itch.io/porklike
// https://store.steampowered.com/app/548430/Deep_Rock_Galactic/

namespace Tmpl8
{
	/* sprites */
	shared_ptr<Sprite> s_tileset(new Sprite(new Surface("assets/tiles.png"), 6));
	shared_ptr<Sprite> s_ghost(new Sprite(new Surface("assets/ghost.png"), 4));
	shared_ptr<Sprite> s_player(new Sprite(new Surface("assets/player.png"), 1));

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(SDL_Window* win)
	{
		window = win;

		// Initialize the enemies, player, & tilemap:
		enemies = std::make_shared<EnemyArena>();

		player.reset(new Player(s_player, 1, 1));
		tilemap = std::make_unique<Tilemap>(16, 16, ldcsv("assets/maps/test.csv"), s_tileset);

		// Temp: add an enemy.
		Enemy::New(s_ghost, 6, 8);
		Enemy::New(s_ghost, 7, 8);
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
		if (key == 79 || key == 7 ) player->Move(cdir::right);
		if (key == 80 || key == 4 ) player->Move(cdir::left);
		if (key == 81 || key == 22) player->Move(cdir::down);
		if (key == 82 || key == 26) player->Move(cdir::up);
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