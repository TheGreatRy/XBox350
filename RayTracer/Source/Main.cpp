#include "Renderer.h"
#include "framebuffer.h"
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
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"

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

    Framebuffer framebuffer(renderer, 800, 600);

    Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };
    camera.SetView({ 0,0,-20 }, { 0,0,0 });

    Scene scene;

    std::shared_ptr<Material> material = std::make_shared<Material>(color3_t{1,0,0});
    std::unique_ptr<Sphere> object = std::make_unique<Sphere>(glm::vec3{ 0,0,0 }, 2.0f, material);

    scene.AddObject(std::move(object));

    std::shared_ptr<Material> planeMaterial = std::make_shared<Material>(color3_t{ 0,0,1 });
    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, planeMaterial);
    scene.AddObject(std::move(plane));

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

        framebuffer.Clear(color_t{ 0,255,0,255 });

        scene.Render(framebuffer, camera);

        framebuffer.Update();

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.GetRenderer());
    }

    return 0;
}