///
/// This Fragment Shader is used for shading the fragment with the given
/// texture.
///

#version 410 core

// The output of the Vertex Shader
in vec2 out_vs_texCoord;
in vec3 out_vs_norm;
in vec3 out_vs_pos;

uniform sampler2D fsTexture; // Texture to be used

void main() {
    gl_FragColor = texture2D(fsTexture, out_vs_texCoord);
}