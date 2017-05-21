#ifndef STD_BASE_LIGHT_GLSL
#define STD_BASE_LIGHT_GLSL

#include <../../light/shadows2d/shadowHard.glsl>
#include <../../light/shadows2d/shadowInterpolated.glsl>
#include <../../light/shadows2d/shadowPCF.glsl>
#include <../../light/shadows2d/shadowPCFInterpolated.glsl>
#include <../../light/shadows2d/shadowVariance.glsl>

// Shadow Type "enumeration"
const int SHADOW_TYPE_NONE						= 0;

const int SHADOW_TYPE_HARD  					= 1;
const int SHADOW_TYPE_INTERPOLATED				= 2;
const int SHADOW_TYPE_PCF						= 3;
const int SHADOW_TYPE_PCF_INTERPOLATED			= 4;

const int SHADOW_TYPE_VARIANCE					= 5;
const int SHADOW_TYPE_VARIANCE_AA               = 6;

///
/// The basic structure for all lights.
/// 
struct BaseLight {
    vec3 color;		 // The color of the light
    float intensity; // The intensity of the light
};

///
/// The attenuation structure for non-uniform lights.
///
struct Attenuation {
	float constant;  // The constant coefficient in the attenuation equation
	float linear;	 // The linear coefficient in the attenuation equation
	float quadratic; // The quadratic coefficient in the attenuation equation
};

///
/// The structure for a shadow.
/// 
struct Shadow {
	int shadowType;	 // The type of shadow cast by this Light
	mat4 projection; // The projection of the Shadow

	float intensity; // The intensity of the Shadow
	float softness;  // The softness of the Shadow [0.0F, 1.0F]

	float minBias;	 // Minimum Bias (if light is parallel to surface)
	float maxBias;	 // Maximum Bias (if light is perpendicular to surface)
};

/// Calculates the attenuation of the specified attenuation component at the
/// specified distance.
/// Attenuation atten : The attenuation component.
/// float d : The distance of the fragment from the light.
/// return : The value of the attenuation at the fragment distance given.
float calculateAttenuation(Attenuation atten, float d) {
	return (atten.constant + atten.linear * d + atten.quadratic * d * d);
}

/// Checks if the fragment is in shadow using the specified shadow type
/// algorithm. This method should be used for flat 2D shadow maps (i.e. Spot or
/// Directional Lights only).
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec2 texCoords : Coordinates using which to sample the 2D texture map.
/// float bias : The bias of the shadow.
/// float curDepth : The current depth of the fragment.
/// int shadowType : The shadow to be used.
/// return : A value between [0.0F, 1.0F] where 1.0F is fully in shadow and
///          0.0F is fully not in shadow.
float isInShadow2D(sampler2D map, vec2 texCoords, float bias, float curDepth,
		int shadowType) {
	// Information fetched from the texture is only valid if the Z component of
	// the the texture coordinates is in range [0, 1]. Otherwise, this fragment
	// is not in the texture map so any shadow calculation is unreliable.
	float isValidShadow = float(curDepth >= 0.0F && curDepth <= 1.0F);

	float shadow = 0.0F; // Stores the Shadow Value

	if (shadowType == SHADOW_TYPE_HARD) {
		shadow = sampleShadowHard(map, texCoords, bias, curDepth);
	} else if (shadowType == SHADOW_TYPE_INTERPOLATED) {
		shadow = sampleShadowInterpolated(map, texCoords, bias, curDepth);
	} else if (shadowType == SHADOW_TYPE_PCF) {
		shadow = sampleShadowPCF(map, texCoords, bias, curDepth);
	} else if (shadowType == SHADOW_TYPE_PCF_INTERPOLATED) {
		shadow = sampleShadowPCFInterpolated(map, texCoords, bias, curDepth);
	} else if (shadowType == SHADOW_TYPE_VARIANCE || 
			shadowType == SHADOW_TYPE_VARIANCE_AA) {
		shadow = sampleShadowVariance(map, texCoords, bias, curDepth);
	}

	// Return the Shadow Value multiplied by the validity factor
	return (1.0F - shadow) * isValidShadow;
}

#endif