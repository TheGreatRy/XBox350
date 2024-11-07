# XBox350

TheOnePlane is a school software project that utilizes GLM, SDL, and STB to render obj models in a vector mesh and a movable camera to interact with 3D scenes
RayTracer builds on TheOnePlane but renders materials and objects beyond vector representations

# Build

To get the build working, you will need Visual Studio with the C++ language available. These instructions go through the steps of setting up the project in Visual Studio

## Project Properties

1) Go to General -> C++ Standard Language and check to make sure it is C++ 17 or higher.
2) Go to General -> Debugging -> Working Directory and set the value to $(SolutionDir)Build
3) Go to C/C++ -> Additional Include Directories and set the value to $(SolutionDir)ThirdParty\SDL2\include;$(SolutionDir)ThirdParty\stb;$(SolutionDir)ThirdParty/glm;%(AdditionalIncludeDirectories)
4) Go to Linker -> General -> Additional Library Directories and set the value to $(SolutionDir)ThirdParty\SDL2\lib\$(PlatformTarget)
5) Go to Linker -> Input -> Additional Dependencies and set the value to sdl2.lib;sdl2main.lib;%(AdditionalDependencies)

# TheOnePlane
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
