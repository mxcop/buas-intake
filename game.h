#pragma once

#include <SDL.h>

namespace Tmpl8 {

	class Surface;

	class Game
	{
		public:
			void SetTarget( Surface* surface ) { screen = surface; }
			void Init( SDL_Window* win );
			void Shutdown();
			void Tick( float deltaTime );
			void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseMove(int dx, int dy);
			void KeyUp( int key ) { /* implement if you want to handle keys */ }
			void KeyDown( int key ) { /* implement if you want to handle keys */ }
		private:
			Surface* screen;
			SDL_Window* window;
			int mouse_x;
			int mouse_y;
	};
}; // namespace Tmpl8