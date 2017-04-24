#version 410 core

#include <../../../../standard/structs/stdCamera.glsl>
#include <../../../../standard/vertex/stdVertexVS.glsl>

uniform mat4 objTransform; // Transform Matrix (pos, rot, scl)
uniform Camera camera; // Camera Structure

uniform float lvRange;	// Light volume range for point and spot lights

void main() {
	mat4 sclMatrix = mat4(lvRange);
	sclMatrix[3][3] = 1.0F;
	mat4 sclTransform = objTransform * sclMatrix;

	gl_Position = camera.projection * sclTransform * vertexIn.position;

	vertexOut.position = (sclTransform * vertexIn.position).xyz;
}