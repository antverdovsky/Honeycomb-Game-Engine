#version 330

layout (location = 0) in vec3 ivs_Position;         // Vertex Position Vector
layout (location = 1) in vec2 ivs_TexturePosition;  // Vertex Texture Coords.
layout (location = 2) in vec3 ivs_Normal;           // Vertex Normal Vector

uniform mat4 uvs_Projection = mat4(1.0F);     // Camera Projection Matrix
uniform mat4 uvs_Transformation = mat4(1.0F); // Vertex Transformation Matrix

out vec3 ovs_Position;          // Normalized Vertex Position Vector
out vec3 ovs_Normal;            // Normalized Vertex Normal Vector
out vec2 ovs_TexturePosition;   // Vertex Texture Coords.

void main() {
    // The transformed position of the vertex is equal to the camera
    // projection matrix multiplied by the object transformation matrix
    // multiplied by the original vertex position.
    gl_Position = uvs_Projection * uvs_Transformation * 
        vec4(ivs_Position, 1.0);

	ovs_TexturePosition = ivs_TexturePosition;
	ovs_Normal = normalize(uvs_Transformation * vec4(ivs_Normal, 0.0F)).xyz;
    ovs_Position = (uvs_Transformation * vec4(ivs_Position, 1.0F)).xyz;
}