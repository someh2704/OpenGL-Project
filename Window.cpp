#include "Window.h"
#include "Debug.h"
enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };
Window::Window(int width, int height, const char* vertexFilePath, const char* fragmentFilePath)
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

	this->initShader(vertexFilePath, fragmentFilePath);
	this->initCamera();
	glfwSetCursorPos(this->window, this->framebufferWidth / 2, this->framebufferHeight / 2);
}

Window::~Window()
{
	delete[] window;
	delete[] shader;
	delete[] camera;
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

void Window::initShader(const char* vertexFilePath, const char* fragmentFilePath)
{
	shader = new Shader(3, 3, vertexFilePath, fragmentFilePath);
}

void Window::initCamera(glm::vec3 pos, glm::vec3 view, glm::vec3 up)
{
	camera = new Camera(pos, view, up);
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

	for (int i = 0; i < this->objects.size(); i++) {
		this->shader->Use();
		glm::mat4 ProjectionMatrix = camera->getProjection();
		glm::mat4 ViewMatrix = camera->getViewMatirx();

		shader->setMatrix4fv(ProjectionMatrix, "ProjectionMatrix");
		shader->setMatrix4fv(ViewMatrix, "ViewMatrix");

		this->objects[i].render(shader);
		switch (i)
		{
		case 0:
			this->objects[i].Move(glm::vec3(0.01f, 0.0f, 0.0f));
			this->objects[i].Rotate(glm::vec3(1.0f, 0.0f, 1.0));
			break;
		case 1:
			this->objects[i].Move(glm::vec3(0.0f, 0.01f, 0.0f));
			this->objects[i].Rotate(glm::vec3(-1.0f, 0.0f, -1.0));
			break;
		case 2:
			this->objects[i].Move(glm::vec3(0.0f, 0.0f, 0.01f));
			this->objects[i].Rotate(glm::vec3(0.0f, 1.0f, 0.0f));
		default:
			break;
		}
		
	}

	glfwSwapBuffers(window);
}