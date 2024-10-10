#include "FrameBuffer.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Image.h"
#include <iostream>

Framebuffer::Framebuffer(const Renderer& renderer, int width, int height)
{
	m_width = width;
	m_height = height;
	m_pitch = width * sizeof(color_t);

	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!m_texture)
	{
		std::cerr << "Error creating SDL Texture: " << SDL_GetError() << std::endl;
	}
	m_buffer.resize(m_width * m_height);
}

Framebuffer::~Framebuffer()
{ 
	SDL_DestroyTexture(m_texture);
}

void Framebuffer::Update()
{
	SDL_UpdateTexture(m_texture,NULL,m_buffer.data(), m_pitch);
}

void Framebuffer::Clear(const color_t& color)
{
	std::fill(m_buffer.begin(), m_buffer.end(), color);
}

int Framebuffer::computeCode(int x, int y)
{
	x_max = m_width;
	y_max = m_height;

	// initialized as being inside
	int code = INSIDE;

	if (x < x_min)
	{
		// to the left of rectangle
		code |= LEFT;
	}
	else if (x > x_max)
	{
		// to the right of rectangle
		code |= RIGHT;
	}
	if (y < y_min)
	{
		// below the rectangle
		code |= BOTTOM;
	}
	else if (y > y_max)
	{
		// above the rectangle
		code |= TOP;
	}

	return code;
}

void Framebuffer::cohenSutherlandClip(int& x1, int& y1, int& x2, int& y2)
{
	// Compute region codes for P1, P2
	int code1 = computeCode(x1, y1);
	int code2 = computeCode(x2, y2);

	// Initialize line as outside the rectangular window
	bool accept = false;

	while (true) {
		if ((code1 == 0) && (code2 == 0)) {
			// If both endpoints lie within rectangle
			accept = true;
			break;
		}
		else if (code1 & code2) {
			// If both endpoints are outside rectangle,
			// in same region
			break;
		}
		else
		{
			// Some segment of line lies within therectangle
			int code_out;
			int x, y;

			// At least one endpoint is outside the
			// rectangle, pick it.
			if (code1 != 0)
			{
				code_out = code1;
			}
			else
			{
				code_out = code2;

			}

			// Find intersection point;
			// using formulas y = y1 + slope * (x - x1),
			// x = x1 + (1 / slope) * (y - y1)
			if (code_out & TOP) {
				// point is above the clip rectangle
				x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
				y = y_max;
			}
			else if (code_out & BOTTOM) {
				// point is below the rectangle
				x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
				y = y_min;
			}
			else if (code_out & RIGHT) {
				// point is to the right of rectangle
				y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
				x = x_max;
			}
			else if (code_out & LEFT) {
				// point is to the left of rectangle
				y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
				x = x_min;
			}

			// Now intersection point x, y is found
			// We replace point outside rectangle
			// by intersection point
			if (code_out == code1)
			{
				x1 = x;
				y1 = y;
				code1 = computeCode(x1, y1);
			}
			else
			{
				x2 = x;
				y2 = y;
				code2 = computeCode(x2, y2);
			}
		}
	}
	if (accept) {


		 /*
		std::cout << "Line accepted from " << x1 << ", "
			<< y1 << " to " << x2 << ", " << y2 << std::endl;
		// Here the user can add code to display the rectangle
		// along with the accepted (portion of) lines
		*/
	}
	//else std::cout << "Line rejected" << std::endl;


}

void Framebuffer::DrawImage(int x, int y, int w, int h, const Image& image)
{
	w = image.m_width;
	h = image.m_height;
	
	// check if off-screen
	if (x + w < 0 || y + h < 0 || x >= m_width || y >= m_height) return;

	// iterate through image y
	for (int iy = 0; iy < image.m_height; iy++)
	{
		// set screen y 
		int sy = y + iy;
		// check if off-screen, don't draw if off-screen

		if (sy < 0 || sy >= m_height) continue;

		// iterate through image x
		for (int ix = 0; ix < image.m_width; ix++)
		{
			// set screen x
			int sx = x + ix;
			// check if off-screen, don't draw if off-screen
			if (sx < 0 || sx >= m_width) continue;

			//ix -> m-width, loops
			color_t color = image.m_buffer[ix + iy * image.m_width];
			// check alpha, if 0 don't draw
			if (color.a == 0) return ;
			// set buffer to color
			m_buffer[sx + sy * m_width] = color;
		}
	}
}

