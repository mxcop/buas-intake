#pragma once

#include <memory>
#include <SDL.h>
#include "int2.hpp"
#include "float2.hpp"
#include "game/player.h"

using std::shared_ptr;
using std::unique_ptr;

namespace Tmpl8 {
	/* constants */
	constexpr int ScreenScalingFactor = 4;
	constexpr int TilemapWidth = 16;
	constexpr int TilemapHeight = 16;
	constexpr int TileSize = 8;

	class Surface;

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

		/* functions */
		void SetTarget(Surface* surface) { screen = surface; }
		void Init(SDL_Window* win);
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int dx, int dy);
		void KeyUp(int key);
		void KeyDown(int key);

		/* objects */
		//shared_ptr<EnemyArena> enemies = nullptr;

	private:
		Game() {}

		/* windowing */
		Surface* screen = nullptr;
		SDL_Window* window = nullptr;

		/* globals */
		unsigned long frame = 0u;
		int2 mouse = int2();
		float2 f_mouse = float2();

		/* objects */
		unique_ptr<Player> player = nullptr;
	};
}; // namespace Tmpl8