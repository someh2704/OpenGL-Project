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
#include "Light.h"


class Window {
public:
	Window(int width, int height);
	~Window();
	void Update();
	void CreateObject(Object& object);
	void UpdateKeyboard();
	void UpdateMouse();
private:
	void initWindow(int width, int height);
	void initShader();
	void initCamera(glm::vec3 pos = glm::vec3(3,3,10), glm::vec3 view = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 0));
	void initLight();
	void pprintFPS();



	int framebufferWidth, framebufferHeight;
	GLFWwindow* window;
	Shader* objectShader;
	Shader* lightShader;
	std::vector<Object> objects;
	Camera* camera;
	Light* light;

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