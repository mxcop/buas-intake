#include "tilemap.h"

void Tilemap::Draw(Tmpl8::Surface* screen, const int2 pos) const
{
	uint s_width = tileset->GetWidth();
	uint s_height = tileset->GetHeight();

	// There might be trouble here due to type mixing (int + uint)
	for (size_t y = pos.y; y < pos.y + height; y++)
	{
		for (size_t x = pos.x; x < pos.x + width; x++)
		{
			tileset->SetFrame(*(values + x + y * width));
			tileset->Draw(screen, x * s_width, y * s_height);
		}
	}
}

Tilemap::~Tilemap()
{
	delete[] values;
	// This might go wrong (not sure how to delete a Sprite)
	delete tileset;
}
