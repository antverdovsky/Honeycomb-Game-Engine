#version 410 core

#include <../standard/include/stdCamera.glsl>

// Retrieves the position, texture coordinate, and normal of the Vertex from
// the specified vertex attribute array pointers (see Mesh.cpp)
layout (location = 0) in vec3 in_vs_pos;
layout (location = 1) in vec2 in_vs_texCoord;
layout (location = 2) in vec3 in_vs_norm;

uniform Camera camera;

out vec3 out_vs_texCoord; // Texture Coordinates Output
out vec3 out_vs_norm; // The normalized normal vector of the vertex
out vec3 out_vs_pos; // The position of the vertex in the world

void main() {
    // Set the position of the vertex depending on the Camera view
    vec4 pos = camera.view * vec4(in_vs_pos, 1.0F);
	gl_Position = pos.xyww;
    
    // Since we have a 1x1x1 Cube, texture coordinates = position coordinates
    out_vs_texCoord = in_vs_pos;
	out_vs_norm = in_vs_norm;
    out_vs_pos = pos.xyw;
}