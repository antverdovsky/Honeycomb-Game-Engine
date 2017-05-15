#version 330 core

#include <../../../standard/vertex/stdVertexFS.glsl>

out vec4 color;

uniform vec3 lightPos;    // The world position of the light
uniform float zFar;       // The far plane of the shadow render box

void main() {
	// Get the distance between the fragment and the light
	vec3 fragToLight = vertexIn.position - lightPos;
	float dist = length(fragToLight);

	// Divide the distance by the zFar value to map the distance between [0, 1]
	float depthDist = dist / zFar;

	// Fetch the Depth value and calculate the partial derivatives of the depth
	// with respect to X and Y coordinates.
	float depth = depthDist;
	float depth2 = depth * depth;
	float dX = dFdx(depth);
	float dY = dFdy(depth);

	// Write the depth to the depth buffer
	gl_FragDepth = depthDist;
	color = vec4(depth, depth2 + 0.25F * (dX * dX + dY * dY), 0.0F, 0.0F);
}