///
/// This Fragment Shader is used for rendering the position, diffuse, normals,
/// and texture coordinates to their respective color attachments.
///

#version 410 core

#include <../../../util/packing.glsl>
#include <../../../standard/structs/stdCamera.glsl>
#include <../../../standard/structs/stdMaterial.glsl>
#include <../../../standard/vertex/stdVertexFS.glsl>

// Outputs correlating to the texture ID in the G-Buffer
layout (location = 0) out vec3 out_fs_pos;
layout (location = 1) out vec3 out_fs_normal;
layout (location = 2) out vec4 out_fs_material;

uniform Material material;  // Standard Material of the Object
uniform Camera camera;      // Scene Camera
uniform samplerCube skybox; // Skybox for Reflection
uniform float gamma;		// Gamma value for reading in textures

vec2 displacedTexCoords;	// Parallax Displaced Tex Coords for this Fragment

/// Calculates the Reflection color of this object's fragment.
/// return : The reflection color.
vec3 calculateReflection() {
	// Calculate the Reflection Color. To avoid an if statement, calculate the
	// reflection strength as one minus the material's reflection strength.
	// This strength will be one if the material reflection is zero, or zero
	// if the material reflection is one. Then, add the reflected vector to the
	// strength, so that if the strength is one, it remains one (after being
	// clamped) or if the strength is zero, it becomes equal to the reflected
	// vector. (
	// Note on Normals: out_fs_normal should be computed prior to this!)
	vec3 viewVec = normalize(vertexIn.position - camera.translation);
	float matRefStr = clamp(material.reflectionStrength, 0.0F, 1.0F);
	vec3 refVec = refract(viewVec, -normalize(vertexIn.normal), 
		1.0F / material.refractiveIndex);
	vec3 refStr = vec3(1.0F) - vec3(matRefStr);
	vec3 refTexture = textureCubeSRGB(skybox, refVec, gamma).rgb;
	vec3 reflection = clamp(refStr + refTexture, 0.0F, 1.0F);

	return reflection;
}

/// Calculates the Ambient Color of this object's fragment.
/// return : The ambient color.
vec3 calculateAmbient() {
	// Fetch material texture & ambient
	vec3 tex = texture2DSRGB(material.ambientTexture.sampler, 
		displacedTexCoords, gamma).rgb;
	vec3 ambient = material.ambientColor.xyz;

	// Return Texture + Ambient
	return tex * ambient;
}

/// Calculates the Albedo Color of this object's fragment.
/// return : The albedo color.
vec3 calculateAlbedo() {
	// Fetch material texture & albedo
	vec3 tex = texture2DSRGB(material.albedoTexture.sampler, 
		displacedTexCoords, gamma).rgb;
	vec3 albedo = material.albedoColor.xyz;

	// Return Texture + Albedo
	return tex * albedo;
}

/// Calculates the Diffuse Color of this object's fragment.
/// return : The diffuse color.
vec3 calculateDiffuse() {
	// Fetch material texture & diffuse
	vec3 tex = texture2DSRGB(material.diffuseTexture.sampler, 
		displacedTexCoords, gamma).rgb;
	vec3 diffuse = material.diffuseColor.xyz;

	// Return Texture + Diffuse
	return tex * diffuse;
}

/// Calculates the Normal/Bump map vector of this object's fragment.
/// return : The normal vector.
vec3 calculateNormal() {
	// Fetch the standard interpolated vertex shader normal
	vec3 vsNorm = normalize(vertexIn.normal);

	// Fetch texture value from the Normal Map of the Material
	vec3 tex = texture2DSRGB(material.normalsTexture.sampler, 
		displacedTexCoords, 1.0F).rgb;
	vec3 texNorm = tex;

	// Convert the Normal Map texture from the range of [0, 1] to [-1, 1] since
	// a normal can be negative or positive.
	texNorm = normalize((tex * 2.0F) - vec3(1.0F));

	// Orient the normal map according to the Tangent-Bitangent-Normal Matrix
	texNorm = normalize(vertexIn.tbnMatrix * texNorm);

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
	vec3 tex = texture2DSRGB(material.specularTexture.sampler, 
		vertexIn.texCoords0, 1.0F).rgb;
	float shine = clamp(material.shininess / 255.0F, 0.0F, 1.0F);

	// Return Color + Texture, Shininess
	return vec4(tex * color, shine);
}

vec4 calculateMaterial() {
	vec3 reflectionVec = calculateReflection();

	vec3 albedoVec = calculateAlbedo() * reflectionVec;
	vec3 ambientVec = calculateAmbient() * albedoVec;
	vec3 diffuseVec = calculateDiffuse() * albedoVec;
	vec4 specularVec = calculateSpecular();

	float albF = packRGB(albedoVec);
	float ambF = packRGB(ambientVec);
	float difF = packRGB(diffuseVec);
	float specF = packRGBA(specularVec);

	return vec4(albF, ambF, difF, specF);
}

void main() {
	// Calculate Parallax Displaced Texture Coordinates once
	vec3 viewVec = normalize(vertexIn.position - camera.translation);
	displacedTexCoords = getTextureCoordinates(material, vertexIn.texCoords0);
	displacedTexCoords = parallaxTransform(material.displacementTexture,
		displacedTexCoords, viewVec, vertexIn.tbnMatrix);

    out_fs_normal = calculateNormal();
    out_fs_material = calculateMaterial();
    
	out_fs_pos = vertexIn.position;
}
