#include "game.h"
#include "engine/surface.h"
#include <memory>
#include <cstdio> // printf
#include <string>
#include <sstream>
#include "engine/template.h"
#include "engine/keys.h"
#include "game/pool/pool.h"
#include "game/projectile.h"
#include "game/ui/healthbar.h"
#include "game/ui/button.h"

using std::make_shared;
using std::make_unique;

namespace Tmpl8
{
	float Game::mouse_x = 0;
	float Game::mouse_y = 0;
	bool Game::mouse_down = false;

	/* sprites */
	shared_ptr<Sprite> s_turret(new Sprite(new Surface("assets/turret.png"), 1));
	shared_ptr<Sprite> s_plane(new Sprite(new Surface("assets/enemy-plane.png"), 4));
	shared_ptr<Sprite> s_bullet(new Sprite(new Surface("assets/bullet.png"), 1));
	shared_ptr<Sprite> s_player(new Sprite(new Surface("assets/player-plane.png"), 4));
	shared_ptr<Sprite> s_player_attack(new Sprite(new Surface("assets/player-attack.png"), 3));
	shared_ptr<Sprite> s_heart(new Sprite(new Surface("assets/heart.png"), 2));
	shared_ptr<Sprite> s_tiles(new Sprite(new Surface("assets/testing-tiles.png"), 2));

	/* objects */
	unique_ptr<HealthBar> healthBar = nullptr;
	unique_ptr<Button> playButton = nullptr;
	unique_ptr<Button> quitButton = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(SDL_Window* win)
	{
		window = win;

		/* Initialize the object pools */
		colliders   = make_shared<Pool<Collider>   >(128);
		projectiles = make_shared<Pool<Projectile> >(512);
		turrets     = make_shared<Pool<Turret>     >(16);
		planes      = make_shared<Pool<Plane>      >(16);

		/* Initialize the player object */
		player      = make_shared<Player>(s_player, s_player_attack, 80, 80);

		/* Initialize the HUD */
		healthBar   = make_unique<HealthBar>(s_heart, player);

		/* Initialize some enemies for testing */
		turrets   ->  Add(Turret(40, 40, s_turret, s_bullet, player, projectiles));
		turrets   ->  Add(Turret(240, 80, s_turret, s_bullet, player, projectiles));
		planes    ->  Add(Plane(screen->GetWidth() / 2, 120, s_plane, s_bullet, player, projectiles));

		/* Initialize the UI */
		playButton  = make_unique<Button>(100, 100, 32, 16, "play");
		quitButton  = make_unique<Button>(100, 200, 32, 16, "quit");
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{

	}

	bool w, a, s, d;
	float deflectTimer = 0;

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltatime)
	{
		// Clear the graphics window.
		screen->Clear(0);

		/* Draw a tile grid as background */
		for (size_t y = 0; y < ScreenHeight / 8; y++)
		{
			for (size_t x = 0; x < ScreenWidth / 8; x++)
			{
				s_tiles->SetFrame((x + y * ScreenWidth + y % 2) % 2);
				s_tiles->Draw(screen, x * 8, y * 8);
			}
		}

		// Update the window title with the frame count:
		std::ostringstream oss;
		oss << " Delta : " << deltatime << " Mouse : " << mouse.x << ", " << mouse.y << " Colliders : " << colliders->Active();
		SDL_SetWindowTitle(window, oss.str().c_str());

		/* Update and Draw the object pools */
		projectiles->Tick(frame, deltatime);
		turrets->Tick(frame, deltatime);
		planes->Tick(frame, deltatime);

		projectiles->Draw(screen);
		turrets->Draw(screen);
		planes->Draw(screen);

		/* Update and Draw the player */
		if (w == true) player->Move(0, -1);
		if (a == true) player->Move(-1, 0);
		if (s == true) player->Move(0, 1);
		if (d == true) player->Move(1, 0);
		player->Tick(frame, deltatime);
		player->Draw(screen);

		/* Draw the HUD */
		healthBar->Draw(screen);

		playButton->Tick();
		playButton->Draw(screen);
		quitButton->Tick();
		quitButton->Draw(screen);

		/* Draw a cursor */
		screen->Circle(mouse.x, mouse.y, 2, 0xffffff);

		/* Increment the frame counter */
		frame++;

		deflectTimer -= deltatime / 1000;
		if (deflectTimer < 1) deflecting = false;
	}

	void Game::KeyDown(int key) 
	{
		// std::cout << std::bitset<32>(key) << '\n';

		/* WASD inputs */
		if (key == KEY_W) w = true;
		if (key == KEY_A) a = true;
		if (key == KEY_S) s = true;
		if (key == KEY_D) d = true;

		if (key == KEY_SPACE && deflectTimer <= 0) {
			deflecting = true;
			deflectTimer = 1;
			player->Attack();
		}

		if (key == KEY_SHIFT) {
			player->shrink = true;
		}
	}

	void Game::KeyUp(int key) 
	{
		/* WASD inputs */
		if (key == KEY_W) w = false;
		if (key == KEY_A) a = false;
		if (key == KEY_S) s = false;
		if (key == KEY_D) d = false;

		if (key == KEY_SHIFT) {
			player->shrink = false;
		}
	}

	void Game::MouseMove(int dx, int dy) 
	{
		/* Store the updated mouse position */
		float sx = static_cast<float>(ScreenWidth) / BufferWidth;
		float sy = static_cast<float>(ScreenHeight) / BufferHeight;

		f_mouse.x += dx / sx;
		f_mouse.y += dy / sy;

		Game::mouse_x = f_mouse.x;
		Game::mouse_y = f_mouse.y;

		mouse.x = floor(f_mouse.x);
		mouse.y = floor(f_mouse.y);
	}

	void Game::MouseDown(int button) {
		if (button == 1) Game::mouse_down = true;
	}

	void Game::MouseUp(int button) {
		if (button == 1) Game::mouse_down = false;
	}
};