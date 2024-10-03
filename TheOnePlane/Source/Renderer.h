#pragma once
#include <SDL.h>
#include <string>

class Renderer
{
public:
	void Initialize();
	void CreateWindow(std::string name, int width, int height );
	void CopyFrameBuffer(const class Framebuffer& framebuffer);

	SDL_Renderer* GetRenderer() { return m_renderer; }

	void operator = (const class Framebuffer& framebuffer);

	friend class Framebuffer;

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
};