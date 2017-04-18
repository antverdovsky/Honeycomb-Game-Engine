///
/// This Fragment Shader is used for inverting the specified Texture (ideally
/// the final texture which is rendered to the screen).
///

#version 410 core

#include <../standard/vertex/stdVertexFS.glsl>

uniform sampler2D gBufferFinal;

out vec4 fragColor;

void main() {
    // Invert the Color
    fragColor = vec4(vec3(
		1.0F - texture2D(gBufferFinal, vertexIn.texCoords0)), 1.0F);
}