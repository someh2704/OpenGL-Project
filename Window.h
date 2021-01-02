#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Vertex.h"
#include "Camera.h"
#include "Object.h"
#include "Shader.h"


class Window {
public:
	Window(int width, int height, const char* vertexFilePath, const char* fragmentFilePath);
	~Window();
	void Update();
	void CreateObject(Object& object);
	void UpdateKeyboard();
	void UpdateMouse();
private:
	void initWindow(int width, int height);
	void initShader(const char* vertexFilePath, const char* fragmentFilePath);
	void initCamera(glm::vec3 pos = glm::vec3(3,3,10), glm::vec3 view = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 0));
	void pprintFPS();



	int framebufferWidth, framebufferHeight;
	GLFWwindow* window;
	Shader* shader;
	std::vector<Object> objects;
	Camera* camera;

	double mouseX;
	double mouseY;
	double lastMouseX;
	double lastMouseY;

	bool firstMouse;

	double lastTime;
	double currentTime;
	float dt;
	int numOfFrames;
};