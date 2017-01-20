///
/// This Fragment Shader is used for rendering the position, diffuse, normals,
/// and texture coordinates to their respective color attachments.
///

#version 410 core

#include <..\..\..\standard\include\stdMaterial.glsl>

// The output of the Geometry Vertex Shader
in vec2 out_vs_texCoord;
in vec3 out_vs_norm;
in vec3 out_vs_pos;

// Outputs correlating to the texture ID in the G-Buffer
layout (location = 0) out vec3 out_fs_pos;
layout (location = 1) out vec3 out_fs_diffuse;
layout (location = 2) out vec3 out_fs_normal;
layout (location = 3) out vec3 out_fs_texCoord;
layout (location = 4) out vec4 out_fs_specular;

uniform Material material; // Standard Material

void main() {
    out_fs_pos = out_vs_pos;
    out_fs_diffuse = texture2D(material.albedoTexture, out_vs_texCoord).xyz
		* material.diffuseColor.xyz;
    out_fs_normal = out_vs_norm;
    out_fs_texCoord = vec3(out_vs_texCoord, 0.0F);
	out_fs_specular = material.specularColor;
}