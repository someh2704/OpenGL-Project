#include "Camera.h"
enum direction{FORWARD=0, BACKWARD, LEFT, RIGHT};

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
{
	this->viewMatirx = glm::mat4(1.0f);

	this->speed = 1.0f;
	this->sensitivity = 0.1f;
	
	this->worldUp = worldUp;
	this->position = position;
	this->right = glm::vec3(0.0f);
	this->up = worldUp;

	this->pitch = 0.0f;
	this->yaw = -90.0f;
	this->roll = 0.0f;

	this->updateCameraVector();

	this->FOV = 45.0f;
	this->width = 4.0f;
	this->height = 3.0f;
	this->nearClip = 0.1f;
	this->farClip = 1000.0f;
}

glm::mat4 Camera::getProjection()
{
	this->projectionMatrix = projectionMatrix = glm::perspective(glm::radians(FOV), this->width / this->height, this->nearClip, this->farClip);
	return projectionMatrix;
}

glm::mat4 Camera::getViewMatirx()
{
	this->updateCameraVector();
	this->viewMatirx = glm::lookAt(
		this->position,
		this->position + this->front,
		this->up
	);

	return this->viewMatirx;
}

glm::vec3 Camera::getPosition()
{
	return this->position;
}

void Camera::updateCameraVector()
{
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

void Camera::move(const float& dt, const int direction) {
	switch (direction) {
	case FORWARD:
		this->position += this->front * this->speed * dt;
		break;
	case BACKWARD:
		this->position -= this->front * this->speed * dt;
		break;
	case LEFT:
		this->position -= this->right * this->speed * dt;
		break;
	case RIGHT:
		this->position += this->right * this->speed * dt;
		break;
	default:
		break;
	}
}

void Camera::updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
{
	this->pitch -= static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
	this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

	if (this->pitch > 80.0f)
		this->pitch = 80.0f;
	else if (this->pitch < -80.0f)
		this->pitch = -80.f;
	
	if (this->yaw > 360.0f || this->yaw < -360.0f)
		this->yaw = 0.0f;
}

void Camera::updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
{
	this->updateMouseInput(dt, offsetX, offsetY);
	this->move(dt, direction);
}
