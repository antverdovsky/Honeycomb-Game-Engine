//
// Sets the color of the fragment to the color indicated by the Texture.
//

#version 330 core

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS

uniform vec3 albedoColor = vec3(1.0F);
uniform sampler2D textureSampler; // Texture Sampler2D

void main() {
	// Set the color to the color provided by the Texture
	gl_FragColor = vec4(albedoColor, 1.0F) * 
		texture2D(textureSampler, out_vs_texCoord);
}