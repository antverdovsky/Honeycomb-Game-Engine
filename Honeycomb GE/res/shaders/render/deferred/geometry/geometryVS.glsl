///
/// This Vertex Shader is used for processing the specified vertex position,
/// texture coordinates, and normals, and outputting the processed information
/// for the fragment shader. The Shader takes into account the projection of
/// the Camera and the trasnformation of the Object when processing the
/// vertex.
///

#version 410 core

#include <../../../standard/structs/stdCamera.glsl>
#include <../../../standard/vertex/stdVertexVS.glsl>

uniform mat4 objTransform;		// Transform Matrix (pos, rot, scl)
uniform Camera camera;			// Camera Structure

void main() {
	// Fetch position and texture coordinates
    vertexOut.position = (objTransform * vertexIn.position).xyz;
	vertexOut.texCoords0 = vertexIn.texCoords0;
	
	// Fetch the Normals & Tangents of the Vertex, use them to calculate the
	// perpendicular bitangent. JIC, reorthagonize the tangent vector using the
	// Gram-Schmidt process.
	vertexOut.normal = normalize(objTransform * vertexIn.normal).xyz;
	vertexOut.tangent = normalize(objTransform * vertexIn.tangent).xyz;
	vertexOut.tangent = normalize(vertexOut.tangent - 
		dot(vertexOut.tangent, vertexOut.normal) * vertexOut.normal);
	vertexOut.bitangent = cross(vertexOut.tangent, vertexOut.normal);

	// Construct the TBN Matrix
	vertexOut.tbnMatrix = mat3(
		vertexOut.tangent, 
		vertexOut.bitangent, 
		vertexOut.normal);
    
	// The position of each vertex equals to the transformation matrix
    // mutliplied with the vector representing the original position.
    gl_Position = camera.projection * objTransform * vertexIn.position;
}
