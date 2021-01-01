#include "Debug.h"

void pprint(std::vector<Vertex> vertex)
{
	std::cout << "Postion" << std::endl;
	std::cout << "1: " << vertex[0].position.x << " " << vertex[0].position.y << " " << vertex[0].position.z << std::endl;
	std::cout << "2: " << vertex[1].position.x << " " << vertex[1].position.y << " " << vertex[1].position.z << std::endl;
	std::cout << "3: " << vertex[2].position.x << " " << vertex[2].position.y << " " << vertex[2].position.z << std::endl;
	
	std::cout << "Color" << std::endl;
	std::cout << "1: " << vertex[0].color.x << " " << vertex[0].color.y << " " << vertex[0].color.z << std::endl;
	std::cout << "2: " << vertex[1].color.x << " " << vertex[1].color.y << " " << vertex[1].color.z << std::endl;
	std::cout << "3: " << vertex[2].color.x << " " << vertex[2].color.y << " " << vertex[2].color.z << std::endl;
}
