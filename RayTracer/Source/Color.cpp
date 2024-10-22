#include "Color.h"

color_t(*blend_func)(const color_t& source, const color_t& dest);

void SetBlendMode(BlendMode blendMode)
{
	switch (blendMode)
	{
	case BlendMode::NORMAL:
		blend_func = NormalBlend;
		break;
	case BlendMode::ALPHA:
		blend_func = AlphaBlend;
		break;
	case BlendMode::ADD:
		blend_func = AddBlend;
		break;
	case BlendMode::MULTIPLY:
		blend_func = MultiplyBlend;
		break;
	default:
		break;

	}
}

color_t NormalBlend(const color_t& source, const color_t& dest)
{
	return source;
}

color_t ColorBlend(const color_t& source, const color_t& dest)
{
	return blend_func(source, dest);
}

color_t AlphaBlend(const color_t& source, const color_t& dest)
{
	uint8_t alp = source.a;
	uint8_t iAlp = 255 - source.a;

	color_t color;
	color.r = (source.r * alp + dest.r * iAlp) >> 8;
	color.g = (source.g * alp + dest.g * iAlp) >> 8;
	color.b = (source.b * alp + dest.b * iAlp) >> 8;
	color.a = source.a;

	return color;
}

color_t AddBlend(const color_t& source, const color_t& dest)
{
	color_t color;
	color.r = std::min(source.r + dest.r, 255);
	color.g = std::min(source.g + dest.g, 255);
	color.b = std::min(source.b + dest.b, 255);
	color.a = source.a;

	return color;
}

color_t MultiplyBlend(const color_t& source, const color_t& dest)
{
	

	color_t color;
	color.r = (source.r * dest.r) >> 8;
	color.g = (source.g * dest.g) >> 8;
	color.b = (source.b * dest.b) >> 8;
	color.a = source.a;

	return color;
}
