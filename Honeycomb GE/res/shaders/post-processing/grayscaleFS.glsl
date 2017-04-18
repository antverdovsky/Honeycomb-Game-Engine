///
/// This Fragment Shader is used for inverting the specified Texture (ideally
/// the final texture which is rendered to the screen).
///

#version 410 core

#include <../standard/vertex/stdVertexFS.glsl>

uniform sampler2D gBufferFinal;

out vec4 fragColor;

void main() {
    // Grayscale the Color
    fragColor = texture2D(gBufferFinal, vertexIn.texCoords0);
    float avg = 
        0.2126F * fragColor.x + 
        0.7152F * fragColor.y + 
        0.0722F * fragColor.z;
    
    fragColor = vec4(avg, avg, avg, 1.0F);
}