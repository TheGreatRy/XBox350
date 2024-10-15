#pragma once
#include "Color.h"
#include <SDL.h>
#include <vector>

class Framebuffer
{
public:
	Framebuffer(const class Renderer& renderer, int width, int height);
	~Framebuffer();

	void Update();
	void Clear(const color_t& color);

	void DrawImage(int x, int y, int w, int h, const class Image& image);

	void DrawPoint(int x, int y, const color_t& color);
	void DrawPointClip(int x, int y, const color_t& color);
	void DrawRect(int x, int y, int w, int h, const color_t& color);
	void DrawLineSlope(int x1, int y1, int x2, int y2, const color_t& color);
	void DrawLine(int x1, int y1, int x2, int y2, const color_t& color);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color);
	void DrawCircle(int xc, int yc, int radius, const color_t& color);

	void DrawLinearCurve(int x1, int y1, int x2, int y2, const color_t& color);
	void DrawQuadraticCurve(int x1, int y1, int x2, int y2,int x3, int y3, const color_t& color);
	void DrawCubicCurve(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4, const color_t& color);


	friend class Renderer;

private:
	const int INSIDE = 0; // 0000
	const int LEFT = 1; // 0001
	const int RIGHT = 2; // 0010
	const int BOTTOM = 4; // 0100
	const int TOP = 8; // 1000

	int x_max;
	int y_max;
	const int x_min = 0;
	const int y_min = 0;

	int computeCode(int x, int y);
	void cohenSutherlandClip(int& x1, int& y1, int& x2, int& y2);
	
public:
	int m_width{ 0 };
	int m_height{ 0 };
	int m_pitch{ 0 };
	SDL_Texture* m_texture{ nullptr };
	std::vector<color_t> m_buffer;
};