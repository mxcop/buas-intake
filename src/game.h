#pragma once

#include <memory>
#include <SDL.h>
#include "int2.hpp"
#include "float2.hpp"
#include "game/player.h"
#include "game/collider.h"
#include "game/enemy/turret.h"
#include "game/enemy/plane.h"

using std::shared_ptr;
using std::unique_ptr;

namespace Tmpl8 {
	/* constants */
	constexpr int TilemapWidth = 32;
	constexpr int TilemapHeight = 32;
	constexpr int TileSize = 8;

	class Surface;

	enum class GameState {
		MENU = 0b00,
		GAME = 0b01,
		DEAD = 0b10
	};

	class Game
	{
	public:
		// Don't allow creation of instances outside the class:
		Game(Game const&) = delete;
		void operator=(Game const&) = delete;

		// C++ singleton pattern : <https://stackoverflow.com/questions/1008019/c-singleton-design-pattern>
		static shared_ptr<Game> instance() {
			static shared_ptr<Game> s{ new Game };
			return s;
		}

		/* static mouse position */
		static float mouse_x;
		static float mouse_y;
		static bool mouse_down;

		/* static score */
		static u32 score;

		/* functions */
		void SetTarget(Surface* surface) { screen = surface; }
		void Init(SDL_Window* win);
		void Setup();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button);
		void MouseDown(int button);
		void MouseMove(int dx, int dy);
		void KeyUp(int key);
		void KeyDown(int key);
		void Gameover();

		/* inputs */
		bool deflecting = false;

		/* objects */
		shared_ptr<Pool<Collider>> colliders = nullptr;
		shared_ptr<Pool<Turret>> turrets = nullptr;
		shared_ptr<Pool<Plane>> planes = nullptr;

	private:
		Game() {}

		void Play();
		void Return();
		void Quit();

		/* windowing */
		Surface* screen = nullptr;
		SDL_Window* window = nullptr;
		GameState state = GameState::MENU;

		/* globals */
		unsigned long frame = 0u;
		int2 mouse = int2();
		float2 f_mouse = float2();

		/* objects */
		shared_ptr<Player> player = nullptr;
		shared_ptr<Pool<Projectile>> projectiles = nullptr;
	};
}; // namespace Tmpl8