#pragma once
#include "Color.h"

class Material
{
public:
	Material() = default;
	Material(const color3_t& color3):
		m_color{color3}
	{}
	color3_t& GetColor() { return m_color; }

private:
	color3_t m_color;

};