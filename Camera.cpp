#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 viewPoint, glm::vec3 up, GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearClip, GLfloat farClip)
	: position(position), viewPoint(viewPoint), up(up), FOV(FOV), width(width), height(height), nearClip(nearClip), farClip(farClip)
{
	updateViewMatrix();
	updateProjectionMatrix();
}

glm::mat4 Camera::getProjection()
{
	updateProjectionMatrix();
	return projectionMatrix;
}

glm::mat4 Camera::getViewMatirx()
{
	updateViewMatrix();
	return viewMatirx;
}

void Camera::updateViewMatrix()
{
	viewMatirx = glm::lookAt(position, viewPoint, up);
}

void Camera::updateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(FOV), width / height, nearClip, farClip);
}
