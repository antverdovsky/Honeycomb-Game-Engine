#version 330 core

#include <../../include/stdCamera.glsl>

// Retrieves the position, texture coordinate, and normal of the Vertex from
// the specified vertex attribute array pointers (see Mesh.cpp)
layout (location = 0) in vec3 in_vs_pos;
layout (location = 1) in vec2 in_vs_texCoord;
layout (location = 2) in vec3 in_vs_norm;

uniform mat4 objTransform = mat4(1.0); // Transform Matrix (pos, rot, scl)

uniform Camera camera;

out vec2 out_vs_texCoord; // Texture Coordinates Output
out vec3 out_vs_norm; // The normalized normal vector of the vertex
out vec3 out_vs_pos; // The position of the vertex in the world

void main() {
    // The position of each vertex equals to the transformation matrix
    // mutliplied with the vector representing the original position.
    gl_Position = camera.projection * objTransform * vec4(in_vs_pos, 1.0);

	out_vs_texCoord = in_vs_texCoord;
	out_vs_norm = normalize(objTransform * vec4(in_vs_norm, 0.0F)).xyz;
    out_vs_pos = (objTransform * vec4(in_vs_pos, 1.0F)).xyz;
}