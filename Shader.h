#pragma once
#include <GL/glew.h>
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
private:
	GLuint ProgramID;
	const int versionMajor;
	const int versionMinor;

	std::string LoadShaderSource(const char* fileName);
	GLuint LoadShader(GLenum type, const char* fileName);
	void LinkProgram(GLuint vertexShader, GLuint geometryShader, GLuint FragmentShader);
};