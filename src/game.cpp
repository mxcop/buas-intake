#include "game.h"
#include "engine/surface.h"
#include <memory>
#include <cstdio> // printf
#include <string>
#include <sstream>
#include "engine/template.h"
#include "engine/keys.h"
#include "game/enemy/turret.h"
#include "game/pool/pool.h"
#include "game/projectile.h"
#include "game/ui/healthbar.h"
#include <bitset>
#include <iostream>

namespace Tmpl8
{
	/* sprites */
	//shared_ptr<Sprite> s_tileset(new Sprite(new Surface("assets/tiles.png"), 6));
	shared_ptr<Sprite> s_turret(new Sprite(new Surface("assets/turret.png"), 1));
	shared_ptr<Sprite> s_bullet(new Sprite(new Surface("assets/bullet.png"), 1));
	shared_ptr<Sprite> s_player(new Sprite(new Surface("assets/player-plane.png"), 4));
	shared_ptr<Sprite> s_player_attack(new Sprite(new Surface("assets/player-attack.png"), 3));
	shared_ptr<Sprite> s_heart(new Sprite(new Surface("assets/heart.png"), 2));
	shared_ptr<Sprite> s_tiles(new Sprite(new Surface("assets/testing-tiles.png"), 2));

	/* objects */
	unique_ptr<HealthBar> healthBar = nullptr;
	unique_ptr<Turret> turret = nullptr;
	unique_ptr<Turret> turret2 = nullptr;
	unique_ptr<Turret> turret3 = nullptr;

	/* pools */
	shared_ptr<Pool<Projectile>> projectiles = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(SDL_Window* win)
	{
		window = win;

		colliders = std::make_shared<Pool<Collider>>(128);

		// Initialize the enemies, player, & tilemap:
		player = std::make_shared<Player>(s_player, s_player_attack, 80, 80);
		projectiles = std::make_shared<Pool<Projectile>>(512);
		turret = std::make_unique<Turret>(40, 40, s_turret, s_bullet, player, projectiles);
		turret2 = std::make_unique<Turret>(120, 80, s_turret, s_bullet, player, projectiles);
		//turret3 = std::make_unique<Turret>(60, 160, s_turret, s_bullet, player, projectiles);

		healthBar = std::make_unique<HealthBar>(s_heart, player);

		//enemies = std::make_shared<EnemyArena>();
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

		for (size_t y = 0; y < ScreenHeight; y++)
		{
			for (size_t x = 0; x < ScreenWidth; x++)
			{
				s_tiles->SetFrame((x + y * ScreenWidth + y % 2) % 2);
				s_tiles->Draw(screen, x * 8, y * 8);
			}
		}

		// Update the window title with the frame count:
		std::ostringstream oss;
		oss << " Delta : " << deltatime << " Mouse : " << mouse.x << ", " << mouse.y << " Colliders : " << colliders->Active();
		SDL_SetWindowTitle(window, oss.str().c_str());

		// Player:
		if (w == true) player->Move( 0, -1);
		if (a == true) player->Move(-1,  0);
		if (s == true) player->Move( 0,  1);
		if (d == true) player->Move( 1,  0);
		player->Tick(frame, deltatime);
		player->Draw(screen);

		turret->Tick(frame);
		turret->Draw(screen);
		turret2->Tick(frame);
		turret2->Draw(screen);
		//turret3->Tick(frame);
		//turret3->Draw(screen);

		projectiles->Tick(frame, deltatime);
		projectiles->Draw(screen);

		healthBar->Draw(screen);

		// Draw the enemies.
		//enemies->UpdateAll(frame);
		//enemies->DrawAll(screen);

		// Draw the cursor.
		screen->Circle(mouse.x, mouse.y, 2, 0xffffff);

		// Increment the frame counter.
		frame++;

		deflectTimer -= deltatime / 1000;
		if (deflectTimer < 1) deflecting = false;
	}

	void Game::KeyDown(int key) 
	{
		std::cout << std::bitset<32>(key) << '\n';
		//printf("key pressed : %d.\n", std::bitset<32>(key));

		/* Player cardinal movement */
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
		float sx = static_cast<float>(ScreenWidth) / BufferWidth;
		float sy = static_cast<float>(ScreenHeight) / BufferHeight;

		f_mouse.x += dx / sx;
		f_mouse.y += dy / sy;

		mouse.x = floor(f_mouse.x);
		mouse.y = floor(f_mouse.y);
	}
};