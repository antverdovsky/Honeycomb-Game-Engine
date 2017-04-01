///
/// This Fragment Shader is used for inverting the specified Texture (ideally
/// the final texture which is rendered to the screen).
///

#version 410 core

#include <../standard/include/stdCamera.glsl>
#include <../standard/include/stdMaterial.glsl>

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform sampler2D gBufferFinal;

out vec4 fragColor;

void main() {
    // Invert the Color
    fragColor = vec4(vec3(1.0F - texture2D(gBufferFinal, out_vs_texCoord)), 1.0F);
}