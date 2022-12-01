#pragma once

#include <memory>
#include <SDL.h>
#include "int2.hpp"
#include "float2.hpp"

#include "game/player.h"
#include "game/arena/arena.h"
#include "graphics/tilemap.h"

using std::shared_ptr;
using std::unique_ptr;

namespace Tmpl8 {

	constexpr int ScreenScalingFactor = 4;

	constexpr int TilemapWidth = 16;
	constexpr int TilemapHeight = 16;

	constexpr int TileSize = 8;

	class Surface;

	//class Game
	//{
	//	public:
	//		static unique_ptr<Tilemap> tilemap;
	//		void SetTarget( Surface* surface ) { screen = surface; }
	//		void Init( SDL_Window* win );
	//		void Shutdown();
	//		void Tick( float deltaTime );
	//		void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	//		void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	//		void MouseMove(int dx, int dy);
	//		void KeyUp( int key ) { /* implement if you want to handle keys */ }
	//		void KeyDown(int key);
	//	private:
	//		/* windowing */
	//		Surface* screen = nullptr;
	//		SDL_Window* window = nullptr;

	//		/* globals */
	//		unsigned long frame = 0u;
	//		int2 mouse = int2();
	//		float2 f_mouse = float2();

	//		/* objects */
	//		unique_ptr<Player> player = nullptr;
	//		shared_ptr<EnemyArena> enemies = nullptr;
	//};

	class Game
	{
	public:
		Game(Game const&) = delete;
		void operator=(Game const&) = delete;

		// C++ singleton pattern : https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
		static std::shared_ptr<Game> instance()
		{
			static std::shared_ptr<Game> s{ new Game };
			return s;
		}

		void SetTarget(Surface* surface) { screen = surface; }
		void Init(SDL_Window* win);
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int dx, int dy);
		void KeyUp(int key) { /* implement if you want to handle keys */ }
		void KeyDown(int key);

		shared_ptr<Tilemap> tilemap = nullptr;

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
		shared_ptr<EnemyArena> enemies = nullptr;
	};
}; // namespace Tmpl8