void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
	if (x >= m_width || x < 0 || y >= m_height || y < 0) return;
	m_buffer[x + y * m_width] = color;
}

void Framebuffer::DrawRect(int x, int y, int w, int h, const color_t& color)
{
	/*for (int sy = y; sy < y + h; sy++)
	{
		if (y < 0) h = h + y;
		if (y + h > m_width) h = h - y;

		for (int sx = x; sx < x + w; sx++)
		{
			if (x < 0) w = w + x;
			if (x + w > m_width) w = w - x;
			m_buffer[sx + sy * m_width] = color;
		}
	}*/

}

void Framebuffer::DrawLineSlope(int x1, int y1, int x2, int y2, const color_t& color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dx == 0)
	{
		if (y1 > y2) std::swap(y1, y1);
		for (int y = y1; y < y2; y++)
		{
			m_buffer[x1 + y * m_width] = color;
		}
	}
	else
	{ 
	
		float m = dy / (float)dx;
	
		float b = y1 - (m * x1);
	
		if (std::abs(dx) > std::abs(dy))
		{
			// run > rise
			for (int x = x1; x < x2; x++)
			{
				// y = mx + b
				int y = (int)round((m * x) + b);
				m_buffer[x + y * m_width] = color;
			}
		}
		else
		{
			// rise > run
			for (int y = y1; y < y2; y++)
			{
				// x = y - b / m
				int x = (int)round((y - b) / m);
				m_buffer[x + y * m_width] = color;
			}
		}
	}
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	bool steep = (std::abs(dy) > std::abs(dx));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	dx = x2 - x1;
	dy = std::abs(y2 - y1);

	

	int error = dx / 2;
	int ystep = (y1 < y2) ? 1 : -1;

	for (int x = x1, y = y1; x <= x2; x++)
	{
		cohenSutherlandClip(x1, y1, x2, y2);

		(steep) ? DrawPoint(y, x, color) : DrawPoint(x, y, color);

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}

void Framebuffer::DrawCircle(int xc, int yc, int radius, const color_t& color)
{
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;
	DrawPoint(xc + x, yc + y, color);
	DrawPoint(xc - x, yc + y, color);
	DrawPoint(xc + x, yc - y, color);
	DrawPoint(xc - x, yc - y, color);
	DrawPoint(xc + y, yc + x, color);
	DrawPoint(xc - y, yc + x, color);
	DrawPoint(xc + y, yc - x, color);
	DrawPoint(xc - y, yc - x, color);
	while (y >= x)
	{
		// check for decision parameter
		// and correspondingly 
		// update d, y
		if (d > 0) {
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;

		// Increment x after updating decision parameter
		x++;

		// Draw the circle using the new coordinates
		DrawPoint(xc + x, yc + y, color);
		DrawPoint(xc - x, yc + y, color);
		DrawPoint(xc + x, yc - y, color);
		DrawPoint(xc - x, yc - y, color);
		DrawPoint(xc + y, yc + x, color);
		DrawPoint(xc - y, yc + x, color);
		DrawPoint(xc + y, yc - x, color);
		DrawPoint(xc - y, yc - x, color);
	}

}

void Framebuffer::DrawLinearCurve(int x1, int y1, int x2, int y2, const color_t& color)
{
	float dt = 1 / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++)
	{
		int sx1 = Lerp(x1, x2, t1);
		int sy1 = Lerp(y1, y2, t1);

		float t2 = t1 + dt;

		int sx2 = Lerp(x1, x2, t2);
		int sy2 = Lerp(y1, y2, t2);
		
		t1 += dt;
		
		DrawLine(sx1, sy1, sx2, sy2, color);

	}
}

void Framebuffer::DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	float dt = 1 / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++)
	{
		int sx1, sy1;

		QuadraticPoint(x1, y1, x2, y2, x3, y3, t1, sx1, sy1);
		float t2 = t1 + dt;
		
		int sx2, sy2;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t2, sx2, sy2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);

	}
}

void Framebuffer::DrawCubicCurve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, const color_t& color)
{
	float dt = 1 / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++)
	{
		int sx1, sy1;

		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t1, sx1, sy1);
		float t2 = t1 + dt;

		int sx2, sy2;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t2, sx2, sy2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

