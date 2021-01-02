#include "Object.h"

Object::Object(std::vector<Vertex> vertexArray, std::vector<GLuint> indexArray, glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale) {
	this->position = position;
	this->origin = origin;
	this->rotation = rotation;
	this->scale = scale;
	
	this->vertexArray = vertexArray;
	this->indexArray = indexArray;

	this->InitVAO();
	this->UpdateModelMatrix();
}

Object::~Object()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);

	if (this->indexArray.size() > 0) {
		glDeleteBuffers(1, &this->EBO);
	}
}

void Object::SetPosition(const glm::vec3 position)
{
	this->position = position;
}

void Object::SetOrigin(const glm::vec3 origin)
{
	this->origin = origin;
}

void Object::SetRotation(const glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Object::SetScale(const glm::vec3 scale)
{
	this->scale = scale;
}

void Object::Move(const glm::vec3 position)
{
	this->position += position;
}

void Object::Rotate(const glm::vec3 rotation)
{
	this->rotation += rotation;
}

void Object::ScaleUp(const glm::vec3 scale)
{
	this->scale += scale;
}

void Object::InitVAO()
{
	// Create VAO
	glCreateVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// VBO
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertexArray.size() * sizeof(Vertex), &this->vertexArray[0], GL_STATIC_DRAW);

	// EBO
	if (indexArray.size() > 0) {
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->vertexArray.size() * sizeof(GLuint), &this->indexArray[0], GL_STATIC_DRAW);
	}

	// VertexAttribPointer
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	// Normal will use later with Material
	// glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	// glEnableVertexAttribArray(2);

	// Bind VAO 0
	glBindVertexArray(0);
}

void Object::UpdateModelMatrix()
{
	this->ModelMatrix = glm::mat4(1.0f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

void Object::UpdateUniforms(Shader* shader)
{
	shader->setMatrix4fv(this->ModelMatrix, "ModelMatrix");
}

glm::mat4 Object::getMatrix()
{
	this->UpdateModelMatrix();
	return ModelMatrix;
}

void Object::render(Shader* shader)
{
	this->UpdateModelMatrix();
	this->UpdateUniforms(shader);
	shader->Use();
	// Bind VAO
	glBindVertexArray(this->VAO);
	
	if (this->indexArray.size() == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->vertexArray.size());
	else
		glDrawElements(GL_TRIANGLES, this->indexArray.size(), GL_UNSIGNED_INT, 0);

	// glBindVertexArray(0);
	glUseProgram(0);
}
