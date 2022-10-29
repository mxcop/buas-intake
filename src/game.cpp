#include "game.h"
#include "engine/surface.h"
#include "utils.h"
#include "physics/bone.h"
#include <cstdio> //printf
#include <string>
#include <sstream>

namespace Tmpl8
{
	static Bone* arm_left = nullptr;
	static Bone* arm_right = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(SDL_Window* win)
	{
		f_mouse = float2();
		mouse = int2();

		window = win; 
		SDL_SetWindowTitle(window, "Test Test Test");
		arm_right = new Bone(screen->GetWidth() / 2 + 20, 30, 0, 50, new Bone(50, 0, 0, 50));
		arm_left = new Bone(screen->GetWidth() / 2 - 20, 30, 180, 50, new Bone(50, 0, 0, 50));
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
		std::ostringstream oss;
		oss << "Frame : " << frame << " Delta : " << deltaTime << " Mouse : " << mouse.x << ", " << mouse.y;
		SDL_SetWindowTitle(window, oss.str().c_str());

		screen->Circle(mouse.x, mouse.y, 5, 0xffffff);

		screen->Circle(screen->GetWidth() / 2, screen->GetHeight() / 2, 100, 0xff0000);
		//screen->Circle(300, 150, 5, 0x00ff00);

		screen->Circle(screen->GetWidth() / 2, 30, 20, 0xffffff);

		//float2 e = f_mouse;
		arm_right->Update(float2(screen->GetWidth() / 2 + 42, 80));
		arm_right->Draw(screen, float2(0, 0), 0, true);
		arm_left->Update(float2(screen->GetWidth() / 2 - 42, 80));
		arm_left->Draw(screen, float2(0, 0), 0, true);

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