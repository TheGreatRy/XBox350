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
    
    scene.Render(framebuffer, camera, 80, 6);
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
    //final
    //scene.SetSky(color3_t{ 1,1,1 }, color3_t{ 0.1f,0.3f,0.5f });

    //final extra credit
    scene.SetSky(color3_t{ 0,0,0 }, color3_t{ 0.1f,0.3f,0.7f });
    
    std::vector<std::shared_ptr<Material>> materials;

    //Lambertian
    std::shared_ptr<Material> blue = std::make_shared<Lambertian>(color3_t{ 0,0,1 });
    materials.push_back(blue);

    std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    materials.push_back(red);

    //Metals
    std::shared_ptr<Material> yellow = std::make_shared<Metal>(color3_t{ 1, 1, 0 }, 0.5f);
    materials.push_back(yellow);

    auto cyan = std::make_shared<Metal>(color3_t{ 0,1,1 }, 0.3f);
    materials.push_back(cyan);

    //Emissive
    std::shared_ptr<Material> white = std::make_shared<Emissive>(color3_t{ 1});
    materials.push_back(white);

    //Dielectric
    std::shared_ptr<Material> pink = std::make_shared<Dielectric>(color3_t{ 1, 0, 1}, 3.01f);
    materials.push_back(pink);
    
    std::shared_ptr<Material> glass = std::make_shared<Dielectric>(color3_t{ 1 }, 5.33f);

    //plane
    /*
    std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 1 });
    auto plane = std::make_unique<Plane>(Transform{ glm::vec3{0,-2,0}, glm::vec3{0, 0 ,0} }, gray);
    scene.AddObject(std::move(plane));*/
    
    //box

    /*auto roof = std::make_unique<Plane>(Transform{ glm::vec3{0,2,0}, glm::vec3{180, 0 ,0} }, gray);
    scene.AddObject(std::move(roof));
    
    auto planeBack = std::make_unique<Plane>(Transform{ glm::vec3{0,0,11}, glm::vec3{90, 0 ,0} }, gray);
    scene.AddObject(std::move(planeBack));

    auto wallLeft = std::make_unique<Plane>(Transform{ glm::vec3{3,0,0}, glm::vec3{90, 0 ,-90} }, red);
    scene.AddObject(std::move(wallLeft));
    
    auto wallRight = std::make_unique<Plane>(Transform{ glm::vec3{-3,0,0}, glm::vec3{90, 0 ,90} }, green);
    scene.AddObject(std::move(wallRight));*/

    
    for (int i = 0; i < 300; i++)
    {
        //final
        /*auto randObject = std::make_unique<Sphere>(
            Transform{ random(glm::vec3{ -20.0f, -1.5f, -20.0f }, glm::vec3{ 20.0f, -1.0f, 30.0f }), glm::vec3{20,0,0} },
            randomf(0.1f, 0.5f),
            materials[random(0, 6)]
        );*/
        //final extra credit
        auto randObject = std::make_unique<Sphere>(
            Transform{ random(glm::vec3{ -20.0f, -5.0f, -20.0f }, glm::vec3{ 20.0f, 5.0f, 30.0f }), glm::vec3{20,0,0} },
            randomf(0.1f, 0.5f),
            glass
        );
        scene.AddObject(std::move(randObject));
    }
    
    
    //final
    /*std::shared_ptr<Material> metal = std::make_shared<Metal>(color3_t{ 0.7f }, 0.0f);
    auto sphere = std::make_unique<Sphere>(Transform{ glm::vec3{-3,-0.5f, 15}, glm::vec3{0,0,0}, glm::vec3{1.5f} }, 1.0f, metal );
    scene.AddObject(std::move(sphere));
    
    auto orb = std::make_unique<Sphere>(Transform{ glm::vec3{-1,-0.5f, 10}, glm::vec3{0,0,0}, glm::vec3{1.5f} }, 1.0f, glass );
    scene.AddObject(std::move(orb));
    
    std::shared_ptr<Material> diffuse = std::make_shared<Lambertian>(color3_t{ 0.1f, 0.7f, 0.3f });
    auto cube = std::make_unique<Model>(Transform{ glm::vec3{1,-0.5f, 5}, glm::vec3{0,0,0}, glm::vec3{1.5f} }, diffuse );
    cube->Load("models/cube.obj"),
    scene.AddObject(std::move(cube));*/

    //final extra credit
    auto triangle = std::make_unique<Triangle>(glm::vec3{ 10,-2.5f,0 }, glm::vec3{ 10,2.5f,0 }, glm::vec3{5,0,0 } , blue);
    scene.AddObject(std::move(triangle));

    auto cube = std::make_unique<Model>(Transform{ glm::vec3{1,0, 5}, glm::vec3{0,30,0}, glm::vec3{5} }, blue);
    cube->Load("models/cube-2.obj");
    scene.AddObject(std::move(cube));

    auto orb = std::make_unique<Sphere>(Transform{ glm::vec3{-5,5, 5}, glm::vec3{0,0,0}, glm::vec3{1.5f} }, 1.0f, white);
    scene.AddObject(std::move(orb));
}