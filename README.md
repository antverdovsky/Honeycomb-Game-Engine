# Honeycomb
## Introduction
![picture alt](http://i.imgur.com/Sar1PEE.jpg)
Honeycomb is a 3D Game Engine written from scratch in C++ using OpenGL. It is not a game engine which is designed to rival any current game engines, but is rather my own object oriented abstraction of the OpenGL functions. I have been writing this engine purely for practice and for fun, but it may still be possible to create a fully featured game in the future using this engine.

## Installation
### Remark
Due to the vast differences in graphics hardware and drivers, I cannot guarantee the engine will function correctly on your machine. For best compatibility, you should update your graphics drivers to their most recent versions, and ensure that you have the latest OpenGL and GLSL versions available.

### Fetch
Either fork or clone this repository. For the purposes of this manual, the folder you acquired is referred to as the Honeycomb master directory. It contains the Honeycomb Library as well as a small Test Game executable.

### Resource Files
The Honeycomb library and its Test Game executable require a set of resource files in order to function correctly. In order to not pollute this GitHub repository, the files are not included on this repo, but may be acquired from [this Dropbox link](https://www.dropbox.com/sh/6nkd70gwobio5in/AACn92XMsDHNb3KVr4hH7VhRa?dl=0). Once downloaded, simply place the contents of the folder into the Honeycomb master directory.

Note on Resources: Even if you do not wish to use Honeycomb with any of its default 3D models or 2D textures, you must still acquire the resources since the Deferred Renderer utilizes rendering lights via rendering 3D models, which are included in the resource folder. Without these resources, the engine cannot render anything and will most likely crash.

### Dependencies
Honeycomb is dependent on the following external libraries (link to where you might acquire each library is included):
* [GLEW](http://glew.sourceforge.net/)
* [GLFW](http://www.glfw.org/)
* [ASSIMP](http://www.assimp.org/)
* [SOIL](http://www.lonesock.net/soil.html)

It is also recommended that you acquire [CMake](https://cmake.org/) since it will make building the engine a lot easier. For the dependent libraries, you should fetch the developer versions. Acquire them using your favorite package manager. An example is provided for acquiring all of the dependencies on Ubuntu:
```
sudo apt-get install cmake libglew-dev libglfw3-dev libassimp-dev libsoil-dev
```

### Build
#### Linux
Navigate to the Honeycomb master directory and run the following commands in your Terminal:
```
chmod +x buildUNIX.sh
./buildUNIX.sh
```
If all steps were done correctly up to this point, the Honeycomb Library should be automatically built and linked to the Test Game executable. To run the executable, execute the following commands in the same Terminal window:
```
cd executable
./HoneycombTestGame
```

#### Windows
Coming Soon...

#### macOS
Coming Soon...

## Implemented Features
- [x] 3D Model Loading (through ASSIMP)
- [x] 3D Mesh Rendering 
- [x] 3D Mesh Transformation
- [x] Camera Support
- [x] Component Support
- [x] Cubemaps and Skyboxes
- [x] Deferred Renderer
- [x] Fast Approximate Anti Aliasing (FXAA)
- [x] Game Object Support
- [x] Gamma Corrected and Linear Color Spaces
- [x] Lighting Support
  - [x] Ambient Light
  - [x] Directional Light
  - [x] Point Light
  - [x] Spot Light
  - [x] Specular Reflections
- [x] Math Support: Vector, Matrix, Quaternions
- [x] Normal/Bump Mapping
- [x] Scene Hierarchy
- [x] Shader Support
  - [x] Full integration with GLSL Shaders
  - [x] Ability to parse GLSL Structs into Honeycomb Components
  - [x] Auto detection and addition of uniform names to OpenGL
- [x] Specular Mapping
- [x] Transformation Hierarchy

and a lot more...

## Features to be Implemented
- [ ] Bloom
- [ ] Deferred Light Pre Pass Renderer
- [ ] Exception Handling
- [ ] Forward Renderer
- [ ] Geometry Shader Support
- [ ] HDR
- [ ] Intancing
- [ ] Physically Based Rendering
- [ ] Physics Engine (likely using Bullet)
- [ ] SSAO
- [ ] Shadow Mapping
- [ ] Transparency

and a lot more...

## License
This entire project has been written using the MIT License. Feel free to borrow, use, or enlighten yourself with any of the code found on this repository. 
