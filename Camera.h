#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 viewPoint, glm::vec3 up, 
		GLfloat FOV = 45.0f, GLfloat width = 4.0f, GLfloat height = 3.0f, GLfloat nearClip = 0.1f, GLfloat farClip = 100.0f);

	glm::mat4 getProjection();
	glm::mat4 getViewMatirx();

private:
	// View Variable
	glm::vec3 position;
	glm::vec3 viewPoint;
	glm::vec3 up;
	

	// Projection Variable
	GLfloat FOV;
	GLfloat width;
	GLfloat height;
	GLfloat nearClip;
	GLfloat farClip;

	glm::mat4 viewMatirx;
	glm::mat4 projectionMatrix;

	void updateViewMatrix();

	void updateProjectionMatrix();
};