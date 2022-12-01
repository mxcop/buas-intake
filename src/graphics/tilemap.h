#pragma once
#include <memory>
#include "../engine/surface.h"
#include "int2.hpp"
#include "types.h"
#include "map/map.h"

class Tilemap: public Map<u8> {
public:
	Tilemap(const u32 width, const u32 height, std::shared_ptr<Tmpl8::Sprite> tileset) : Map(width, height), tileset(tileset) {}
	Tilemap(const u32 width, const u32 height, const u8 def, std::shared_ptr<Tmpl8::Sprite> tileset) : Map(width, height, def), tileset(tileset) {}
	Tilemap(const u32 width, const u32 height, const std::initializer_list<u8> def, std::shared_ptr<Tmpl8::Sprite> tileset) : Map(width, height, def), tileset(tileset) {}
	Tilemap(const u32 width, const u32 height, const std::vector<u8> def, std::shared_ptr<Tmpl8::Sprite> tileset) : Map(width, height, def), tileset(tileset) {}

	/// <summary>
	/// Draw the tilemap to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen, const int2 pos) const;

	/// <returns>True if the given position is within bounds of the tilemap.</returns>
	bool Bounds(const int2 pos) const;
	bool Bounds(const u16 x, const u16 y) const;

	/// <returns>True if the given position is within walkable.</returns>
	bool IsWalkable(const u16 x, const u16 y) const;

private:
	std::shared_ptr<Tmpl8::Sprite> tileset;
};