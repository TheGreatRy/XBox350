#include "Renderer.h"
#include "FrameBuffer.h"
#include "PostProcess.h"
#include "Color.h"
#include "Image.h"
#include "Model.h"
#include "ETime.h"
#include "Input.h"
#include "Transform.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    Time time;
    Input input;
    input.Initialize();

    Renderer renderer;
    // initialize SDL
    renderer.Initialize();

    // create window
    renderer.CreateWindow("Gaming", 800, 600);

    SetBlendMode(BlendMode::NORMAL);

    Camera camera(renderer.m_width, renderer.m_height);
    camera.SetView(glm::vec3{ 0,0,-20 }, glm::vec3{ 0 });
    camera.SetProjection(60.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform camTransform{ {0,0,-20} };

    Framebuffer frameBuffer(renderer, 800, 600);

    Image image;
    image.Load("outside.jpg");

    Image imageAlp;
    imageAlp.Load("colors.png");
    PostProcess::Alpha(imageAlp.m_buffer, 128);

    vertices_t vertices = { {-5, 5, 0}, {5, 5, 0},{-5, -5, 0} };
    Model model(vertices, { 0,255,0,255 });
    Transform transform = { {0,0,45}, glm::vec3{0,0,45}, glm::vec3{3} };

    bool quit = false;
    while (!quit)
    {
        time.Tick();
        input.Update();

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
        
        int mx, my; 
        SDL_GetMouseState(&mx, &my);
        //uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() %255)

        /*
        int ticks = SDL_GetTicks();
        float time = ticks * 0.001f;
        float t = std::abs(std::sin(time));
        */


#pragma region clear_screen
        // Renderer Class
        /*
        SDL_SetRenderDrawColor(renderer.GetRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(renderer.GetRenderer());
        */

        //Framebuffer Class
        
        frameBuffer.Clear(color_t{ 0,0,0,255 });
#pragma endregion

#pragma region draw_points_lines
        //draw point
        //frameBuffer.DrawPoint(0, 0, color_t{ 255,255,255,255 });
        //draw random point
        /*
        for (int i = 0; i < 1000; i++)
        {
            int x = rand() % frameBuffer.m_width;
            int y = rand() % frameBuffer.m_height;
            frameBuffer.DrawPoint(x, y, color_t{ 255,255,255,255 });
        }
        */

        //draw with clipping algorithm
        // clipping
        //frameBuffer.DrawLine(-10, 20, 50, -10, color_t{255,255,255,255});

        // no clipping (completely inside)
        //frameBuffer.DrawLine(10, 20, 50, 10, color_t{255,255,255,255});

        // no clipping (completely outside)
        //frameBuffer.DrawLine(-10, -1, -1, -10, color_t{255,255,255,255});
        
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
#pragma endregion

#pragma region draw_shapes
        
        //draw rectangle
        //frameBuffer.DrawRect(20, 10, 50, 50, color_t{ 255,255,255,255 });
        
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
        //frameBuffer.DrawCircle(frameBuffer.m_width / 2, frameBuffer.m_height / 2, 20, color_t{ 255,255,255,255 });
#pragma endregion
        
#pragma region draw_curves
        //draw linear curve
        //frameBuffer.DrawLinearCurve(100, 100, 200, 200, color_t{ 255,255,255,255 });

        //draw quad curve
        //frameBuffer.DrawQuadraticCurve(100, 200, mx, my, 300, 200, color_t{ 255,255,255,255 });

        //draw cubic curve
        //frameBuffer.DrawCubicCurve(100, 200, 100, 100, 200, 100, 200, 200, color_t{ 255,255,255,255 });
#pragma endregion

#pragma region alpha_blend

        //SetBlendMode(BlendMode::NORMAL);
        //frameBuffer.DrawImage(20, 20, 50, 100, image);

        //SetBlendMode(BlendMode::NORMAL);
        //SetBlendMode(BlendMode::ALPHA);
        //SetBlendMode(BlendMode::ADD);
        //SetBlendMode(BlendMode::MULTIPLY);
        //frameBuffer.DrawImage(20, 20, 50, 100, imageAlp);

#pragma endregion

#pragma region post_process
        /*
        PostProcess::Invert(frameBuffer.m_buffer);
        PostProcess::Monochrome(frameBuffer.m_buffer);
        PostProcess::Brightness(frameBuffer.m_buffer, 70);
        PostProcess::Noise(frameBuffer.m_buffer, 100);
        PostProcess::ColorBalance(frameBuffer.m_buffer, 150, -50, -50);
        PostProcess::Threshold(frameBuffer.m_buffer, 150);
        PostProcess::Posterize(frameBuffer.m_buffer, 4);
        */

        //PostProcess::BoxBlur(frameBuffer.m_buffer, frameBuffer.m_width, frameBuffer.m_height);
        //PostProcess::GaussBlur(frameBuffer.m_buffer, frameBuffer.m_width, frameBuffer.m_height);
        //PostProcess::Sharpen(frameBuffer.m_buffer, frameBuffer.m_width, frameBuffer.m_height);
        //PostProcess::Edge(frameBuffer.m_buffer, frameBuffer.m_width, frameBuffer.m_height, 100);
        //PostProcess::Emboss(frameBuffer.m_buffer, frameBuffer.m_width, frameBuffer.m_height);
#pragma endregion

#pragma region models
        /*
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate(modelMatrix, glm::vec3(400.0f, 300.0f, 0.0f));
        glm::mat4 scale = glm::scale(modelMatrix, glm::vec3(5));
        glm::mat4 rotate = glm::rotate(modelMatrix, glm::radians(time * 90), glm::vec3{ 0,1,0 });
        modelMatrix = translate * scale * rotate;
        */

        //glm::vec3 direction{ 0 };

        //if (input.GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
        //if (input.GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;
        //if (input.GetKeyDown(SDL_SCANCODE_D)) direction.y = 1;
        //if (input.GetKeyDown(SDL_SCANCODE_A)) direction.y = -1;
        //if (input.GetKeyDown(SDL_SCANCODE_Q)) direction.z = 1;
        //if (input.GetKeyDown(SDL_SCANCODE_E)) direction.z = -1;
       
        ////camTransform.position += direction * 70.0f * time.GetDeltaTime();
        ////camera.SetView(camTransform.position, glm::vec3{ 0 });
        //direction += 90 * direction.z;
#pragma endregion
        
        model.Draw(frameBuffer, transform.getMatirx(), camera);

        frameBuffer.Update();
        // show screen
        renderer = frameBuffer;
        SDL_RenderPresent(renderer.GetRenderer());
    }

    return 0;
}