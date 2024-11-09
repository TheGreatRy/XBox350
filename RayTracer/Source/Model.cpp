#include "Model.h"
#include "Framebuffer.h"
#include "Sphere.h"
#include "Triangle.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Model::Update()
{
	//transform vertices
	for (size_t i = 0; i < m_local_vertices.size(); i++)
	{
		m_vertices[i] = m_transform * glm::vec4{ m_local_vertices[i], 1 };
	}
	// get center point of transformed vertices
	m_center = glm::vec3{ 0 };
	for (auto& vertex : m_vertices)
	{
		//add vertex to center
		m_center += vertex ;
	}
	m_center /= (float) m_vertices.size();

	//After that, compute the radius by getting the length of each vertex from the center. Store the highest radius.

	// get radius of transformed vertices
	m_radius = 0;
	for (auto& vertex : m_vertices)
	{
		float radius = glm::length(vertex - m_center);
		m_radius = glm::max(radius, m_radius);
	}

	
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
					m_local_vertices.push_back(position);
				}
			}
		}
	}
	m_vertices.resize(m_local_vertices.size());
	stream.close();

	return true;
}

bool Model::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
	// check cast ray with mesh triangles 
	for (size_t i = 0; i < m_vertices.size(); i += 3)
	{
		//check for bounding sphere raycast
		float t;
		if (!Sphere::Raycast(ray, m_center, m_radius, minDistance, maxDistance, t)) return false;

		if (Triangle::Raycast(ray, m_vertices[i], m_vertices[i + 1], m_vertices[i + 2], minDistance, maxDistance, t))
		{
			// set raycast hit
			raycastHit.distance = t;
			raycastHit.point = ray.at(t);

			// set edges of the triangle
			glm::vec3 edge1 = m_vertices[i + 1] - m_vertices[i];
			glm::vec3 edge2 = m_vertices[i + 2] - m_vertices[i];

			//<calculate triangle normal, vector perpendicular to edge1 and edge 2, normalize vector>
			raycastHit.normal = glm::normalize(Cross(edge1, edge2));
			raycastHit.material = GetMaterial();
			return true;
		}
	}

	return false;
}