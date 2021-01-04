#include "Light.h"



Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color, GLfloat intensity,
	GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	this->position = position;
	this->color = color;

	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;

	this->intensity = intensity;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void Light::setPosition(const glm::vec3 position)
{
	this->position = position;
}

void Light::sendToShader(Shader* shader)
{
	shader->setVec3(this->ambient, "light.ambient");
	shader->setVec3(this->diffuse, "light.diffuse");
	shader->setVec3(this->specular, "light.specular");

	shader->setVec3(this->position, "element.position");
	shader->setVec3(this->color, "element.color");

	shader->set1f(this->intensity, "element.intensity");
	shader->set1f(this->constant, "element.constant");
	shader->set1f(this->linear, "element.linear");
	shader->set1f(this->quadratic, "element.quadratic");
}
