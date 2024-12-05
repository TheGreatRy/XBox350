#pragma once
#include "Color.h"
#include "glm/glm.hpp"

struct fragment_input_t
{
	glm::vec3 position;
	glm::vec3 normal;
	color4_t color{ 1 };
};

class FragmentShader
{
public:
	static color4_t Process(const fragment_input_t& fragment);
};