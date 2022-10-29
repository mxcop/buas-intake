#pragma once
#include <cmath>

struct float2 {
	float x;
	float y;

	float2() : x{ 0 }, y{ 0 } {}
	float2(float x, float y) : x{ x }, y{ y } {}

	float2 const operator-(float2 const& o) const { float2 r(*this); return r -= o; }
	float2& operator-=(float2 const& o) { x -= o.x; y -= o.y; return *this; }

	float2 const operator+(float2 const& o) const { float2 r(*this); return r += o; }
	float2& operator+=(float2 const& o) { x += o.x; y += o.y; return *this; }

	float2 operator*(float m) const {
		return float2(x * m, y * m);
	}

	void set(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float xx() const {
		return x * x;
	}

	float yy() const {
		return y * y;
	}

	float distance(float2& o) const {
		float dx = (o.x - x);
		float dy = (o.y - y);
		return sqrtf(dx * dx + dy * dy);
	}

	float length() const {
		return sqrt(x * x + y * y);
	}

	float2 normalized() const {
		float l = length();
		return float2(x / l, y / l);
	}
};