#include "PostProcess.h"
#include "MathUtils.h"
#include <algorithm>
#include <cmath>

void PostProcess::Invert(std::vector<color_t>& buffer)
{
	/*for (auto& color : buffer)
	{
		color.r = 255 - color.r;
		color.g = 255 - color.g;
		color.b = 255 - color.b;
	}*/

	std::for_each(buffer.begin(), buffer.end(), [](auto& color)
		{
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
		});
}

void PostProcess::Monochrome(std::vector<color_t>& buffer)
{
	std::for_each(buffer.begin(), buffer.end(), [](auto& color)
		{
			uint8_t avg = static_cast<uint8_t>((color.r + color.g + color.b) / 3);
			color.r = avg;
			color.g = avg;
			color.b = avg;
		});
}

void PostProcess::Brightness(std::vector<color_t>& buffer, int brightness)
{
	std::for_each(buffer.begin(), buffer.end(), [brightness](auto& color)
		{
			color.r = static_cast<uint8_t>(Clamp(color.r + brightness, 0, 255));
			color.g = static_cast<uint8_t>(Clamp(color.g + brightness, 0, 255));
			color.b = static_cast<uint8_t>(Clamp(color.b + brightness, 0 ,255));
		});
}

void PostProcess::ColorBalance(std::vector<color_t>& buffer, int ro, int go, int bo)
{
	std::for_each(buffer.begin(), buffer.end(), [ro, go, bo](auto& color)
		{
			color.r = static_cast<uint8_t>(Clamp(color.r + ro, 0, 255));
			color.g = static_cast<uint8_t>(Clamp(color.g + go, 0, 255));
			color.b = static_cast<uint8_t>(Clamp(color.b + bo, 0, 255));
		});
}

void PostProcess::Noise(std::vector<color_t>& buffer, uint8_t noise)
{
	std::for_each(buffer.begin(), buffer.end(), [noise](auto& color)
	{
		int offset = (rand() % ((noise * 2) + 1)) - noise;
		
		color.r = static_cast<uint8_t>(Clamp(color.r + offset, 0, 255));
		color.g = static_cast<uint8_t>(Clamp(color.g + offset, 0, 255));
		color.b = static_cast<uint8_t>(Clamp(color.b + offset, 0, 255));
	});

}

void PostProcess::Threshold(std::vector<color_t>& buffer, uint8_t threshold)
{
	std::for_each(buffer.begin(), buffer.end(), [threshold](auto& color)
		{
			(color.r >= threshold || color.g >= threshold || color.b >= threshold)
				? color = { 255,255,255,255 } : color = { 0,0,0,0 };
				
		});
}

void PostProcess::Posterize(std::vector<color_t>& buffer, uint8_t levels)
{
	uint8_t level = 255 / levels ;

	std::for_each(buffer.begin(), buffer.end(), [levels, level](auto& color)
		{
			color.r = static_cast<uint8_t>(Clamp(color.r / level * level, 0, 255));
			color.g = static_cast<uint8_t>(Clamp(color.g / level * level, 0, 255));
			color.b = static_cast<uint8_t>(Clamp(color.b / level * level, 0, 255));

		});

}

void PostProcess::BoxBlur(std::vector<color_t>& buffer, int width, int height)
{
	std::vector<color_t> source = buffer;
	int k[3][3] =
	{
		{1,1,1},
		{1,1,1},
		{1,1,1}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		// % 5 : 1 2 3 4 5 6 7 8 9 10
		//reman: 1 2 3 4 0 1 2 3 4 0
		int x = i % width;
		int y = i / width;

		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(ix + x - 1) + (iy + y - 1) * width];
				int weight = k[iy][ix];

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}

		}
		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(r / 9);
		color.g = static_cast<uint8_t>(g / 9);
		color.b = static_cast<uint8_t>(b / 9);

	}

}

void PostProcess::GaussBlur(std::vector<color_t>& buffer, int width, int height)
{
	std::vector<color_t> source = buffer;
	int k[3][3] =
	{
		{1,2,1},
		{2,4,2},
		{1,2,1}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		// % 5 : 1 2 3 4 5 6 7 8 9 10
		//reman: 1 2 3 4 0 1 2 3 4 0
		int x = i % width;
		int y = i / width;

		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(ix + x - 1) + (iy + y - 1) * width];
				int weight = k[iy][ix];

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}

		}
		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(r / 16);
		color.g = static_cast<uint8_t>(g / 16);
		color.b = static_cast<uint8_t>(b / 16);

	}
}

void PostProcess::Sharpen(std::vector<color_t>& buffer, int width, int height)
{
	std::vector<color_t> source = buffer;
	int k[3][3] =
	{
		{0,-1,0},
		{-1,5,-1},
		{0,-1,0}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		// % 5 : 1 2 3 4 5 6 7 8 9 10
		//reman: 1 2 3 4 0 1 2 3 4 0
		int x = i % width;
		int y = i / width;

		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(ix + x - 1) + (iy + y - 1) * width];
				int weight = k[iy][ix];

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}

		}
		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(Clamp(r, 0, 255));
		color.g = static_cast<uint8_t>(Clamp(g, 0, 255));
		color.b = static_cast<uint8_t>(Clamp(b, 0, 255));

	}
}

void PostProcess::Edge(std::vector<color_t>& buffer, int width, int height, int threshold)
{
	std::vector<color_t> source = buffer;
	int hk[3][3] =
	{
		{1,0,-1},
		{2,0,-2},
		{1,0,-1}
	};
	
	int vk[3][3] =
	{
		{1,2,1},
		{0,0,0},
		{-1,-2,-1}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		// % 5 : 1 2 3 4 5 6 7 8 9 10
		//reman: 1 2 3 4 0 1 2 3 4 0
		int x = i % width;
		int y = i / width;

		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int h = 0;
		int v = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(ix + x - 1) + (iy + y - 1) * width];
				
				h += pixel.r * hk[iy][ix];
				v += pixel.r * vk[iy][ix];
			}

		} 
		int m = std::sqrt((h * h) + (v * v));
		m = (m >= threshold) ? m : 0;
		uint8_t c = Clamp(m, 0, 255);

		color_t& color = buffer[i];
		color.r = c;
		color.g = c;
		color.b = c;

	}
}
