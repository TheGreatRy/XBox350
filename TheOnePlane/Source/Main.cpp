#include "Renderer.h"
#include "FrameBuffer.h"
#include "PostProcess.h"
#include "Color.h"
#include "Image.h"
#include "Model.h"
#include "MathUtils.h"
#include "ETime.h"
#include "Random.h"
#include "Input.h"
#include "Transform.h"
#include "Camera.h"
#include "Actor.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char* argv[])
{
    Time time;

    Renderer renderer;
    // initialize SDL
    renderer.Initialize();

    // create window
    renderer.CreateWindow("Gaming", 800, 600);

    Input input;
    input.Initialize();
    input.Update();

    SetBlendMode(BlendMode::NORMAL);

    Camera camera(renderer.m_width, renderer.m_height);
    camera.SetView(glm::vec3{ 0,0,0}, glm::vec3{ 0 });
    camera.SetProjection(60.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform camTransform{ {0,0,-10} };

    Framebuffer frameBuffer(renderer, 800, 600);

    Image image;
    image.Load("space.jpg");

    Image imageAlp;
    imageAlp.Load("colors.png");
    PostProcess::Alpha(imageAlp.m_buffer, 128);

    Shader::uniforms.view = camera.GetView();
    Shader::uniforms.projection = camera.GetProjection();
    Shader::uniforms.ambient = color3_t{ 0.05f };

    Shader::uniforms.light.position = glm::vec3{ 10, 10, -10 };
    Shader::uniforms.light.direction = glm::vec3{ 0, -1, 0 }; // light pointing down
    Shader::uniforms.light.color = color3_t{ 1 }; 

    // materials
    std::shared_ptr<material_t> material = std::make_shared<material_t>();
    material->albedo = color3_t{ 0, 0, 1 };
    material->specular = color3_t{ 1 };
    material->shininess = 50.0f;
    
    std::shared_ptr<material_t> material_dull = std::make_shared<material_t>();
    material_dull->albedo = color3_t{ 0, 1, 0 };
    material_dull->specular = color3_t{ 0.1f };
    material_dull->shininess = 5.0f;
    
    std::shared_ptr<material_t> material_mid = std::make_shared<material_t>();
    material_mid->albedo = color3_t{ 1, 0, 0 };
    material_mid->specular = color3_t{ 0.7f };
    material_mid->shininess = 15.0f;

    Shader::framebuffer = &frameBuffer;

    std::vector<std::unique_ptr<Actor>> actors;

#pragma region scene
    ////Astronaut by Poly by Google [CC-BY] via Poly Pizza
    //std::shared_ptr<Model> site = std::make_shared<Model>();
    //site->Load("models/model.obj");

    //Transform siteTrans = { {-25, 0,50}, glm::vec3{-15,0,-45}, glm::vec3{15} };
    //std::unique_ptr<Actor> siteActor = std::make_unique<Actor>(siteTrans, site);
    //siteActor->SetColor({ 150,0,200,255 });
    //actors.push_back(std::move(siteActor));

    ////Rocket ship by Poly by Google [CC-BY] via Poly Pizza
    //std::shared_ptr<Model> ship = std::make_shared<Model>();
    //ship->Load("models/RocketShip.obj");

    //Transform shipTrans = { {30, 0,50}, glm::vec3{15,0,45}, glm::vec3{1} };
    //std::unique_ptr<Actor> shipActor = std::make_unique<Actor>(shipTrans, ship);
    //shipActor->SetColor({ 150,0,0,255 });
    //actors.push_back(std::move(shipActor));

    ////Moon by Poly by Google [CC-BY] via Poly Pizza
    //std::shared_ptr<Model> model = std::make_shared<Model>();
    //model->Load("models/moon.obj");

    //Transform transform = { {0,-20,60}, glm::vec3{0,0,0}, glm::vec3{0.5f} };
    //std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
    //actor->SetColor({ 100,100,100,255 });
    //actors.push_back(std::move(actor));
#pragma endregion

    std::shared_ptr<Model> model = std::make_shared<Model>();
    model->Load("models/cube.obj");
    Transform transform = { glm::vec3{0}, glm::vec3{0}, glm::vec3{3} };

    std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model, material);
    actors.push_back(std::move(actor));

    Transform transform_dull = { glm::vec3{5,0,0}, glm::vec3{0}, glm::vec3{3} };

    std::unique_ptr<Actor> actor_dull = std::make_unique<Actor>(transform_dull, model, material_dull);
    //actors.push_back(std::move(actor_dull));
    
    Transform transform_mid = { glm::vec3{-5,0,0}, glm::vec3{0}, glm::vec3{3} };

    std::unique_ptr<Actor> actor_mid = std::make_unique<Actor>(transform_mid, model, material_mid);
    //actors.push_back(std::move(actor_mid));

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
        //// clipping
        //frameBuffer.DrawLine(-10, 20, 50, -10, color_t{255,255,255,255});

        ////no clipping (completely inside)
        //frameBuffer.DrawLine(10, 20, 50, 10, color_t{255,255,255,255});

        ////no clipping (completely outside)
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

        SetBlendMode(BlendMode::NORMAL);
        frameBuffer.DrawImage(0, 0, 50, 100, image);
        //SetBlendMode(BlendMode::NORMAL);
        //SetBlendMode(BlendMode::ALPHA);
        //SetBlendMode(BlendMode::ADD);
        //SetBlendMode(BlendMode::MULTIPLY);
       
        //frameBuffer.DrawImage(20, 20, 50, 100, imageAlp);
        //PostProcess::Invert(frameBuffer.m_buffer);

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


#pragma endregion

        if (input.GetMouseButtonDown(2))
        {
            input.SetRelativeMode(true);
            glm::vec3 direction{ 0 };

            if (input.GetKeyDown(SDL_SCANCODE_D))   direction.x =  1;
            if (input.GetKeyDown(SDL_SCANCODE_A))   direction.x = -1;
            if (input.GetKeyDown(SDL_SCANCODE_E))   direction.y =  1;
            if (input.GetKeyDown(SDL_SCANCODE_Q))   direction.y = -1;
            if (input.GetKeyDown(SDL_SCANCODE_W))   direction.z =  1;
            if (input.GetKeyDown(SDL_SCANCODE_S))   direction.z = -1;

            camTransform.rotation.y += input.GetMouseRelative().x * 0.25f;
            camTransform.rotation.x += input.GetMouseRelative().y * 0.25f;

            glm::vec3 offset = camTransform.GetMatrix() * glm::vec4{ direction, 0 };
            camTransform.position += offset * 5.0f * time.GetDeltaTime();
        }
        else
        {
            
            input.SetRelativeMode(false);
        }

        
        camera.SetView(camTransform.position, camTransform.position + camTransform.GetForward());
        Shader::uniforms.view = camera.GetView();
        
        for (auto& actor : actors) 
        {
            actor->GetTransform().rotation.y += time.GetDeltaTime() * 90;
            actor->Draw();
        }
        /*;
        PostProcess::Invert(frameBuffer.m_buffer);*/

        frameBuffer.Update();
        // show screen
        renderer = frameBuffer;
        SDL_RenderPresent(renderer.GetRenderer());
    }
    return 0;
}