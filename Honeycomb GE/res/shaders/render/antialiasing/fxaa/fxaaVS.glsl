#version 410 core

// Retrieves the position, texture coordinate, and normal of the Vertex from
// the specified vertex attribute array pointers (see Mesh.cpp)
layout (location = 0) in vec3 in_vs_pos;
layout (location = 1) in vec2 in_vs_texCoord;
layout (location = 2) in vec3 in_vs_norm;

out vec2 out_vs_texCoord; // Texture Coordinates Output
out vec3 out_vs_norm; // The normalized normal vector of the vertex
out vec3 out_vs_pos; // The position of the vertex in the world

void main() {
	out_vs_texCoord = in_vs_texCoord;
	out_vs_norm = normalize(in_vs_norm);
    out_vs_pos = in_vs_pos;
    
    gl_Position = vec4(in_vs_pos, 1.0);
}