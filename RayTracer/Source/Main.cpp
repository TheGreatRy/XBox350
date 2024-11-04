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
#include "Triangle.h"

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
    camera.SetView({ 0,0,20 }, { 0,0,0 });

    Scene scene;

    std::vector<std::shared_ptr<Material>> materials;

    //Lambertian
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0,1,0 });
    materials.push_back(std::move(green));
    
    std::shared_ptr<Material> pink = std::make_shared<Lambertian>(color3_t{ 1, 0, 1});
    materials.push_back(std::move(pink));
    
    //Metals
    std::shared_ptr<Material> red = std::make_shared<Metal>(color3_t{ 1, 0, 0 }, 0.3f);
    materials.push_back(std::move(red));

    //Emissive
    std::shared_ptr<Material> blue = std::make_shared<Emissive>(color3_t{ 0, 0, 1 }, 5.0f);
    materials.push_back(std::move(blue));

    //Dielectric
    std::shared_ptr<Material> yellow = std::make_shared<Dielectric>(color3_t{ 1, 1, 0 }, 2.33f);
    materials.push_back(std::move(yellow));

    for (int i = 0; i < 0; i++)
    {
        auto randObject = std::make_unique<Sphere>(random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f }), randomf(1.0f, 5.0f), materials[random(0,5)]);
        scene.AddObject(std::move(randObject));
    }
    auto triangle = std::make_unique<Triangle>(glm::vec3{5,-2.5f,-5}, glm::vec3{0,2.5f,0}, glm::vec3{-5,-2.5f,-5}, materials[3]);
    //scene.AddObject(std::move(triangle));

    auto model = std::make_unique<Model>( materials[3] );
    model->Load("cube-2.obj");
    /*Transform transform = { glm::vec3{-5,0,0}, glm::vec3{0,0,0}, glm::vec3{3} };
    auto actor = std::make_unique<Actor>(transform, std::move(model));*/
    scene.AddObject(std::move(model));
    
    std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
    auto plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, gray); 
    scene.AddObject(std::move(plane));

    //render
    //framebuffer.Clear(ColorConvert(color4_t{0,0.5f,0,1}));
    scene.Render(framebuffer, camera, 2, 3);

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

        

        framebuffer.Update();

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.GetRenderer());
    }

    return 0;
}