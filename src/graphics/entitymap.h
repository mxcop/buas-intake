#pragma once

#include <memory>
#include "../engine/surface.h"
#include "../utils/int2.hpp"
#include "types.h"
#include "map.h"
#include "../game/entity.h"

class Entitymap : public Map<u16> {
public:
	Entitymap(const uint width, const uint height) : Map(width, height) {}

	//void SetPos();

	/// <returns>The id of the entity at a position. (0 if there is no entity)</returns>
	//u16 ReadPos(const u16 x, const u16 y) const;
};