#version 410 core

#include <../../../standard/structs/stdCamera.glsl>
#include <../../../standard/vertex/stdVertexVS.glsl>

uniform mat4 objTransform; // Transform Matrix (pos, rot, scl)
uniform Camera camera; // Camera Structure

void main() {
	vertexOut.position = (objTransform * vertexIn.position).xyz;
    
	// The position of each vertex equals to the transformation matrix
    // mutliplied with the vector representing the original position.
    gl_Position = camera.projection * objTransform * vertexIn.position;
}