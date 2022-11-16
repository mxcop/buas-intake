#pragma once
#include <cmath>

struct int2 {
	int x;
	int y;

	explicit int2() : x{ 0 }, y{ 0 } {}
	int2(int x, int y) : x{ x }, y{ y } {}

	int2 operator-(int2& o) const {
		return int2(x - o.x, y - o.y);
	}

	int2 operator+(int2& o) const {
		return int2(x + o.x, y + o.y);
	}

	int2 operator*(int m) const {
		return int2(x * m, y * m);
	}

	void set(int x, int y) {
		this->x = x;
		this->y = y;
	}
};