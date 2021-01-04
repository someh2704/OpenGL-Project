#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);

	glm::mat4 getProjection();
	glm::mat4 getViewMatirx();
	glm::vec3 getPosition();

	void move(const float& dt, const int direction);
	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);
	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);
private:
	// View Variable
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	GLfloat speed;
	GLfloat sensitivity;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	GLfloat FOV;
	GLfloat nearClip;
	GLfloat farClip;

	glm::mat4 viewMatirx;


	glm::mat4 projectionMatrix;
	GLfloat width;
	GLfloat height;
	void updateCameraVector();
};