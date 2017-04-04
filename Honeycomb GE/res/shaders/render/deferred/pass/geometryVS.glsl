///
/// This Vertex Shader is used for processing the specified vertex position,
/// texture coordinates, and normals, and outputting the processed information
/// for the fragment shader. The Shader takes into account the projection of
/// the Camera and the trasnformation of the Object when processing the
/// vertex.
///

#version 410 core

#include <../../../standard/include/stdCamera.glsl>

// Retrieves the position, texture coordinate, and normal of the Vertex from
// the specified vertex attribute array pointers (see Mesh.cpp)
layout (location = 0) in vec3 in_vs_pos;
layout (location = 1) in vec2 in_vs_texCoord;
layout (location = 2) in vec3 in_vs_norm;
layout (location = 3) in vec3 in_vs_tangent;

uniform mat4 objTransform;		// Transform Matrix (pos, rot, scl)

uniform Camera camera;			// Camera Structure

out vec2 out_vs_texCoord;		// Texture Coordinates Output
out vec3 out_vs_norm;			// The normalized normal vector of the vertex
out vec3 out_vs_pos;			// The position of the vertex in the world
out vec3 out_vs_tangent;		// The tangent vector of the vertex
out vec3 out_vs_bitangent;		// The bitangent vector of the vertex

out mat3 out_vs_tbnMatrix;		// Tangent-Bitangent-Normal Matrix

void main() {
	// Fetch position and texture coordinates
    out_vs_pos = (objTransform * vec4(in_vs_pos, 1.0F)).xyz;
	out_vs_texCoord = in_vs_texCoord;
	
	// Fetch the Normals & Tangents of the Vertex, use them to calculate the
	// perpendicular bitangent.
	out_vs_norm = normalize(objTransform * vec4(in_vs_norm, 0.0F)).xyz;
	out_vs_tangent = normalize(objTransform * vec4(in_vs_tangent, 0.0F)).xyz;
	out_vs_bitangent = cross(out_vs_tangent, out_vs_norm);

	// Construct the TBN Matrix
	out_vs_tbnMatrix = transpose(
		mat3(out_vs_tangent, out_vs_bitangent, out_vs_norm));
    
	// The position of each vertex equals to the transformation matrix
    // mutliplied with the vector representing the original position.
    gl_Position = camera.projection * objTransform * vec4(in_vs_pos, 1.0);
}
