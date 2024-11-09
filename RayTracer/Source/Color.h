#pragma once
#include "MathUtils.h"
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/color_space.hpp>
#include <SDL.h>
#include <vector>
#include <algorithm>

using color_t = SDL_Color;
using color3_t = glm::vec3;
using color4_t = glm::vec4;

inline color3_t HSVtoRGB(const glm::vec3& hsv)
{
	return glm::rgbColor(hsv);
}

inline color3_t HSVtoRGB(float hue, float saturation, float value)
{
	return glm::rgbColor(color3_t{hue, saturation, value});
}

inline float LinearToGamma(float linear)
{
	if (linear > 0) return std::sqrt(linear);
	return 0;
}

inline color_t ColorConvert(const color4_t& color4) 
{
	color_t color;
	color.r = (uint8_t)(Clamp(LinearToGamma(color4.r), 0.0f, 1.0f) * 255);
	color.g = (uint8_t)(Clamp(LinearToGamma(color4.g), 0.0f, 1.0f) * 255);
	color.b = (uint8_t)(Clamp(LinearToGamma(color4.b), 0.0f, 1.0f) * 255);
	color.a = 255;

	return color;
}

inline color_t ColorConvert(const color3_t& color3)
{
	color_t color;
	color.r = (uint8_t)(Clamp(LinearToGamma(color3.r), 0.0f, 1.0f) * 255);
	color.g = (uint8_t)(Clamp(LinearToGamma(color3.g), 0.0f, 1.0f) * 255);
	color.b = (uint8_t)(Clamp(LinearToGamma(color3.b), 0.0f, 1.0f) * 255);
	color.a = 255;

	return color;
}

inline color4_t ColorConvert(const color_t& color)
{
	color4_t color4;
	color4.r = Clamp(color.r / 255.0f, 0.0f, 255.0f);
	color4.g = Clamp(color.g / 255.0f, 0.0f, 255.0f);
	color4.b = Clamp(color.b / 255.0f, 0.0f, 255.0f);
	color4.a = 255;

	return color4;
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