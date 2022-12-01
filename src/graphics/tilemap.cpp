#include "tilemap.h"

void Tilemap::Draw(Tmpl8::Surface* screen, const int2 pos) const
{
	u32 s_width = tileset.GetWidth();
	u32 s_height = tileset.GetHeight();

	// Using static cast to long long here to avoid overflowing.
	for (size_t y = pos.y; y < static_cast<long long>(pos.y) + height; y++)
	{
		for (size_t x = pos.x; x < static_cast<long long>(pos.x) + width; x++)
		{
			tileset.SetFrame(*(values + x + y * width));
			tileset.Draw(screen, x * s_width, y * s_height);
		}
	}
}

bool Tilemap::Bounds(const int2 pos) const
{
	return pos.x >= 0 && pos.y >= 0 && pos.x < width && pos.y < height;
}

bool Tilemap::Bounds(const u16 x, const u16 y) const
{
	return x < width && y < height;
}

bool Tilemap::IsWalkable(const u16 x, const u16 y) const 
{
	return Bounds(x, y) && Get(x, y) <= 1;
}

Tilemap::~Tilemap()
{
	delete[] values;
}
