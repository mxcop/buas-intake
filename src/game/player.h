#pragma once
#include "../engine/surface.h"
#include "../utils/int2.hpp"
#include "../graphics/tilemap.h"

enum class Direction { UP, RIGHT, DOWN, LEFT };

class Player {
public:
	Player(int2 tile_pos, Tmpl8::Sprite* sprite) : tile_pos(tile_pos), sprite(sprite) {}

	/// <summary>
	/// Draw the player to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen) const;

	/// <summary>
	/// Update the player's animation.
	/// </summary>
	/// <param name="frame"></param>
	void Update(unsigned long frame);

	/// <summary>
	/// Move the player one tile into the given direction.
	/// </summary>
	void Move(const Tilemap& map, const Direction dir);

private:
	Tmpl8::Sprite* sprite = nullptr;
	int2 tile_pos = int2(0, 0);
	int2 pixel_offset = int2(0, 0);
	bool face_left = false;

	/// <summary>More flexible move function.</summary>
	void mov(const Tilemap& map, const int2 dir);
};