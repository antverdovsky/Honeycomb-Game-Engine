//
// Test Vertex Shader 2
//
// Scales the position of the vertex by the test uniform float.
// 

#version 330 core

// Tells OpenGL to look for the position in the 0th index of the vertex
// attribute array (see Mesh.cpp).
layout(location = 0) in vec3 pos;

// Uniform which scaled the position of the vertex.
uniform float uni_scale = 0.5;

void main() {
    // Set the position of each vertex to the position found above.
    //gl_Position = vec4(uni_scale * pos, 1.0);
    gl_Position = vec4(uni_scale * pos, 1.0);
}