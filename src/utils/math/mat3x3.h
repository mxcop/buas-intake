#pragma once

#include "../float2.hpp"

class mat3x3 {
private:
	float m[9];

public:
	// Constructors.
	mat3x3() { identity(); }
	mat3x3(float values[9]) : m{ *values } {}

	/// <summary>
	/// Get an element within the matrix.
	/// </summary>
	/// <param name="x">The column to grab from.</param>
	/// <param name="y">The row to grab from.</param>
	/// <returns>The value at the given position.</returns>
	float get(int x, int y) const;

	/// <summary>
	/// Set an element within the matrix.
	/// </summary>
	/// <param name="x">The column of the element.</param>
	/// <param name="y">The row of the element.</param>
	/// <param name="val">The value to insert.</param>
	void set(int x, int y, float val);

	/// <summary>
	/// Turn matrix into identity matrix.
	/// </summary>
	void identity();

	/// <summary>
	/// Multiply by another matrix.
	/// </summary>
	void multiply(const mat3x3& matrix);

	/// <summary>
	/// Translate the matrix by (ox, oy)
	/// </summary>
	/// <param name="ox">Offset on the X axis.</param>
	/// <param name="oy">Offset on the Y axis.</param>
	void translate(float ox, float oy);

	/// <summary>
	/// Rotate the matrix by theta.
	/// </summary>
	/// <param name="theta">The angle in radians.</param>
	void rotate(float theta);

	/// <summary>
	/// Scale the matrix by (x, y)
	/// </summary>
	void scale(float x, float y);

	/// <summary>
	/// Shear the matrix by (sx, sy)
	/// </summary>
	void shear(float sx, float sy);

	/// <summary>
	/// Returns the inverted matrix.
	/// </summary>
	mat3x3 inverted();

	/// <summary>
	/// Transform the given sprite space coordinates into screen space coordinates.
	/// </summary>
	float2 transform(const float2 &sp) const;
};