#include "game.h"
#include "surface.h"
#include "./src/types.h"
#include "./src/arm.h"
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
		window = win; 
		SDL_SetWindowTitle(window, "Test Test Test");
		arm = new Bone(300, 300, 100, new Bone(100, 0, 100));
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
		float2 c = float2(300, 300);
		float2 e = float2(mouse_x, mouse_y) - c;
		float a1 = 100;
		float a2 = 100;

		float q1 = NAN;
		float q2 = NAN;

		if (e.x > 0) {
			q2 = acos((e.xx() + e.yy() - a1 * a1 - a2 * a2) / (2.0 * a1 * a2));
			q1 = atan(e.y / e.x) - atan((a2 * sin(q2)) / (a1 + a2 * cos(q2)));
		}
		else if (e.x < 0) {
			q2 = -acos((e.xx() + e.yy() - a1 * a1 - a2 * a2) / (2.0 * a1 * a2));
			q1 = atan(e.y / e.x) + atan((a2 * sin(q2)) / (a1 + a2 * cos(q2)));
		}

		if (e.x != 0 && e.y != 0) {
			if (!isnan(q1) && !isnan(q2)) {
				float2 p1 = c;
				float2 p2;
				float2 p3;

				if (e.x >= 0) {
					p2 = float2(p1.x + cos(q1) * a1, p1.y + sin(q1) * a1);
					p3 = float2(p2.x + cos(q1 + q2) * a2, p2.y + sin(q1 + q2) * a2);
				}
				else {
					p2 = float2(p1.x - cos(q1) * a1, p1.y - sin(q1) * a1);
					p3 = float2(p2.x - cos(q1 - q2) * a2, p2.y - sin(q1 - q2) * a2);
				}

				screen->Line(p1.x, p1.y, p2.x, p2.y, 0xffffff);
				screen->Line(p2.x, p2.y, p3.x, p3.y, 0xffffff);
			}
			else {
				float2 b = e.normalized() * (a1 + a2);
				screen->Line(c.x, c.y, c.x + b.x, c.y + b.y, 0xffffff);
			}
		}

		//arm->Update(effector);
		//arm->Draw(screen, float2(0, 0));

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