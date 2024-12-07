<img width="601" alt="rendered_scene" src="https://github.com/user-attachments/assets/b4486e10-d4c9-4e2e-864f-978b518756ff">

# XBox350

TheOnePlane is a school software project that utilizes GLM, SDL, and STB to render obj models and a movable camera to interact with 3D scenes. Object rendering includes primitives, materials, and post processing. It also supports lighting and shaders, with lighting being Gouraud and Phong and shaders being fragment and vertex shaders.

RayTracer was built on top of the TheOnePlane and renders primitives and complex models with support for Lambertian, metallic, dielectric, and emissive materials. It also implements anti-aliasing and multiple bounce reflections.

# Build

To get the build working, you will need Visual Studio with the C++ language available. These instructions go through the steps of setting up the project in Visual Studio

## Project Properties

1) Go to General -> C++ Standard Language and check to make sure it is C++ 17 or higher.
2) Go to General -> Debugging -> Working Directory and set the value to $(SolutionDir)Build
3) Go to C/C++ -> Additional Include Directories and set the value to $(SolutionDir)ThirdParty\SDL2\include;$(SolutionDir)ThirdParty\stb;$(SolutionDir)ThirdParty/glm;%(AdditionalIncludeDirectories)
4) Go to Linker -> General -> Additional Library Directories and set the value to $(SolutionDir)ThirdParty\SDL2\lib\$(PlatformTarget)
5) Go to Linker -> Input -> Additional Dependencies and set the value to sdl2.lib;sdl2main.lib;%(AdditionalDependencies)

# TheOnePlane

<img width="605" alt="oneplane_lightingrender" src="https://github.com/user-attachments/assets/00ebea7a-0036-468e-9435-d043f0480421">

## Run
When you run the program, you will be able to view a 3D vector scene with a movable camera

You will need to hold right click on your mouse to move the camera.
- Holding right click and moving the mouse will change where the camera is pointing
- Right Click + W: move the camera forward
- Right Click + S: move the camera backward
- Right Click + A: move the camera left
- Right Click + D: move the camera right
- Right Click + Q: move the camera down
- Right Click + E: move the camera up
- 
<img width="601" alt="pointlight_render" src="https://github.com/user-attachments/assets/9b26a457-2798-463b-8b61-aa45c376d926">

## Features
- Shaders: Fragment and Vertex Shaders
- Lighting: Gouraud and Phong
- Materials: Albedo, Shininess, and Specular
- Image Rendering: Blend Modes and Post Processing
- Camera Movement: View Movement

# RayTracer

<img width="602" alt="raytracer_render" src="https://github.com/user-attachments/assets/e1395171-f0cd-45da-a21e-d407eb2a80bd">

## Run
There is no camera movement as this project's focus is on rendering a scene

You can change the sample number and depth (ray bounces) per pixel for rendering the scene on line 46 of main:
- scene.Render(framebuffer, camera, SAMPLES, DEPTH);
- The materials will not render if you go below 1 sample and a depth of 2

<img width="608" alt="cornell_box" src="https://github.com/user-attachments/assets/334d94d8-b8c5-46f4-bdcf-04c010565b92">

## Features
- Materials: Lambertian, Metal, Dielectric, and Emissive
- Post Processing: Image and Scene Effects
- Anti-Aliasing: Sampling and Kernal Rendering
- Muti-Bounce Rays: Dynamic Renders



    
  
