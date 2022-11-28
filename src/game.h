#pragma once

#include <SDL.h>
#include "utils.h"
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
			Surface* screen;
			SDL_Window* window;
			int2 mouse;
			float2 f_mouse;
	};
}; // namespace Tmpl8