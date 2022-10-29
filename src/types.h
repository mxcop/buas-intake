#pragma once
#include <cmath>

struct float2 {
	float x;
	float y;

	float2() : x{ 0 }, y{ 0 } {}
	float2(float x, float y) : x{ x }, y{ y } {}

	/*float2 operator-(float2& o) const {
		return float2(x - o.x, y - o.y);
	}*/

	/*float2 operator+(float2& o) const {
		return float2(x + o.x, y + o.y);
	}*/

	float2 const operator- (float2 const& rhs) const { float2 result(*this); return result -= rhs; }
	float2& operator-=(float2 const& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

	float2 const operator+ (float2 const& rhs) const { float2 result(*this); return result += rhs; }
	float2& operator+=(float2 const& rhs) { x += rhs.x; y += rhs.y; return *this; }

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
		return sqrtf(dx*dx + dy*dy);
	}

	float length() const {
		return sqrt(x*x + y*y);
	}

	float2 normalized() const {
		float l = length();
		return float2(x / l, y / l);
	}
};

struct int2 {
	int x;
	int y;

	int2() : x{ 0 }, y{ 0 } {}
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