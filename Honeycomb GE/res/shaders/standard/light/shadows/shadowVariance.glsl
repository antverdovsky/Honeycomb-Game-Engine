#ifndef SHADOW_VARIANCE_GLSL
#define SHADOW_VARIANCE_GLSL

#include <../../../util/math.glsl>

/// Samples the specified shadow map at the specified coordinates using the
/// variance shadow mapping technique.
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec2 coords : The coordnates at which to sample the shadow map.
/// float bias : The shadow bias value.
/// float curDepth : The current depth from the projection coordinates.
/// return : 1.0F if the fragment is in shadow, 0.0F otherwise.
float sampleShadowVariance(sampler2D map, vec2 coords, float bias,
		float curDepth);

float sampleShadowVariance(sampler2D map, vec2 coords, float bias,
		float curDepth) {
	// Fetch the RG channels of the texture and use them to get the depth and
	// depth ^ 2 values.
	vec2 mapRG = texture2D(map, coords).rg;
	float textureDepth = mapRG.r;
	float textureDepth2 = mapRG.g;
	
	// The probability the texture is in shadow, according to classic shadow
	// mapping. Bias is not really necessary anymore but it's left in for more
	// user control.
	float p = smoothstep(curDepth - bias, curDepth, textureDepth);

	// Calculate the Variance value for Chebyshev's Inequality
	float variance = max(textureDepth2 - textureDepth * textureDepth, 0.0002F);

	// Calculate the distance from the mean (standard deviation) and use it to 
	// compute the maximum P value (maximum probability the pixel is lit).
	float d = curDepth - textureDepth;
	float pMax = variance / (variance + d * d);

	// Clamp the probability such that any values below MIN_P_MAX go to 0.0F 
	// and any values greater than MAX_P_MAX go to 1.0F, using linear stepping.
	// This helps lower the light bleeding artifact of VSM.
	const float MIN_P_MAX = 0.2F;
	const float MAX_P_MAX = 1.0F;
	pMax = linstep(0.2F, 1.0F, pMax);

	// Return the probability that the pixel is lit (which should be such that
	// pMax > p is bounded between [0.0F, 1.0F])
	return clamp(max(p, pMax), 0.0F, 1.0F);
}

#endif