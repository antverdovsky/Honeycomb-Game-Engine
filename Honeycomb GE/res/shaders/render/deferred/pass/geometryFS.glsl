///
/// This Fragment Shader is used for rendering the position, diffuse, normals,
/// and texture coordinates to their respective color attachments.
///

#version 410 core

#include <../../../standard/include/stdCamera.glsl>
#include <../../../standard/include/stdMaterial.glsl>

// The output of the Geometry Vertex Shader
in vec2 out_vs_texCoord;
in vec3 out_vs_norm;
in vec3 out_vs_pos;
in vec3 out_vs_tangent;
in vec3 out_vs_bitangent;
in mat3 out_vs_tbnMatrix;

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

/// Calculates the Diffuse Color of this object's fragment. NOTE: Diffuse MUST
/// be calculated after the normal has been calculated since the diffuse method
/// will use the OUT_FS_NORMAL, rather than OUT_VS_NORMAL (to allow for bump
/// mapping).
/// return : The diffuse color.
vec3 calculateDiffuse() {
	// Calculate the Reflection Color. To avoid an if statement, calculate the
	// reflection strength as one minus the material's reflection strength.
	// This strength will be one if the material reflection is zero, or zero
	// if the material reflection is one. Then, add the reflected vector to the
	// strength, so that if the strength is one, it remains one (after being
	// clamped) or if the strength is zero, it becomes equal to the reflected
	// vector.
	float matRefStr = clamp(material.reflectionStrength, 0.0F, 1.0F);
	vec3 viewVec = normalize(out_vs_pos - camera.translation);
	vec3 refVec = refract(viewVec, -normalize(out_fs_normal), 
		1.0F / material.refractiveIndex);
	vec3 refStr = vec3(1.0F) - vec3(matRefStr);
	vec3 refTexture = textureCubeSRGB(skybox, refVec, gamma).rgb;
	vec3 reflection = clamp(refStr + refTexture, 0.0F, 1.0F);

	// Fetch material texture & diffuse
	vec2 coord = out_vs_texCoord * material.diffuseTexture.tiling +
		material.diffuseTexture.offset;
	vec3 texture = texture2DSRGB(
		material.diffuseTexture.sampler, coord, gamma).rgb;
	vec3 diffuse = material.diffuseColor.xyz;

	// Return Texture + Diffuse + Reflection
	return texture * diffuse * reflection;
}

/// Calculates the Normal/Bump map vector of this object's fragment.
/// return : The normal vector.
vec3 calculateNormal() {
	// Fetch the standard interpolated vertex shader normal
	vec3 vsNorm = normalize(out_vs_norm);

	// Fetch texture value from the Normal Map of the Material
	vec2 texCoord = out_vs_texCoord * material.normalsTexture.tiling +
		material.normalsTexture.offset;
	vec3 tex = texture2D(material.normalsTexture.sampler, texCoord).xyz;
	vec3 texNorm = tex;

	// Convert the Normal Map texture from the range of [0, 1] to [-1, 1] since
	// a normal can be negative or positive.
	texNorm = (texNorm * 2.0F) - 1.0F;

	// Orient the normal map according to the Tangent-Bitangent-Normal Matrix
	texNorm = normalize(out_vs_tbnMatrix * texNorm);
	
	// Multiply by the ceiling of the original texture value. If this object
	// has a texture map, the ceiling of the texture will be a { 1, 1, 1 }
	// white vector, and will therefore not modify the texture map. If this
	// object does not have a texture map, the ceiling of the texture will be
	// { 0, 0, 0 } and will therefore nullify the texture map.
	texNorm = ceil(tex) * texNorm;

	// Now do the opposite of the above to the interpolated normal. If this
	// object has a texture map, one minus the ceiling will be { 0, 0, 0 } and
	// therefore the interpolated normal will be zero. If this object has no
	// texture map, one minus the ceiling will be { 1, 1, 1 } and therefore the
	// interpolated normal is not modified.
	vsNorm = (vec3(1.0F) - ceil(tex)) * vsNorm;

	// Since either vsNorm is zero or texNorm is zero, but not both, sum them
	// up and the result will be equal to the non zero value, which is the one
	// we want.
	return texNorm + vsNorm;
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
    out_fs_normal = calculateNormal();
	out_fs_specular = calculateSpecular();
    out_fs_diffuse = calculateDiffuse();
    
	out_fs_pos = out_vs_pos;
    out_fs_texCoord = vec3(out_vs_texCoord, 0.0F);
}
