///
/// This Fragment Shader is used for inverting the specified Texture (ideally
/// the final texture which is rendered to the screen).
///

#version 410 core

#include <..\standard\include\stdCamera.glsl>
#include <..\standard\include\stdMaterial.glsl>

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform Material material;          // TODO: Deprecated but will print errors if not found!
uniform Camera camera;

uniform sampler2D gBufferFinal;

out vec4 fragColor;

void main() {
    // Grayscale the Color
    fragColor = texture2D(gBufferFinal, out_vs_texCoord);
    float avg = 
        0.2126F * fragColor.x + 
        0.7152F * fragColor.y + 
        0.0722F * fragColor.z;
    
    fragColor = vec4(avg, avg, avg, 1.0F);
}