///
/// This Vertex Shader is used for processing the specified vertex position,
/// texture coordinates, and normals, and outputting the processed information
/// for the fragment shader. The Shader takes into account the projection of
/// the Camera and the trasnformation of the Object when processing the
/// vertex.
///

#version 410 core

#include <../../../standard/include/stdCamera.glsl>
#include <../../../standard/include/vertex/stdVertexAttrib.glsl>
#include <../../../standard/include/vertex/stdVertexOut.glsl>

uniform mat4 objTransform;		// Transform Matrix (pos, rot, scl)
uniform Camera camera;			// Camera Structure

void main() {
	// Fetch position and texture coordinates
    vertexOut.position = (objTransform * in_vs_position).xyz;
	vertexOut.texCoords0 = in_vs_texCoords0.xy;
	
	// Fetch the Normals & Tangents of the Vertex, use them to calculate the
	// perpendicular bitangent. JIC, reorthagonize the tangent vector using the
	// Gram-Schmidt process.
	vertexOut.normal = normalize(objTransform * in_vs_normal).xyz;
	vertexOut.tangent = normalize(objTransform * in_vs_tangent).xyz;
	vertexOut.tangent = normalize(vertexOut.tangent - 
		dot(vertexOut.tangent, vertexOut.normal) * vertexOut.normal);
	vertexOut.bitangent = cross(vertexOut.tangent, vertexOut.normal);

	// Construct the TBN Matrix
	vertexOut.tbnMatrix = mat3(vertexOut.tangent, 
		vertexOut.bitangent, 
		vertexOut.normal);
    
	// The position of each vertex equals to the transformation matrix
    // mutliplied with the vector representing the original position.
    gl_Position = camera.projection * objTransform * in_vs_position;
}
