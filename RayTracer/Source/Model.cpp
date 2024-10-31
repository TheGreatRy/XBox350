#include "Model.h"
#include "Camera.h"
#include "Framebuffer.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Model::Load(const std::string& filename)
{
	// open file using ifstream (input file stream)
	std::ifstream stream(filename);
	// check if stream is_open
	if (!stream.is_open())
	{
		std::cerr << "Error loading object: " << filename << std::endl;
		return false;
	}

	vertices_t vertices;
	std::string line;
	while (std::getline(stream, line))
	{
		// read in vertex positions
		// https://cplusplus.com/reference/string/string/substr/
		if (line.substr(0,2) == "v ")
		{
			// read position of vertex
			
		
			std::istringstream sstream{ line.substr(2)};
			
			glm::vec3 position;

			//alt code
			/*int count = 0;
			for (std::string subline; std::getline(sstream, subline, ' ');)
			{
				if (count == 0) position.x = std::stof(subline); 
				if (count == 1) position.y = std::stof(subline);
				if (count == 2) position.z = std::stof(subline);
				count++;
			}*/

			sstream >> position.x;
			sstream >> position.y;
			sstream >> position.z;

			//add position to vertices vector
			vertices.push_back(position);
		}
		// read in faces (triangles)
		else if (line.substr(0, 2) == "f ")
		{
			// read face (triangle), index of vertex position in vertices array [1, 2, 3]
			std::istringstream sstream{ line.substr(2) };
			std::string str;
			// https://en.cppreference.com/w/cpp/string/basic_string/getline
			while (std::getline(sstream, str, ' '))
			{
				std::istringstream sstream(str);
				std::string indexString;

				// read each triangle index (position, normal, uv)
				size_t i = 0;
				unsigned int index[3] = { 0, 0, 0 }; // 0 = position, 1 = normal, 2 = uv
				while (std::getline(sstream, indexString, '/'))
				{
					if (!indexString.empty())
					{
						std::istringstream indexStream{ indexString };
						//stream indexStream into index[i]
						indexStream >> index[i];
					}
					i++;
				}

				// check if index 0 (position) is valid
				if (index[0])
				{
					// get vertex at index position
					// index is 1 based, need to subtract one for array
					glm::vec3 position = vertices[index[0]-1];
					//add position to m_vertices
					m_vertices.push_back(position);
				}
			}
		}
	}
	stream.close();

	return true;
}

bool Model::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
	// check cast ray with mesh triangles 
	/*for (size_t i = 0; i < m_vertices.size(); <skip by 3>)
	{
		Triangle triangle(<create triangle with the three vertex points>);
		if (triangle.Hit(ray, raycastHit, minDistance, maxDistance))
		{
			return true;
		}
	}*/

	return false;
}