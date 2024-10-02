#include "Renderer.h"
#include "FrameBuffer.h"
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    Renderer renderer;
    // initialize SDL
    renderer.Initialize();

    // create window
    renderer.CreateWindow("Gaming", 800, 600);

    Framebuffer frameBuffer(renderer, 400, 300);
   

    bool quit = false;
    while (!quit)
    {
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
        // clear screen
        // Renderer Class
        SDL_SetRenderDrawColor(renderer.GetRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(renderer.GetRenderer());

        //Framebuffer Class
        /*
        frameBuffer.Clear(color_t{ 0,0,0,255 });
        frameBuffer.DrawPoint(0, 0, color_t{ 255,255,255,255 });
        frameBuffer.Update();

        renderer = frameBuffer;
        //renderer.CopyFrameBuffer(frameBuffer);
        */

        // show screen
        SDL_RenderPresent(renderer.GetRenderer());
    }

    return 0;
}