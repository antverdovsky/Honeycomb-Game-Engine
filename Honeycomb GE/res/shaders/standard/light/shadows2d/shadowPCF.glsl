#ifndef SHADOW_PCF_GLSL
#define SHADOW_PCF_GLSL

/// Samples the specified shadow map at the specified coordinates using
/// percentage-closer filtering (PCF).
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec2 coords : The coordnates at which to sample the shadow map.
/// float bias : The shadow bias value.
/// float curDepth : The current depth from the projection coordinates.
/// return : 1.0F if the fragment is in shadow, 0.0F otherwise.
float sampleShadowPCF(sampler2D map, vec2 coords, float bias, float curDepth);

float sampleShadowPCF(sampler2D map, vec2 coords, float bias, float curDepth) {
	// The number of samples used for PCF.
	const int SAMPLE_COUNT = 1 * 3;	// DO NOT modify the value 3
	const int SAMPLE_COUNT_SQRD = SAMPLE_COUNT * SAMPLE_COUNT;

	// Get the texel size (inverse of the pixel size of the shadow map)
	vec2 offset = 1.0F / textureSize(map, 0);
	
	// Stores the final shadow map depth value
	float shadow = 0.0F;

	// Loop through all of the surrounding pixels and the current pixel
	for (int i = 0; i < SAMPLE_COUNT_SQRD; ++i) {
		// Get the x and y offsets from the current pixel ([-1, 1])
		int x = i / SAMPLE_COUNT - 1;
		int y = i % SAMPLE_COUNT - 1;

		// Fetch the depth from the shadow texture map at the current pixel
		vec2 offsetCoord = coords + vec2(x, y) * offset;
		float textureDepth = texture2D(map, offsetCoord).r;

		// If the current depth is greater than the shadow depth then the 
		// fragment is currently farther away from the light than according to 
		// the shadow map. This implies the fragment is in shadow, therefore,
		// increment the shadow value.
		shadow += step(curDepth - bias, textureDepth);
	}

	// Since we sampled 9 pixels in total (8 surrounding + 1 center), we divide
	// the shadow value by 9 to get the average shadow value.
	return shadow / SAMPLE_COUNT_SQRD;
}

#endif