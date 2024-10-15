#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>

using color_t = SDL_Color;

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