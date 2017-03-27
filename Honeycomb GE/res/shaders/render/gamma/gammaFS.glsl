#version 410 core

in vec2 out_vs_texCoord; // Texture Coordinates outputted from Gamma VS

uniform sampler2D gBufferFinal; // The final texture to be gamma corrected

out vec4 color; // The Gamma post-processed output image

uniform float gamma; // The gamma value

void main() {
	// Fetch color from the buffer and compute the gamma corrected color
	vec4 inColor = texture2D(gBufferFinal, out_vs_texCoord);
	vec3 gammaVec3 = vec3(1.0F) / gamma;
	vec3 gammaColor = pow(inColor.rgb, gammaVec3);
	
	// Write gamma corrected color to output but do not modify the alpha!
	color = vec4(gammaColor, inColor.a);
}