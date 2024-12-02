#include "Model.h"
#include "Shader.h"
#include "Framebuffer.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Model::Draw()
{
	Shader::Draw(m_vb);
}

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

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::string line;
	while (std::getline(stream, line))
	{
		// read in vertex positions
		// https://cplusplus.com/reference/string/string/substr/
		if (line.substr(0,2) == "v ")
		{
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
		// read in vertex normals
		else if (line.substr(0,3) == "vn ")
		{
			std::istringstream sstream{ line.substr(3)};
			
			glm::vec3 normal;

			sstream >> normal.x;
			sstream >> normal.y;
			sstream >> normal.z;

			//add position to vertices vector
			normals.push_back(normal);
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
					//add vertex to model vertices
					
					vertex_t vertex;
					vertex.position = vertices[index[0] - 1];
					vertex.normal = (index[2]) ? normals[index[2] - 1] : glm::vec3{ 1 };

					m_vb.push_back(vertex);
				}
			}
		}
	}
	stream.close();

	return true;
}
