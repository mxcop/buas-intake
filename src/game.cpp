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
		//SDL_SetWindowTitle(window, "Test Test Test");
		arm_right = new Bone(screen->GetWidth() / 2 + 20, 30, 0, 50, new Bone(50, 0, 0, 50));
		arm_left = new Bone(screen->GetWidth() / 2 - 20, 30, 180, 50, new Bone(50, 0, 0, 50));

		view = new Camera();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	static Sprite sprite(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;
	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
		// print something in the graphics window
		//screen->Print("hello world", 2, 2, 0xffffff);

		// Update the window title with the frame count:
		std::ostringstream oss;
		oss << "Frame : " << frame << " Delta : " << deltaTime << " Mouse : " << mouse.x << ", " << mouse.y;
		SDL_SetWindowTitle(window, oss.str().c_str());

		screen->Circle(mouse.x, mouse.y, 5, 0xffffff);

		screen->Circle(screen->GetWidth() / 2, screen->GetHeight() / 2 + 20, 80, 0xff0000);
		//screen->Circle(300, 150, 5, 0x00ff00);

		screen->Circle(screen->GetWidth() / 2, 30, 20, 0xffffff);

		arm_right->Update(float2(screen->GetWidth() / 2 + 42, 80));
		arm_right->Draw(screen, float2(0, 0), 0, true);
		arm_left->Update(float2(screen->GetWidth() / 2 - 42, 80));
		arm_left->Draw(screen, float2(0, 0), 0, true);

		sprite.SetFrame(frame);
		sprite.SetFlags(Sprite::FLARE);
		sprite.DrawWithMatrix(screen, view->matrix());

		// print something to the text window
		//printf("this goes to the console window.\n");
		// draw a sprite
		//rotatingGun.SetFrame(frame);
		//rotatingGun.Draw(screen, 100, 100);
		if (++frame == 36) frame = 0;
	}

	void Game::KeyDown(int key) 
	{
		printf("key pressed : %d.\n", key);

		/* Camera cardinal movement */
		if (key == 79) view->move(float2( 1,  0));
		if (key == 80) view->move(float2(-1,  0));
		if (key == 81) view->move(float2( 0, -1));
		if (key == 82) view->move(float2( 0,  1));

		/* Camera rotation */
		if (key == 20) view->rotate(5);
		if (key ==  8) view->rotate(-5);

		/* Camera zoom */
		if (key == 46) view->setZoom(2);
		if (key == 45) view->setZoom(0.5);
	}

	void Game::MouseMove(int dx, int dy) 
	{
		f_mouse.x += dx / static_cast<float>(ScreenScalingFactor);
		f_mouse.y += dy / static_cast<float>(ScreenScalingFactor);

		mouse.x = floor(f_mouse.x);
		mouse.y = floor(f_mouse.y);
	}
};