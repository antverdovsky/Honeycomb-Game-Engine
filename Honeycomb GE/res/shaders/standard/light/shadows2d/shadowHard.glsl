#ifndef SHADOW_HARD_GLSL
#define SHADOW_HARD_GLSL

/// Samples the specified shadow map at the specified coordinates with no
/// antialiasing or special filtering.
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec2 coords : The coordnates at which to sample the shadow map.
/// float bias : The shadow bias value.
/// float curDepth : The current depth from the projection coordinates.
/// return : 1.0F if the fragment is in shadow, 0.0F otherwise.
float sampleShadowHard(sampler2D map, vec2 coords, float bias, float curDepth);

float sampleShadowHard(sampler2D map, vec2 coords, float bias, 
		float curDepth) {
	// Get the depth value of the fragment from the shadow map
	float textureDepth = texture2D(map, coords).r;

	// If the current depth is less than the texture depth, the fragment is not
	// in shadow, so return 0.0F. Otherwise, the fragment is in shadow, so
	// return 1.0F.
	return step(curDepth - bias, textureDepth);
}

#endif