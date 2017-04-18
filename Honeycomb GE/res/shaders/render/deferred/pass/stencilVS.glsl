///
/// This Vertex Shader is used for processing the specified vertex position and
/// outputting the processed information for the fragment shader. The Shader 
/// takes into account the projection of the Camera and the trasnformation of 
/// the Object when processing the vertex.
///

#version 410 core

#include <../../../standard/include/stdCamera.glsl>

// Retrieves the position, texture coordinate, and normal of the Vertex from
// the specified vertex attribute array pointers (see Mesh.cpp)
layout (location = 0) in vec4 in_vs_pos;

uniform mat4 objTransform; // Transform Matrix (pos, rot, scl)

uniform Camera camera; // Camera Structure

out vec3 out_vs_pos; // Position Output

void main() {
	out_vs_pos = (objTransform * in_vs_pos).xyz;
    
	// The position of each vertex equals to the transformation matrix
    // mutliplied with the vector representing the original position.
    gl_Position = camera.projection * objTransform * in_vs_pos;
}