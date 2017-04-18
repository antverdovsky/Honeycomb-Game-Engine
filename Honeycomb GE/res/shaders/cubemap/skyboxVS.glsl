#version 410 core

#include <../standard/structs/stdCamera.glsl>
#include <../standard/vertex/stdVertexVS.glsl>

uniform Camera camera;

out vec3 out_vs_texCoord; // Texture Coordinates Output
out vec3 out_vs_norm; // The normalized normal vector of the vertex
out vec3 out_vs_pos; // The position of the vertex in the world

void main() {
    // Set the position of the vertex depending on the Camera view
    vec4 pos = camera.view * in_vs_position;
	gl_Position = pos.xyww;
    
    // Since we have a 1x1x1 Cube, texture coordinates = position coordinates
    out_vs_texCoord = in_vs_position.xyz;
	out_vs_norm = in_vs_normal.xyz;
    out_vs_pos = pos.xyw;
}