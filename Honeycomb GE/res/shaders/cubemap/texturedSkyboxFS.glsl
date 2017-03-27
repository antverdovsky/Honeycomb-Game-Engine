#version 410 core

in vec3 out_vs_texCoord; // Texture Coordinates Output
in vec3 out_vs_norm; // The normalized normal vector of the vertex
in vec3 out_vs_pos; // The position of the vertex in the world

out vec4 color; // Fragment color

uniform samplerCube cube;
uniform float gamma;

void main() {
	vec4 texture = texture(cube, out_vs_texCoord);
	vec3 gammaVec3 = vec3(gamma);

    // Set the color of the fragment by fetching from the cube
	color = vec4(pow(texture.rgb, gammaVec3), texture.a);
}