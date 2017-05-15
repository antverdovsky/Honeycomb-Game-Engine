#ifndef STD_SPOT_LIGHT_GLSL
#define STD_SPOT_LIGHT_GLSL

#include <stdBaseLight.glsl>

///
/// The spot light structure
///
struct SpotLight {
    BaseLight base;          // The base component of the light
	Shadow shadow;	         // The shadow component of the light
    Attenuation attenuation; // The attenuation of the light

    vec3 position; // The 3D position of the light in the world
    vec3 direction; // The direction of the light in the world
    
    float range; // The range of the light (height of the cone formed by the 
                 // light point and light ray).
    float angle; // The spot angle of the light.
};

/// Checks if the fragment is in shadow of the specified spot light.
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec4 coords : Coordinates using which to sample the 2D texture map.
/// SpotLight sL : The spot light for which the shadow is to be computed.
/// vec3 norm : The normal of the fragment on which the light casts.
/// vec3 pos : The position of the fragment on which the light casts.
/// return : A value between [0.0F, 1.0F] where 1.0F is fully in shadow and
///          0.0F is fully not in shadow.
float isInShadow(sampler2D map, vec4 coords, SpotLight sL, vec3 norm, 
		vec3 pos) {
	// If the light uses no shadows, all fragments are outside of the shadow so
	// always return 0.0F.
	int shadowType = sL.shadow.shadowType;
	if (sL.shadow.shadowType == SHADOW_TYPE_NONE) return 0.0F;

	// Convert the coordinates from light coordinates to texture coordinates.
	vec3 correctedCoords = coords.xyz / coords.w;		// to [-1,  1]
	correctedCoords = correctedCoords * 0.5F + 0.5;		// to [ 0,  1]

	// Get the texture coordinates and the current depth value of the fragment 
	// in relation to the light. When getting the current depth, compute the
	// distance between the fragment and the light and get it into a [0, 1] 
	// range by dividing by the z-far plane (range).
	vec2 texCoords = correctedCoords.xy;
	float curDepth = length(pos - sL.position) / sL.range;

	// Calculate the bias using the distance in order to reduce shadow acne
	float bias = max(sL.shadow.maxBias * curDepth, sL.shadow.minBias);

	// Pick the correct algorithm for the shadow calculation and return the
	// result.
	return isInShadow2D(map, texCoords, bias, curDepth, shadowType);
}

#endif