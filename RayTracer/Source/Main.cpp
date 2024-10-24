#include "Renderer.h"
#include "FrameBuffer.h"
#include "PostProcess.h"
#include "Color.h"
#include "Image.h"
#include "Model.h"
#include "ETime.h"
#include "Random.h"
#include "Input.h"
#include "Transform.h"
#include "Camera.h"
#include "Actor.h"
#include "Tracer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    Time time;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Gaming", 800, 600);

    SetBlendMode(BlendMode::NORMAL);

    Framebuffer frameBuffer(renderer, 800, 600);

    Camera camera{ 70.0f, frameBuffer.m_width / (float)frameBuffer.m_height };
    camera.SetView({ 0,0,-20 }, { 0,0,0 });

    Tracer tracer;

    bool quit = false;
    while (!quit)
    {
        time.Tick();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }

        frameBuffer.Clear(color_t{ 0,255,0,255 });
        tracer.Render(frameBuffer, camera);

        frameBuffer.Update();
        // show screen
        renderer = frameBuffer;
        SDL_RenderPresent(renderer.GetRenderer());
    }

    return 0;
}