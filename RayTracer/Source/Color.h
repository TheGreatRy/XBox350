#pragma once
#include "MathUtils.h"
#include <SDL.h>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>

using color_t = SDL_Color;
using color3_t = glm::vec3;
using color4_t = glm::vec4;

inline color_t ColorConvert(const color4_t& color4) 
{
	color_t color;
	color.r = (uint8_t)(Clamp(color4.r, 0.0f, 1.0f) * 255);
	color.g = (uint8_t)(Clamp(color4.g, 0.0f, 1.0f) * 255);
	color.b = (uint8_t)(Clamp(color4.b, 0.0f, 1.0f) * 255);
	color.a = 255;

	return color;
}
inline color4_t ColorConvert(const color_t& color)
{
	color4_t color4;
	color4.r = color.r / 255.0f;
	color4.g = color.g / 255.0f;
	color4.b = color.b / 255.0f;
	color4.a = 255;

	return color4;
}

inline color_t ColorConvert(const color3_t& color3)
{
	color_t color;
	color.r = color3.r / 255.0f;
	color.g = color3.g / 255.0f;
	color.b = color3.b / 255.0f;
	color.a = 255;

	return color;
}

enum class BlendMode
{
	NORMAL,
	ALPHA,
	ADD,
	MULTIPLY
};

 color_t NormalBlend(const color_t& source, const color_t& dest);
 color_t ColorBlend(const color_t& source, const color_t& dest);
 color_t AlphaBlend(const color_t& source, const color_t& dest);
 color_t AddBlend(const color_t& source, const color_t& dest);
 color_t MultiplyBlend(const color_t& source, const color_t& dest);
 
 void SetBlendMode(BlendMode blendMode);