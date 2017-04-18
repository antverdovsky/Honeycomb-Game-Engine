///
/// This Fragment Shader is used for inverting the specified Texture (ideally
/// the final texture which is rendered to the screen).
///

#version 410 core

#include <../standard/vertex/stdVertexFS.glsl>

uniform sampler2D gBufferFinal;

out vec4 fragColor;

const float offset = 1.0F / 300.0F;

void main() {
    // Construct an array of all of the offsets which will be used to sample
    // the surrounding pixels.
    vec2 offsets[9] = vec2[](
        vec2(-offset,    offset),  // Top Left Pixel
        vec2(   0.0f,    offset),  // Top Center Pixel
        vec2( offset,    offset),  // Top Right Pixel
        vec2(-offset,      0.0f),  // Center Left Pixel
        vec2(   0.0f,      0.0f),  // Center Center Pixel 
        vec2( offset,      0.0f),  // Center Right Pixel
        vec2(-offset,   -offset),  // Bottom Left Pixel
        vec2(   0.0f,   -offset),  // Bottom Center Pixel
        vec2( offset,   -offset)   // Bottom Right Pixel
    );
    
    // Construct the Sharpen Kernel
    float kernel[9] = float[](
        -1,     -1,     -1,
        -1,      9,     -1,
        -1,     -1,     -1
    );
    
    // Sample all of the surrounding fragments
    vec4 sampledPixels[9];
    for (int i = 0; i < 9; ++i) {
        vec2 offsetCoord = vertexIn.texCoords0 + offsets[i];
        sampledPixels[i] = texture2D(gBufferFinal, offsetCoord);
    }
    
    // Clear the fragment color and sum all of the surrounding fragments
    // multiplied by the Kernel.
    fragColor = vec4(0.0F, 0.0F, 0.0F, 0.0F);
    for (int i = 0; i < 9; ++i) {
        vec4 pixColor = sampledPixels[i] * kernel[i];
        fragColor += pixColor;
    }
}