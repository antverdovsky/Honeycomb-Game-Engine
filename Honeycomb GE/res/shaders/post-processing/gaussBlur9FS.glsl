///
/// This Fragment Shader is used for applying a gaussian blur in either the
/// vertical or horizontal direction.
///

#version 410 core

#include <../standard/vertex/stdVertexFS.glsl>

uniform sampler2D gBufferFinal;

uniform vec2 direction;     // Blur Direction (Horizontal or Vertical)
uniform vec2 resolution;    // Resolution of the Blur Texture
uniform vec2 radius;        // Radius of the Gauss Blur

out vec4 fragColor;

void main() {
    fragColor = vec4(0.0F);

	vec2 blur = radius / resolution; // Compute the blur strength

	// Apply the blurring for the negative side of the texture coordinates
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0 + vec2(-4.0F, -4.0F) * blur * direction) *
		0.0162162162F;
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0 + vec2(-3.0F, -3.0F) * blur * direction) *
		0.0540540541F;
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0 + vec2(-2.0F, -2.0F) * blur * direction) *
		0.1216216216F;
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0 + vec2(-1.0F, -1.0F) * blur * direction) *
		0.1945945946F;

	// Apply the blurring for the pixel at the texture coordinate
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0) * 0.2270270270F;

	// Apply the blurring for the positive side of the texture coordinates
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0 + vec2( 1.0F,  1.0F) * blur * direction) *
		0.1945945946F;
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0 + vec2( 2.0F,  2.0F) * blur * direction) *
		0.1216216216F;
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0 + vec2( 3.0F,  3.0F) * blur * direction) *
		0.0540540541F;
	fragColor += texture2D(gBufferFinal,
		vertexIn.texCoords0 + vec2( 4.0F,  4.0F) * blur * direction) *
		0.0162162162F;
}