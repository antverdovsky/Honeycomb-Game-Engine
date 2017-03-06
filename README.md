# Honeycomb
## Introduction
![picture alt](http://i.imgur.com/Sar1PEE.jpg)
Honeycomb is a 3D Game Engine written in C++ using the GLEW and GLFW OpenGL libraries. It is not a game engine which is designed to rival any current game engines, but is rather my own object oriented abstraction of the OpenGL functions. I have been writing this engine purely for practice and for fun, but it may still be possible to create a fully featured game in the future using this engine.

## Installation
Currently, it is only possible to compile and run Honeycomb on Windows. You MUST have GLEW, GLFW, ASSIMP and SOIL libraries installed in order to compile the project, and ASSIMP in order to run the engine. In the future, hopefully, this installation process will be simplified. For now: 
* Clone or fork the repository 
* Open the solution in Visual Studio.
* Set the Additional Include and Linker Dependencies
  * Go into Properties -> C/C++ -> General and set the include directories of the ASSIMP, GLEW, GLFW, SOIL libraries relative to your machine
  * Go into Properties -> Librarian -> General and set the Additional Dependencies and Additional Library Directories relative to your machine
* Set the Startup Project as the Test Game and Build
* Add the ASSIMP DLL to the same directory as the executable file
* Run the Test Game executable

Alternatively, if you just want to run the Test Game file without compiling the project, you may download the always up to date Test Game demo from the [Dropbox Repository](https://www.dropbox.com/sh/fjtj6niks8a47gc/AABEKlFUSKYpYwaHj2Jwr3i4a?dl=0). Simply download the folder, and run the Test Game executable. You will still need to have the GLEW, GLFW, ASSIMP and SOIL binaries installed, however.

## Implemented Features
- [x] 3D Model Loading (through ASSIMP)
- [x] 3D Mesh Rendering 
- [x] 3D Mesh Transformation
- [x] Camera Support
- [x] Component Support
- [x] Deferred Rendering (partial)
- [x] Forward Rendering
- [x] Game Object Support
- [x] Lighting Support
  - [x] Ambient Light
  - [x] Directional Light
  - [x] Point Light
  - [x] Spot Light
  - [x] Specular Reflections
- [x] Math Support: Vector, Matrix, Quaternions
- [x] Shader Support
  - [x] Full integration with GLSL Shaders
  - [x] Ability to parse GLSL Structs into Honeycomb Components
  - [x] Auto detection and addition of uniform names to OpenGL
- [x] Transformation Hierarchy

and a lot more...

## Features to be Implemented
- [ ] Anti-Aliasing
- [ ] Bloom
- [ ] Cube maps
- [ ] Exception Handling
- [ ] Gamma Correction
- [ ] Geometry Shader Support
- [ ] HDR
- [ ] Intancing
- [ ] Physically Based Rendering
- [ ] Physics Engine (likely using Bullet)
- [ ] SSAO
- [ ] Shadow Mapping
- [ ] Transparency (in Deferred Renderer)

and a lot more...

## License
This entire project has been written using the MIT License. Feel free to borrow, use, or enlighten yourself with any of the code found on this repository. 
