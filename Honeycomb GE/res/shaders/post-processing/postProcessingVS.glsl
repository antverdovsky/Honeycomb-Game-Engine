///
/// This Vertex Shader is used for rendering vertices without taking into 
/// account any projection or transformations.
///

#version 410 core

#include <../standard/vertex/stdVertexVS.glsl>

void main() {
	vertexOut.texCoords0 = vertexIn.texCoords0;
	vertexOut.normal = normalize(vertexIn.normal).xyz;
    vertexOut.position = vertexIn.position.xyz;
    
    gl_Position = vertexIn.position;
}