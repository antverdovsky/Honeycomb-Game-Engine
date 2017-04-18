///
/// This Vertex Shader is used for rendering vertices without taking into 
/// account any projection or transformations.
///

#version 410 core

#include <../standard/include/vertex/stdVertexAttrib.glsl>
#include <../standard/include/vertex/stdVertexOut.glsl>

void main() {
	vertexOut.texCoords0 = in_vs_texCoords0.xy;
	vertexOut.normal = normalize(in_vs_normal).xyz;
    vertexOut.position = in_vs_position.xyz;
    
    gl_Position = in_vs_position;
}