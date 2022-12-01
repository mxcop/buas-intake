#pragma once

#include <SDL.h>
#include "utils/int2.hpp"
#include "utils/float2.hpp"
#include "engine/camera.h"

namespace Tmpl8 {

	constexpr int ScreenScalingFactor = 4;

	constexpr int TilemapWidth = 16;
	constexpr int TilemapHeight = 16;

	constexpr int TileSize = 8;

	class Surface;

	class Game
	{
		public:
			Camera* view;
			void SetTarget( Surface* surface ) { screen = surface; }
			void Init( SDL_Window* win );
			void Shutdown();
			void Tick( float deltaTime );
			void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseMove(int dx, int dy);
			void KeyUp( int key ) { /* implement if you want to handle keys */ }
			void KeyDown(int key);
		private:
			Surface* screen = nullptr;
			SDL_Window* window = nullptr;
			unsigned long frame = 0u;
			int2 mouse = int2();
			float2 f_mouse = float2();
	};
}; // namespace Tmpl8