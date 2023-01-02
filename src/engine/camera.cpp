#include "./camera.h"
#include "./template.h"
#include "../game.h"

Camera::Camera() {}

void Camera::setZoom(float level) {
	zoom = level;
}

void Camera::setAngle(float deg) {
	angle = deg * (PI / 180);
}

void Camera::rotate(float deg)
{
	angle += deg * (PI / 180);
}

void Camera::setPos(float2 pos) {
	position = pos;
}

void Camera::move(float2 movement)
{
	position += movement;
}

float2 Camera::getPos() const
{
	return position;
}

mat3x3 Camera::matrix() const {
	mat3x3 mat = mat3x3();

	mat.scale(zoom, zoom);
	mat.translate(
		static_cast<float>(ScreenWidth / ScreenScalingFactor) / (2 * zoom), 
		static_cast<float>(ScreenHeight / ScreenScalingFactor) / (2 * zoom)
	);
	mat.rotate(angle);
	mat.translate(-position.x, position.y);
	
	return mat;
}