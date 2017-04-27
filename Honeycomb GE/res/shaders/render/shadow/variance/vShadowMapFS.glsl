#version 330 core

out vec4 color;

void main() {
	// Fetch the Depth value and calculate the partial derivatives of the depth
	// with respect to X and Y coordinates.
	float depth = gl_FragCoord.z;
	float depth2 = depth * depth;
	float dX = dFdx(depth);
	float dY = dFdy(depth);

	color = vec4(depth, depth2 + 0.25F * (dX * dX + dY * dY), 0.0F, 0.0F);
}