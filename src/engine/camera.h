#pragma once
#include "../utils/math/mat3x3.h"

constexpr float PI = 3.14159f;

class Camera {
public:
	Camera();

	/// <summary>Sets the current camera zoom level.</summary>
	void setZoom(float level);

	/// <summary>Sets the current camera angle.</summary>
	void setAngle(float deg);

	/// <summary>Rotate the camera.</summary>
	void rotate(float deg);

	/// <summary>Sets the current camera position.</summary>
	void setPos(float2 pos);

	/// <summary>Move the camera.</summary>
	void move(float2 movement);

	/// <returns>The current camera position.</returns>
	float2 getPos() const;

	/// <returns>The transformation matrix of the current position, rotation, and zoom level.</returns>
	mat3x3 matrix() const;

private:
	float zoom = 1;
	float angle = 0;
	float2 position = float2(0, 0);
};