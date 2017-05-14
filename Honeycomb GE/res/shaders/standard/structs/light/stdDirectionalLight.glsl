#ifndef STD_DIRECTIONAL_LIGHT_GLSL
#define STD_DIRECTIONAL_LIGHT_GLSL

#include <stdBaseLight.glsl>

///
/// The directional light structure.
///
struct DirectionalLight {
    BaseLight base; // The base component of the light
	Shadow shadow;	// The shadow component of the light
    
    vec3 direction; // The direction of the light
};

/// Checks if the fragment is in shadow of the specified directional light.
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec4 coords : Coordinates using which to sample the 2D texture map.
/// DirectionalLight dL : The directional light for which the shadow is to be
///                       computed.
/// vec3 norm : The normal of the fragment on which the light casts.
/// return : A value between [0.0F, 1.0F] where 1.0F is fully in shadow and
///          0.0F is fully not in shadow.
float isInShadow(sampler2D map, vec4 coords, DirectionalLight dL, vec3 norm) {
	// If the light uses no shadows, all fragments are outside of the shadow so
	// always return 0.0F.
	int shadowType = dL.shadow.shadowType;
	if (dL.shadow.shadowType == SHADOW_TYPE_NONE) return 0.0F;

	// Calculate the bias using the diffuse component to reduce shadow acne
	float diffuse = 1.0F - max(dot(-dL.direction, norm), 0.0F);
	float bias = max(dL.shadow.maxBias * diffuse, dL.shadow.minBias);

	// Convert the coordinates from light coordinates to texture coordinates.
	vec3 correctedCoords = coords.xyz / coords.w;		// to [-1,  1]
	correctedCoords = correctedCoords * 0.5F + 0.5;		// to [ 0,  1]

	// Get the texture coordinates and the current depth value of the fragment 
	// in relation to the light.
	vec2 texCoords = correctedCoords.xy;
	float curDepth = correctedCoords.z;

	// Pick the correct algorithm for the shadow calculation and return the
	// result.
	return isInShadow2D(map, texCoords, bias, curDepth, shadowType);
}

#endif