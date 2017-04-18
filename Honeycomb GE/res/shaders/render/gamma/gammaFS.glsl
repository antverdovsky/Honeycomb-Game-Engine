#version 410 core

#include <../../standard/vertex/stdVertexFS.glsl>

uniform sampler2D gBufferFinal; // The final texture to be gamma corrected
uniform float gamma; // The gamma value

out vec4 color; // The Gamma post-processed output image

void main() {
	// Fetch color from the buffer and compute the gamma corrected color
	vec4 inColor = texture2D(gBufferFinal, vertexIn.texCoords0);
	vec3 gammaVec3 = vec3(1.0F) / gamma;
	vec3 gammaColor = pow(inColor.rgb, gammaVec3);
	
	// Write gamma corrected color to output but do not modify the alpha!
	color = vec4(gammaColor, inColor.a);
}