#include "player.h"
#include "../game.h"

void Player::Draw(Tmpl8::Surface* screen) const {
	sprite->Draw(screen,
		tile_pos.x * Tmpl8::TileSize + pixel_offset.x,
		tile_pos.y * Tmpl8::TileSize + pixel_offset.y,
	face_left);
}

/// <summary>
/// Check if a position on the tilemap is walkable.
/// </summary>
bool isWalkable(const Tilemap& map, const int2 tile_pos) {
	// Check if the position is walkable & within bounds.
	return map.Bounds(tile_pos)
		&& map.Get(tile_pos.x, tile_pos.y) <= 1;
}

void Player::mov(const Tilemap& map, int2 dir) {
	if (isWalkable(map, tile_pos + dir)) {
		tile_pos += dir;
		pixel_offset = dir * -8;

		// Update the sprite facing direction:
		if (dir.x < 0) face_left = true;
		if (dir.x > 0) face_left = false;
	}
}

void Player::Update(unsigned long frame) {
	// Remove a bit of the offset each frame:
	// Idea was Sourced from the Pork-like game.
	if (pixel_offset.x > 0) pixel_offset.x--;
	if (pixel_offset.x < 0) pixel_offset.x++;
	if (pixel_offset.y > 0) pixel_offset.y--;
	if (pixel_offset.y < 0) pixel_offset.y++;
}

void Player::Move(const Tilemap& map, const Direction dir) {
	// Don't move if we're still animating.
	if (pixel_offset.x != 0 || pixel_offset.y != 0) return;

	switch (dir)
	{
	case Direction::UP:
		mov(map, int2( 0,-1)); break;
	case Direction::RIGHT:
		mov(map, int2( 1, 0)); break;
	case Direction::DOWN:
		mov(map, int2( 0, 1)); break;
	case Direction::LEFT:
		mov(map, int2(-1, 0)); break;
	}
}
