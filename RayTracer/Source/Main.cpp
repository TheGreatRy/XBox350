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

void InitScene(Scene& scene);

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
    InitScene(scene);
    scene.Update();
    
    scene.Render(framebuffer, camera, 1000, 3);
    framebuffer.Update();

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

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.GetRenderer());
    }

    return 0;
}

void InitScene(Scene& scene)
{
    
    std::vector<std::shared_ptr<Material>> materials;

    //Lambertian
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0,1,0 });
    materials.push_back(green);

    std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    materials.push_back(red);

    std::shared_ptr<Material> blue = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    materials.push_back(blue);

    //Metals
    std::shared_ptr<Material> pink = std::make_shared<Metal>(color3_t{ 1, 0, 1 }, 0.5f);
    materials.push_back(pink);

    //Emissive

    //Dielectric
    std::shared_ptr<Material> yellow = std::make_shared<Dielectric>(color3_t{ 1, 1, 0 }, 5.33f);
    materials.push_back(yellow);

    std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 1 });

    //box
    auto plane = std::make_unique<Plane>(Transform{ glm::vec3{0,-2,0}, glm::vec3{0, 0 ,0} }, gray);
    scene.AddObject(std::move(plane));

    auto roof = std::make_unique<Plane>(Transform{ glm::vec3{0,2,0}, glm::vec3{180, 0 ,0} }, gray);
    scene.AddObject(std::move(roof));
    
    auto planeBack = std::make_unique<Plane>(Transform{ glm::vec3{0,0,11}, glm::vec3{90, 0 ,0} }, gray);
    scene.AddObject(std::move(planeBack));

    auto wallLeft = std::make_unique<Plane>(Transform{ glm::vec3{3,0,0}, glm::vec3{90, 0 ,-90} }, red);
    scene.AddObject(std::move(wallLeft));
    
    auto wallRight = std::make_unique<Plane>(Transform{ glm::vec3{-3,0,0}, glm::vec3{90, 0 ,90} }, green);
    scene.AddObject(std::move(wallRight));

    for (int i = 0; i < 0; i++)
    {
        auto randObject = std::make_unique<Sphere>(
            Transform{ random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f }), glm::vec3{20,0,0} },
            randomf(1.0f, 5.0f),
            materials[random(0, 5)]
        );
        scene.AddObject(std::move(randObject));
    }
    /*auto triangle = std::make_unique<Triangle>(glm::vec3{ 5,-2.5f,-5 }, glm::vec3{ 0,2.5f,0 }, glm::vec3{ -5,-2.5f,-5 }, materials[3]);
    scene.AddObject(std::move(triangle));*/

    auto model = std::make_unique<Model>(Transform{ glm::vec3{0,2.47f,16}, glm::vec3{0,0,0}, glm::vec3{1} }, std::make_shared<Emissive>(HSVtoRGB( 300.0f, 0.0f, 10.0f )));
    model->Load("models/cube.obj");
    scene.AddObject(std::move(model));
    
    auto sphere = std::make_unique<Sphere>(Transform{ glm::vec3{1,-1.5f, 16}, glm::vec3{0,0,0}, glm::vec3{1} }, 0.5f, pink );
    scene.AddObject(std::move(sphere));
    
    auto cube = std::make_unique<Model>(Transform{ glm::vec3{-1,-1.5f, 15}, glm::vec3{0,45,0} }, blue );
    cube->Load("models/cube.obj");
    scene.AddObject(std::move(cube));

}