#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
class Shader {
public:
	Shader(const int versionMajor, const int versionMinor,
			const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFile = "");
	~Shader();
	void Use();
	void UnUse();

	void set1f(GLfloat value, const GLchar* name);
	void setVec3(glm::vec3 value, const GLchar* name);
	void setVec4(glm::vec4 value, const GLchar* name);
	void setMatrix4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
private:
	GLuint ProgramID;
	const int versionMajor;
	const int versionMinor;

	std::string LoadShaderSource(const char* fileName);
	GLuint LoadShader(GLenum type, const char* fileName);
	void LinkProgram(GLuint vertexShader, GLuint geometryShader, GLuint FragmentShader);
};