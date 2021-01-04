#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "Shader.h"
#include "Object.h"
#include "Camera.h"
#include "Window.h"
#include <vector>

#include <iostream>

#include "Debug.h"


int main() {
	Window window(1600, 900);
	
	// Cube Vertex and Color
	std::vector<Vertex> vertex{
		Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.583f,  0.771f,  0.014f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.609f,  0.115f,  0.436f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.327f,  0.483f,  0.844f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.822f,  0.569f,  0.201f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.435f,  0.602f,  0.223f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.310f,  0.747f,  0.185f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.597f,  0.770f,  0.761f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.559f,  0.436f,  0.730f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.359f,  0.583f,  0.152f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.483f,  0.596f,  0.789f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.559f,  0.861f,  0.639f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.195f,  0.548f,  0.859f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.014f,  0.184f,  0.576f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.771f,  0.328f,  0.970f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.406f,  0.615f,  0.116f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.676f,  0.977f,  0.133f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.971f,  0.572f,  0.833f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.140f,  0.616f,  0.489f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.997f,  0.513f,  0.064f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.945f,  0.719f,  0.592f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.543f,  0.021f,  0.978f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.279f,  0.317f,  0.505f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.167f,  0.620f,  0.077f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.347f,  0.857f,  0.137f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.055f,  0.953f,  0.042f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.714f,  0.505f,  0.345f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.783f,  0.290f,  0.734f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.722f,  0.645f,  0.174f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.302f,  0.455f,  0.848f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.225f,  0.587f,  0.040f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.517f,  0.713f,  0.338f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.053f,  0.959f,  0.120f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.393f,  0.621f,  0.362f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.673f,  0.211f,  0.457f), glm::vec3(1.0f) },
		Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.820f,  0.883f,  0.371f), glm::vec3(1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.982f,  0.099f,  0.879f), glm::vec3(1.0f) },
	};
	/*
	std::vector<Vertex> vertex{
		Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f)}
	};
	*/
	/*
	std::vector<Vertex> object{
		Vertex{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f), glm::vec3( 0.0f,  0.0f, -1.0f)},
		Vertex{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f), glm::vec3(-1.0f, -0.0f, -0.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(1.0f), glm::vec3(-0.0f, -0.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f), glm::vec3(-0.0f,  0.0f,  1.0f)},
		Vertex{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f), glm::vec3( 1.0f, -0.0f,  0.0f)},
		Vertex{glm::vec3(0.99f,  1.0f,  1.0f), glm::vec3(1.0f), glm::vec3( 1.0f,  0.0f,  0.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(1.0f), glm::vec3( 0.0f,  1.0f, -0.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(1.0f), glm::vec3(-0.0f, -1.0f,  0.0f)},

	};
	*/

	std::vector<GLuint> indices;

	// Create Shader, Object and Camera 
	Object object1(vertex, indices);
	Object object2(vertex, indices);
	Object object3(vertex, indices);
	Object object4(vertex, indices);
	Object object5(vertex, indices);


	object1.Move(glm::vec3(10.0f, 0.0f, 10));
	object2.Move(glm::vec3(25.0f, 0.0f, 25.0f));
	object3.Move(glm::vec3(40.0f, 0.0f, 40.0f));
	object4.Move(glm::vec3(70.0f, 0.0f, 70.0f));
	
	window.CreateObject(object1);
	window.CreateObject(object2);
	window.CreateObject(object3);
	window.CreateObject(object4);
	// window.CreateObject(object5);

	// equzlize the hertz of the frame and monitor
	glfwSwapInterval(1);

	while (1)
	{
		window.Update();
	}
}