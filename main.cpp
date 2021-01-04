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

std::vector<Vertex> loadOBJ(const char* file_name)
{
	//Vertex portions
	std::vector<glm::fvec3> vertex_positions;
	std::vector<glm::fvec2> vertex_texcoords;
	std::vector<glm::fvec3> vertex_normals;

	//Face vectors
	std::vector<GLint> vertex_position_indicies;
	std::vector<GLint> vertex_texcoord_indicies;
	std::vector<GLint> vertex_normal_indicies;

	//Vertex array
	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;

	//File open error check
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	//Read one line at a time
	while (std::getline(in_file, line))
	{
		//Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "s")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else if (prefix == "v") //Vertex position
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt")
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		else if (prefix == "vn")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> temp_glint)
			{
				//Pushing indices into correct arrays
				if (counter == 0)
					vertex_position_indicies.push_back(temp_glint);
				else if (counter == 1)
					vertex_texcoord_indicies.push_back(temp_glint);
				else if (counter == 2)
					vertex_normal_indicies.push_back(temp_glint);

				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}
		}
		else
		{

		}
	}

	//Build final vertex array (mesh)
	vertices.resize(vertex_position_indicies.size(), Vertex());

	float color = 1.0f / vertices.size();
	//Load in all indices
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
		vertices[i].color = glm::vec3(color * i, color * i, color * i);
		vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
	}

	//DEBUG
	std::cout << "Nr of vertices: " << vertices.size() << "\n";

	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";
	return vertices;
}


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

	std::vector<Vertex> object = loadOBJ("Tree.obj");
	std::vector<Vertex> sphere = loadOBJ("Moon 2K.obj");

	std::vector<GLuint> indices;

	// Create Shader, Object and Camera 
	Object object1(object, indices);
	Object object2(object, indices);
	Object object3(object, indices);
	Object object4(object, indices);
	Object object5(object, indices);
	Object object6(object, indices);
	Object moon(sphere, indices);

	object1.Move(glm::vec3(10.0f, 0.0f, 10));
	object2.Move(glm::vec3(14.0f, 0.0f, 13.0f));
	object3.Move(glm::vec3(15.0f, 0.0f, 12.0f));
	object4.Move(glm::vec3(11.0f, 0.0f, 11.0f));
	object5.Move(glm::vec3(12.0f, 0.0f, 15.0f));
	
	window.CreateObject(object1);
	window.CreateObject(object2);
	window.CreateObject(object3);
	window.CreateObject(object4);
	window.CreateObject(object5);
	window.CreateObject(object6);
	// window.CreateObject(moon);

	// equzlize the hertz of the frame and monitor
	glfwSwapInterval(1);

	while (1)
	{
		window.Update();
	}
}