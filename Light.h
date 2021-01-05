#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Object.h"
#include <vector>

class Light {
public:
	Light(glm::vec3 position,  glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), GLfloat intensity = 1.0f,
		GLfloat constant = 1.0f, GLfloat linear = 0.045f, GLfloat quadratic = 0.001f);

	void setPosition(const glm::vec3 position);
	void sendToShader(Shader* shader);
	void updateMatrix();
	void updateUniform(Shader* shader);
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	
	glm::vec3 color;

	// Position
	glm::vec3 position;
	GLfloat constant;
	GLfloat linear;
	GLfloat quadratic;
	GLfloat intensity;

	// Matrix
	glm::mat4 lightView;
	glm::mat4 lightProjection;
	glm::mat4 depthModelMatrix;

	glm::mat4 depthMVP;
};