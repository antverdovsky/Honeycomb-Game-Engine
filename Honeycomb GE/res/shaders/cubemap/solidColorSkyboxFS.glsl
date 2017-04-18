#version 410 core

#include <../standard/structs/stdCamera.glsl>

in vec3 out_vs_texCoord; // Texture Coordinates Output
in vec3 out_vs_norm; // The normalized normal vector of the vertex
in vec3 out_vs_pos; // The position of the vertex in the world

out vec4 color; // Fragment color

uniform vec4 solidColor; // Solid Color of the Skybox

void main() {
    // Set the color of the fragment to the solid color of the uniform
	color = solidColor;
}