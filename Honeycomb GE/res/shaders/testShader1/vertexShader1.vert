//
// Test Vertex Shader 1
//
// Sets the position of each vertex to the position defined in the vertex
// attribute array, and nothing else.
// 

#version 330 core

// Tells OpenGL to look for the position in the 0th index of the vertex
// attribute array (see Mesh.cpp).
layout(location = 0) in vec3 pos;

void main() {
    // Set the position of each vertex to the position found above.
    gl_Position = vec4(0.25 * pos, 1.0);
}