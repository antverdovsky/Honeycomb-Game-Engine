#version 410 core

#include <..\standard\include\stdCamera.glsl>

in vec3 out_vs_texCoord; // Texture Coordinates Output
in vec3 out_vs_norm; // The normalized normal vector of the vertex
in vec3 out_vs_pos; // The position of the vertex in the world

out vec4 color; // Fragment color

uniform samplerCube cube;

void main() {
    // Set the color of the fragment by fetching from the cube
	color = texture(cube, out_vs_texCoord);
}