///
/// This Fragment Shader is used for rendering the position, diffuse, normals,
/// and texture coordinates to their respective color attachments.
///

#version 410 core

#include <..\..\..\standard\include\stdCamera.glsl>
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

uniform Material material;  // Standard Material of the Object
uniform samplerCube skybox; // Skybox for Reflection
uniform Camera camera;      // Scene Camera
uniform float gamma;		// Gamma value for reading in textures

/// Calculates the Diffuse Color of this object's fragment.
/// return : The diffuse color.
vec3 calculateDiffuse() {
	vec3 gammaVec3 = vec3(gamma);

	// Calculate the Reflection Color
	float matRefStr = clamp(material.reflectionStrength, 0.0F, 1.0F);
	vec3 viewVec = normalize(out_vs_pos - camera.translation);
	vec3 refVec = refract(viewVec, -normalize(out_vs_norm), 
		1.0F / material.refractiveIndex);
	vec3 refStr = vec3(1.0F) - vec3(matRefStr);
	vec4 refTexture = texture(skybox, refVec);
	vec3 reflection = refStr + pow(refTexture.xyz, gammaVec3);

	// Fetch material texture & diffuse
	vec2 texCoord = out_vs_texCoord * material.diffuseTexture.tiling +
		material.diffuseTexture.offset;
	vec3 texture = pow(
		texture2D(material.diffuseTexture.sampler, texCoord).xyz, gammaVec3);
	vec3 diffuse = material.diffuseColor.xyz;

	// Return Texture + Diffuse + Reflection
	return texture * diffuse * reflection;
}

/// Calculates the Specular Color and shininess of this object's fragment.
/// return : The specular color and shininess.
vec4 calculateSpecular() {
	// Fetch Specular properties from the Materials
	vec3 color = material.specularColor;
	vec2 texCoord = out_vs_texCoord * material.specularTexture.tiling +
		material.specularTexture.offset;
	vec3 tex = texture2D(material.specularTexture.sampler, texCoord).xyz;
	float shine = material.shininess;

	// Return Color + Texture, Shininess
	return vec4(tex * color, shine);
}

void main() {
    out_fs_pos = out_vs_pos;
    out_fs_diffuse = calculateDiffuse();
    out_fs_normal = out_vs_norm;
    out_fs_texCoord = vec3(out_vs_texCoord, 0.0F);
	out_fs_specular = calculateSpecular();
}