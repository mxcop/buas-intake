#include "game.h"
#include "engine/surface.h"
#include "utils.h"
#include "physics/bone.h"
#include <cstdio> //printf
#include <string>
#include <sstream>

namespace Tmpl8
{
	static Bone* arm = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(SDL_Window* win)
	{
		f_mouse = float2();
		mouse = int2();

		window = win; 
		SDL_SetWindowTitle(window, "Test Test Test");
		arm = new Bone(200, 150, 50, new Bone(50, 0, 50));
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;
	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
		// print something in the graphics window
		screen->Print("hello world", 2, 2, 0xffffff);

		// Update the window title with the frame count:
		//std::ostringstream oss;
		//oss << "Frame : " << frame << " Delta : " << deltaTime;
		//SDL_SetWindowTitle(window, oss.str().c_str());

		screen->Circle(mouse.x, mouse.y, 5, 0xffffff);

		screen->Circle(200, 150, 5, 0xff0000);
		screen->Circle(300, 150, 5, 0x00ff00);

		float2 e = f_mouse;
		arm->Update(e);
		arm->Draw(screen, float2(0, 0), 0, true);

		// print something to the text window
		//printf("this goes to the console window.\n");
		// draw a sprite
		//rotatingGun.SetFrame(frame);
		//rotatingGun.Draw(screen, 100, 100);
		if (++frame == 36) frame = 0;
	}

	void Game::MouseMove(int dx, int dy) {
		f_mouse.x += dx / static_cast<float>(ScreenScalingFactor);
		f_mouse.y += dy / static_cast<float>(ScreenScalingFactor);

		mouse.x = floor(f_mouse.x);
		mouse.y = floor(f_mouse.y);
	}
};