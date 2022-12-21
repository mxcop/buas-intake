/* Inspired by javidx9 video : https://www.youtube.com/watch?v=zxwLN2blwbQ */

#include "mat3x3.h"
#include <algorithm>

mat3x3::mat3x3()
{
	identity();
}

mat3x3::mat3x3(std::initializer_list<float> values) {
	if (values.size() > 9) throw "Attempted to create matrix 3x3 using more then 9 values!";
	if (values.size() < 9) throw "Attempted to create matrix 3x3 using less then 9 values!";

	int count{ 0 };
	for (float val : values)
	{
		m[count] = val;
		count++;
	}
};

float mat3x3::get(int x, int y) const
{
	return m[y * 3 + x];
}

void mat3x3::set(int x, int y, float val) 
{
	m[y * 3 + x] = val;
}

void mat3x3::identity() 
{
	m[0] = 1; m[1] = 0; m[2] = 0;
	m[3] = 0; m[4] = 1; m[5] = 0;
	m[6] = 0; m[7] = 0; m[8] = 1;
}

void mat3x3::multiply(const mat3x3& matrix) 
{
	for (size_t c = 0; c < 3; c++) {
		for (size_t r = 0; r < 3; r++) {
			set(c, r,
				get(0, r) * matrix.get(c, 0) +
				get(1, r) * matrix.get(c, 1) +
				get(2, r) * matrix.get(c, 2)
			);
		}
	}
}

void mat3x3::translate(float ox, float oy) 
{
	// 1 | 0 | ox
	// 0 | 1 | oy
	// 0 | 0 | 1
	multiply(mat3x3({
		1, 0, ox,
		0, 1, oy,
		0, 0, 1
	}));
}

void mat3x3::rotate(float theta)
{
	// cos(t)  | -sin(t) | 0
	// sin(t)  |  cos(t) | 0
	// 0       |  0      | 1
	multiply(mat3x3({
	    cosf(theta), sinf(theta), 0,
	   -sinf(theta), cosf(theta), 0,
	    0         ,  0         , 1
	}));
}

void mat3x3::scale(float x, float y)
{
	// x | 0 | 0
	// 0 | y | 0
	// 0 | 0 | 1
	multiply(mat3x3({
		x, 0, 0,
		0, y, 0,
		0, 0, 1
	}));
}

void mat3x3::shear(float sx, float sy)
{
	// 1  | sx | 0
	// sy | 1  | 0
	// 0  | 0  | 1
	multiply(mat3x3({
		1 , sx, 0,
		sy, 1 , 0,
		0 , 0 , 1
	}));
}

/* Copied this function 1 to 1 from the video : https://www.youtube.com/watch?v=zxwLN2blwbQ */
/* He didn't go into any detail about how it works, because apparently it's pretty complex. */
mat3x3 mat3x3::inverted()
{
	mat3x3 result = mat3x3();

	float det = 
		get(0, 0) * (get(1, 1) * get(2, 2) - get(1, 2) * get(2, 1)) -
		get(1, 0) * (get(0, 1) * get(2, 2) - get(2, 1) * get(0, 2)) +
		get(2, 0) * (get(0, 1) * get(1, 2) - get(1, 1) * get(0, 2));

	float idet = 1.0f / det;
	result.set(0, 0, (get(1, 1) * get(2, 2) - get(1, 2) * get(2, 1)) * idet);
	result.set(1, 0, (get(2, 0) * get(1, 2) - get(1, 0) * get(2, 2)) * idet);
	result.set(2, 0, (get(1, 0) * get(2, 1) - get(2, 0) * get(1, 1)) * idet);
	result.set(0, 1, (get(2, 1) * get(0, 2) - get(0, 1) * get(2, 2)) * idet);
	result.set(1, 1, (get(0, 0) * get(2, 2) - get(2, 0) * get(0, 2)) * idet);
	result.set(2, 1, (get(0, 1) * get(2, 0) - get(0, 0) * get(2, 1)) * idet);
	result.set(0, 2, (get(0, 1) * get(1, 2) - get(0, 2) * get(1, 1)) * idet);
	result.set(1, 2, (get(0, 2) * get(1, 0) - get(0, 0) * get(1, 2)) * idet);
	result.set(2, 2, (get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0)) * idet);

	return result;
}

void mat3x3::bounds(float w, float h, float2& min, float2& max)
{
	float2 tl = transform(float2(0, 0));
	float2 tr = transform(float2(w, 0));
	float2 br = transform(float2(w, h));
	float2 bl = transform(float2(0, h));

	min = float2(std::min(std::min(std::min(tl.x, tr.x), br.x), bl.x), std::min(std::min(std::min(tl.y, tr.y), br.y), bl.y));
	max = float2(std::max(std::max(std::max(tl.x, tr.x), br.x), bl.x), std::max(std::max(std::max(tl.y, tr.y), br.y), bl.y));
}

float2 mat3x3::transform(const float2& sp) const {
	return float2(
		sp.x * get(0, 0) + sp.y * get(1, 0) + get(2, 0),
		sp.x * get(0, 1) + sp.y * get(1, 1) + get(2, 1)
	);
}
