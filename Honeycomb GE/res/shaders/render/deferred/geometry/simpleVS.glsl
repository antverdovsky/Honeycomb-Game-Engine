///
/// This Vertex Shader is used for rendering vertices without taking into 
/// account any projection or transformations.
///

#version 410 core

#include <../../../standard/vertex/stdVertexVS.glsl>

out vec2 out_vs_texCoord; // Texture Coordinates Output
out vec3 out_vs_norm; // The normalized normal vector of the vertex
out vec3 out_vs_pos; // The position of the vertex in the world

void main() {
	vertexOut.texCoords0 = vertexIn.texCoords0;
	vertexOut.normal = normalize(vertexIn.normal).xyz;
    vertexOut.position = vertexIn.position.xyz;
    
    gl_Position = vertexIn.position;
}