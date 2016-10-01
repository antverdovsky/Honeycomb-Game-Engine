//
// Test Vertex Shader 3
//
// Shader which allows for the transformation of verticies.
// 

#version 330 core

// Tells OpenGL to look for the position in the 0th index of the vertex
// attribute array (see Mesh.cpp).
layout(location = 0) in vec3 pos;

uniform mat4 transform = mat4(1.0); // Transform Matrix (pos, rot, scl)

void main() {
    // Set the new position of the vertex according the transformation, and the
	// original position.
	gl_Position = transform * vec4(pos, 1.0);
}