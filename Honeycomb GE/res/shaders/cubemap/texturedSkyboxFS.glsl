#version 410 core

#include <../standard/structs/stdMaterial.glsl>

in vec3 out_vs_texCoord; // Texture Coordinates Output
in vec3 out_vs_norm; // The normalized normal vector of the vertex
in vec3 out_vs_pos; // The position of the vertex in the world

out vec4 color; // Fragment color

uniform samplerCube cube;
uniform float gamma;

void main() {
	color = textureCubeSRGB(cube, out_vs_texCoord, gamma);
}