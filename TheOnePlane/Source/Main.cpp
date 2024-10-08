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
        /*
        SDL_SetRenderDrawColor(renderer.GetRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(renderer.GetRenderer());
        */

        //Framebuffer Class
        
        frameBuffer.Clear(color_t{ 0,0,0,255 });
      
        //draw point
        frameBuffer.DrawPoint(0, 0, color_t{ 255,255,255,255 });for (int i = 0; i < 1000; i++);
        //draw random point
        
        for (int i = 0; i < 1000; i++)
        {
            int x = rand() % frameBuffer.m_width;
            int y = rand() % frameBuffer.m_height;
            frameBuffer.DrawPoint(x, y, color_t{ 255,255,255,255 });
        }
        //uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() % 255)
        
        //draw rectangle
        frameBuffer.DrawRect(20, 10, 50, 50, color_t{ 255,255,255,255 });
        
        //draw random lines
        /*
        for (int i = 0; i < 100; i++)
        {
            int x = rand() % frameBuffer.m_width;
            int y = rand() % frameBuffer.m_height;
            int x2 = rand() % frameBuffer.m_width;
            int y2 = rand() % frameBuffer.m_height;
            frameBuffer.DrawLine(x, y, x2, y2, color_t{ uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() % 255) });
        }
        */

        //draw random triangle
        /*
        int x = rand() % frameBuffer.m_width;
        int y = rand() % frameBuffer.m_height;
        int x2 = rand() % frameBuffer.m_width;
        int y2 = rand() % frameBuffer.m_height;
        int x3 = rand() % frameBuffer.m_width;
        int y3 = rand() % frameBuffer.m_height;
        frameBuffer.DrawTriangle(x, y, x2, y2, x3, y3,color_t{ uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() % 255) });
        */

        //draw circle
        frameBuffer.DrawCircle(frameBuffer.m_width / 2, frameBuffer.m_height / 2, 20, color_t{ 255,255,255,255 });

        int mx, my;
        SDL_GetMouseState(&mx, &my);

        //draw linear curve
        frameBuffer.DrawLinearCurve(100, 100, 200, 200, color_t{ 255,255,255,255 });

        //draw quad curve
        frameBuffer.DrawQuadraticCurve(100, 200, mx, my, 300, 200, color_t{ 255,255,255,255 });

        //draw cubic curve
        frameBuffer.DrawCubicCurve(100, 200, 100, 100, 200, 100, 200, 200, color_t{ 255,255,255,255 });

        frameBuffer.Update();
        renderer = frameBuffer;
        //renderer.CopyFrameBuffer(frameBuffer);
        

        // show screen
        SDL_RenderPresent(renderer.GetRenderer());
    }

    return 0;
}