//
// Sets the color of the fragment to the color indicated by the Texture.
//

#version 330 core

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS

uniform sampler2D textureSampler; // Texture Sampler2D

void main() {
	// Set the color to the color provided by the Texture
	// gl_FragColor = vec4(0.0F, 1.0F, 0.0F, 1.0F);
	gl_FragColor = texture2D(textureSampler, out_vs_texCoord) + vec4(0.1F, 0.1F, 0.1F, 1.0F);
}