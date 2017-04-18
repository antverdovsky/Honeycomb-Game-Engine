///
/// This Fragment Shader is used for shading the fragment with the given
/// texture.
///

#version 410 core

#include <../../../standard/include/vertex/stdVertexIn.glsl>

uniform sampler2D fsTexture; // Texture to be used

void main() {
    gl_FragColor = texture2D(fsTexture, vertexIn.texCoords0);
}