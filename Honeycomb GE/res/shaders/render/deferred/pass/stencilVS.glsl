#version 410 core

#include <../../../standard/include/stdCamera.glsl>
#include <../../../standard/include/vertex/stdVertexAttrib.glsl>
#include <../../../standard/include/vertex/stdVertexOut.glsl>

uniform mat4 objTransform; // Transform Matrix (pos, rot, scl)
uniform Camera camera; // Camera Structure

void main() {
	vertexOut.position = (objTransform * in_vs_position).xyz;
    
	// The position of each vertex equals to the transformation matrix
    // mutliplied with the vector representing the original position.
    gl_Position = camera.projection * objTransform * in_vs_position;
}