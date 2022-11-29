#pragma once
#include <memory>
#include "../engine/surface.h"
#include "../utils/int2.hpp"
#include "map.h"

typedef unsigned char byte;

class Tilemap: public Map<byte> {
public:
	Tilemap(const uint width, const uint height, Tmpl8::Sprite& tileset) : Map(width, height), tileset(tileset) {}
	Tilemap(const uint width, const uint height, const byte def, Tmpl8::Sprite& tileset) : Map(width, height, def), tileset(tileset) {}
	Tilemap(const uint width, const uint height, const std::initializer_list<byte> def, Tmpl8::Sprite& tileset) : Map(width, height, def), tileset(tileset) {}
	Tilemap(const uint width, const uint height, const std::vector<byte> def, Tmpl8::Sprite& tileset) : Map(width, height, def), tileset(tileset) {}

	/// <summary>
	/// Draw the tilemap to the screen.
	/// </summary>
	void Draw(Tmpl8::Surface* screen, const int2 pos) const;

	/// <returns>True if the given position is within bounds of the tilemap.</returns>
	bool Bounds(const int2 pos) const;

	virtual ~Tilemap();

private:
	Tmpl8::Sprite& tileset;
};