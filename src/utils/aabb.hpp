//#pragma once
//
///// <summary>
///// Simple AABB Rect2Rect collision check.
///// </summary>
//bool AABB(
//	float x1, float x2,
//	float y1, float y2,
//	float w1, float w2,
//	float h1, float h2
//) {
//	return x1 < x2 + w2 &&
//		x1 + w1 > x2 &&
//		y1 < y2 + h2 &&
//		y1 + h1 > y2;
//}
//
///// <summary>
///// Simple AABB Point2Rect collision check.
///// </summary>
//bool AABB(
//	float x1, float x2,
//	float y1, float y2,
//	float w2,
//	float h2
//) {
//	return x1 < x2 + w2 &&
//		x1 > x2 &&
//		y1 < y2 + h2 &&
//		y1 > y2;
//}