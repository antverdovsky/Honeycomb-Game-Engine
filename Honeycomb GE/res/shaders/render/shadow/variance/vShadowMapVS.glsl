#version 330 core

#include <../../../standard/vertex/stdVertexVS.glsl>
#include <../../../standard/structs/stdCamera.glsl>
#include <../../../standard/structs/stdMaterial.glsl>

uniform Camera camera;
uniform mat4 lightProjection;
uniform mat4 objTransform;
uniform Material material;			// tmp... need to get rid of this but MeshRenderer requires it for now

void main() {
	float a = material.refractiveIndex;

	gl_Position = lightProjection * objTransform * vertexIn.position;
	vertexOut.position = (objTransform * vertexIn.position).xyz;
}
