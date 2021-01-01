#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "Shader.h"
#include "Object.h"
#include <vector>

#include <iostream>

#include "Debug.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
	// glfwInit
	if (!glfwInit()) {
		cout << "glfwInit Failed" << endl;
		std::exit(EXIT_FAILURE);
	}

	// Window Setting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(1600, 900, "OpenGL Project", NULL, NULL);

	if (!window) {
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	//Make Context
	glfwMakeContextCurrent(window);

	// glew Init
	GLenum errorCode = glewInit();
	if (errorCode != GLEW_OK) {
		cout << "Failed to glewInit" << glewGetErrorString(errorCode) << endl;

		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	// Machine Version
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;



	vector<Vertex> vertex{
		Vertex{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
		Vertex{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
		Vertex{ glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }
	};
	
	//vertex.push_back(Vertex{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) });
	//vertex.push_back(Vertex{ glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) });
	//vertex.push_back(Vertex{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) });


	vector<GLuint> indices;

	Shader* shader = new Shader(3, 3, "VertexShader.vertexshader", "FragmentShader.fragmentshader");
	Object object(vertex, indices);

	glfwSwapInterval(1);
	double lastTime = glfwGetTime();
	int numOfFrames = 0;
	int count = 0;

	while (!glfwWindowShouldClose(window)) {

		// Check FPS
		double currentTime = glfwGetTime();
		numOfFrames++;
		if (currentTime - lastTime >= 1.0) {

			printf("%f ms/frame  %d fps \n", 1000.0 / double(numOfFrames), numOfFrames);
			numOfFrames = 0;
			lastTime = currentTime;
		}

		// Clear Window
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw Line
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


		// Draw Triangles
		object.render(shader);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		count++;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete System
	glUseProgram(0);
	glBindVertexArray(0);

	glfwTerminate();

	std::exit(EXIT_SUCCESS);
}