#version 410 core

#include <../../../../standard/structs/stdCamera.glsl>
#include <../../../../standard/vertex/stdVertexVS.glsl>

#define PI 3.1415926535897932384626433832795

uniform mat4 objTransform; // Transform Matrix (pos, rot, scl)
uniform Camera camera; // Camera Structure

uniform float lvRange;	    // Light volume range for point and spot lights
uniform float lvSpotAngle;  // Light volume cone angle for spot lights

void main() {
	// Set the scale matrix so that the X and Y scale varies by spot light
	// angle and the Z scale varies by the spot light range. For point lights,
	// the spot angle should be PI and so the scale will vary only by the range
	// on all axes.
	mat4 sclMatrix = mat4(1.0F);
	sclMatrix[0][0] = cos((PI - lvSpotAngle) / 2.0F) * lvRange;
	sclMatrix[1][1] = cos((PI - lvSpotAngle) / 2.0F) * lvRange;
	sclMatrix[2][2] = lvRange;
	mat4 sclTransform = objTransform * sclMatrix;

	gl_Position = camera.projection * sclTransform * vertexIn.position;

	vertexOut.position = (sclTransform * vertexIn.position).xyz;
}