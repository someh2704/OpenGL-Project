#include "Shader.h"

Shader::Shader(const int versionMajor, const int versionMinor, const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFile)
	: versionMajor(versionMajor), versionMinor(versionMinor)
{
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;

	// Load Shader
	vertexShader = LoadShader(GL_VERTEX_SHADER, vertexFilePath);

	if (geometryFile != "")
		geometryShader = LoadShader(GL_GEOMETRY_SHADER, geometryFile);

	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentFilePath);

	// Link Shader
	this->LinkProgram(vertexShader, geometryShader, fragmentShader);

	// End
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(this->ProgramID);
}

void Shader::Use()
{
	glUseProgram(this->ProgramID);
}

void Shader::UnUse()
{
	glUseProgram(0);
}

void Shader::set1f(GLfloat value, const GLchar* name)
{
	this->Use();
	glUniform1f(glGetUniformLocation(this->ProgramID, name), value);
}

void Shader::setVec3(glm::vec3 value, const GLchar* name)
{
	this->Use();
	glUniform3fv(glGetUniformLocation(this->ProgramID, name), 1, glm::value_ptr(value));
}

void Shader::setVec4(glm::vec4 value, const GLchar* name)
{
	this->Use();
	glUniform3fv(glGetUniformLocation(this->ProgramID, name), 1, glm::value_ptr(value));
	this->UnUse();
}

void Shader::setMatrix4fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
{
	this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->ProgramID, name), 1, transpose, glm::value_ptr(value));
	this->UnUse();
}

std::string Shader::LoadShaderSource(const char* fileName)
{
	std::string src = "";
	std::fstream in_file(fileName, std::ios::in);

	if (in_file.is_open()) {
		std::stringstream sstr;
		sstr << in_file.rdbuf();
		src = sstr.str();
		in_file.close();
	}
	else {
		std::cout << "Filed to Open File: " << fileName << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::string version =
		std::to_string(this->versionMajor) +
		std::to_string(this->versionMinor) +
		"0";

	src.replace(src.find("#version"), 12, ("#version " + version));

	return src;
}

GLuint Shader::LoadShader(GLenum type, const char* fileName) {
	char infoLog[512];
	GLint success;

	GLuint shader = glCreateShader(type);
	std::string str_src = this->LoadShaderSource(fileName);
	const GLchar* src = str_src.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// Error Check
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Failed To Compiled Shader: " << fileName << std::endl;
		std::cout << infoLog << std::endl;
	}

	return shader;
}

void Shader::LinkProgram(GLuint vertexShader, GLuint geometryShader, GLuint FragmentShader)
{
	char infoLog[512];
	GLint success;

	this->ProgramID = glCreateProgram();

	glAttachShader(this->ProgramID, vertexShader);
	if (geometryShader)
		glAttachShader(this->ProgramID, geometryShader);
	glAttachShader(this->ProgramID, FragmentShader);

	glLinkProgram(this->ProgramID);

	glGetProgramiv(this->ProgramID, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(this->ProgramID, 512, NULL, infoLog);
		std::cout << "Failed to Link Program" << std::endl;
		std::cout << infoLog << std::endl;
	}

	glUseProgram(0);
}
