#include "game.h"
#include "engine/surface.h"
#include <memory>
#include <cstdio> // printf
#include <string>
#include <sstream>
#include "engine/template.h"
#include "engine/keys.h"

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
		player = std::make_unique<Player>(s_player, 80, 80);
		//enemies = std::make_shared<EnemyArena>();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{

	}

	bool w, a, s, d;

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

		// Player:
		if (w == true) player->Move( 0, -1);
		if (a == true) player->Move(-1,  0);
		if (s == true) player->Move( 0,  1);
		if (d == true) player->Move( 1,  0);
		player->Draw(screen);

		// Draw the enemies.
		//enemies->UpdateAll(frame);
		//enemies->DrawAll(screen);

		// Draw the cursor.
		screen->Circle(mouse.x, mouse.y, 2, 0xffffff);

		// Increment the frame counter.
		frame++;
	}

	void Game::KeyDown(int key) 
	{
		//std::cout << std::bitset<32>(key) << '\n';
		//printf("key pressed : %d.\n", std::bitset<32>(key));

		/* Player cardinal movement */
		if (key == KEY_W) w = true;
		if (key == KEY_A) a = true;
		if (key == KEY_S) s = true;
		if (key == KEY_D) d = true;
	}

	void Game::KeyUp(int key) 
	{
		if (key == KEY_W) w = false;
		if (key == KEY_A) a = false;
		if (key == KEY_S) s = false;
		if (key == KEY_D) d = false;
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