#pragma once
#include <iostream>
#include <vector>

#include "Vertex.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

class Object {
public:
	Object(std::vector<Vertex> vertexAray, std::vector<GLuint> indexArray, glm::vec3 position = glm::vec3(0.0f), glm::vec3 origin = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
	~Object();

	void SetPosition(const glm::vec3 position);
	void SetOrigin(const glm::vec3 origin);
	void SetRotation(const glm::vec3 rotation);
	void SetScale(const glm::vec3 scale);

	void Move(const glm::vec3 position);
	void Rotate(const glm::vec3 rotation);
	void ScaleUp(const glm::vec3 scale);
	
	void render(Shader* shader);
private:
	std::vector<Vertex> vertexArray;
	std::vector<GLuint> indexArray;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void InitVAO();
	void UpdateModelMatrix();
};