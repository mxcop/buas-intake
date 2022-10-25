#include "game.h"
#include "surface.h"
#include "./src/types.h"
#include "./src/arm.h"
#include <cstdio> //printf
#include <string>
#include <sstream>

namespace Tmpl8
{
	static KinematicSegment* forearm = nullptr;
	static KinematicSegment* arm = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(SDL_Window* win)
	{
		window = win; 
		SDL_SetWindowTitle(window, "Test Test Test");
		forearm = new KinematicSegment(300, 300, 100);
		arm = new KinematicSegment(200, 200, 200);
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

		screen->Circle(mouse_x, mouse_y, 5, 0xffffff);
		screen->Circle(300, 300, 5, 0xffffff);


		// Try kinematics

		// Start and End positions.
		float2 effector = float2(mouse_x, mouse_y);

		forearm->CalculateB();
		forearm->Follow(effector, false);

		arm->CalculateB();

		//seg2->SetA(float2(200, 200));
		//seg2->CalculateB();
		//seg2->Follow(seg->GetJoint(), false);
		
		forearm->Draw(screen);
		//seg2->Draw(screen);

		// print something to the text window
		//printf("this goes to the console window.\n");
		// draw a sprite
		rotatingGun.SetFrame(frame);
		rotatingGun.Draw(screen, 100, 100);
		if (++frame == 36) frame = 0;
	}

	void Game::MouseMove(int dx, int dy) {
		mouse_x += dx;
		mouse_y += dy;
	}
};