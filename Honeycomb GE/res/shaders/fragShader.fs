//
// Sets the color of the fragment to the color indicated by the Texture.
//

#version 330 core

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS

uniform sampler2D textureSampler; // Texture Sampler2D

out vec4 out_fs_color; // The output color

void main() {
	// Set the color to the color provided by the Texture
	out_fs_color = texture(textureSampler, out_vs_texCoord);
}