#include "Window.h"
#include "Debug.h"
enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };
Window::Window(int width, int height)
{
	// glfwInit
	if (!glfwInit()) {
		std::cout << "glfwInit Failed" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	this->initWindow(width, height);

	framebufferWidth = width;
	framebufferHeight = height;

	this->lastMouseX = this->mouseX = this->framebufferWidth / 2;
	this->lastMouseY = this->mouseY = this->framebufferHeight / 2;

	// glfwInit
	GLenum errorCode = glewInit();
	if (errorCode != GLEW_OK) {
		std::cout << "Failed to glewInit" << glewGetErrorString(errorCode) << std::endl;

		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	this->initShader();
	this->initCamera();
	this->initLight();
	glfwSetCursorPos(this->window, this->framebufferWidth / 2, this->framebufferHeight / 2);
}

Window::~Window()
{
	delete[] window;
	delete[] objectShader;
	delete[] lightShader;
	delete[] camera;
	delete[] light;
}

void Window::CreateObject(Object& object)
{
	this->objects.push_back(object);
}

void Window::UpdateKeyboard()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
		this->camera->move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
		this->camera->move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
		this->camera->move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
		this->camera->move(this->dt, RIGHT);
	}
}


void Window::initWindow(int width, int height)
{
	// Window Setting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	this->window = glfwCreateWindow(width, height, "OpenGL Project", NULL, NULL);

	if (!this->window) {
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	// Make Context
	glfwMakeContextCurrent(this->window);
}

void Window::initShader()
{
	this->objectShader = new Shader(3, 3, "Object.vertexshader", "Object.fragmentshader");
	// this->lightShader = new Shader(3, 3, "Light.vertexshader", "Light.fragmentshader");
}

void Window::initCamera(glm::vec3 pos, glm::vec3 view, glm::vec3 up)
{
	camera = new Camera(pos, view, up);
}

void Window::initLight()
{
	this->light = new Light(glm::vec3(10.0f), glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f));
}

void Window::pprintFPS()
{
	if (dt >= 1.0) {

		printf("%f ms/frame  %d fps \n", 1000.0 / double(this->numOfFrames), this->numOfFrames);
		this->numOfFrames = 0;
		this->lastTime = this->currentTime;
	}
}

void Window::Update()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);
	glfwSetCursorPos(this->window, this->framebufferWidth / 2, this->framebufferHeight / 2);
	
	if (glfwWindowShouldClose(this->window)) {
		glUseProgram(0);
		glBindVertexArray(0);

		glfwTerminate();
		std::exit(EXIT_SUCCESS);
	}

	this->currentTime = glfwGetTime();
	this->numOfFrames++;
	this->pprintFPS();

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
	this->UpdateKeyboard();
	float offsetX = this->mouseX - this->lastMouseX;
	float offsetY = this->mouseY - this->lastMouseY;
	this->dt = static_cast<float>(this->currentTime) - static_cast<float>(this->lastTime);
	this->camera->updateMouseInput(this->dt, offsetX, offsetY);

	this->light->setPosition(this->camera->getPosition());

	for (auto& object: this->objects) {
		this->objectShader->Use();
		glm::mat4 ProjectionMatrix = camera->getProjection();
		glm::mat4 ViewMatrix = camera->getViewMatirx();
		glm::vec3 cameraPosition = camera->getPosition();

		this->objectShader->setMatrix4fv(ProjectionMatrix, "ProjectionMatrix");
		this->objectShader->setMatrix4fv(ViewMatrix, "ViewMatrix");
		this->objectShader->setVec3(cameraPosition, "cameraPosition");
		this->light->sendToShader(this->objectShader);


		object.render(objectShader);
	}

	glfwSwapBuffers(window);
}