///
/// This Vertex Shader is used for rendering vertices without taking into 
/// account any projection or transformations.
///

#version 410 core

// Retrieves the position, texture coordinate, and normal of the Vertex from
// the specified vertex attribute array pointers (see Mesh.cpp)
layout (location = 0) in vec4 in_vs_pos;
layout (location = 1) in vec4 in_vs_norm;
layout (location = 3) in vec4 in_vs_texCoord;

out vec2 out_vs_texCoord; // Texture Coordinates Output
out vec3 out_vs_norm; // The normalized normal vector of the vertex
out vec3 out_vs_pos; // The position of the vertex in the world

void main() {
	out_vs_texCoord = in_vs_texCoord.xy;
	out_vs_norm = normalize(in_vs_norm).xyz;
    out_vs_pos = in_vs_pos.xyz;
    
    gl_Position = in_vs_pos;
}