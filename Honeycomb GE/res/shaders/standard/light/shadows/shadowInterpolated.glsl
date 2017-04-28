#ifndef SHADOW_INTERPOLATED_GLSL
#define SHADOW_INTERPOLATED_GLSL

/// Samples the specified shadow map at the specified coordinates with bilinear
/// interpolation.
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec2 coords : The coordnates at which to sample the shadow map.
/// float bias : The shadow bias value.
/// float curDepth : The current depth from the projection coordinates.
/// return : 1.0F if the fragment is in shadow, 0.0F otherwise.
float sampleShadowInterpolated(sampler2D map, vec2 coords, float bias, 
		float curDepth);

float sampleShadowInterpolated(sampler2D map, vec2 coords, float bias, 
		float curDepth) {
	// Get the texel size (inverse of the pixel size of the shadow map)
	vec2 pixelSize = textureSize(map, 0);

	// Compute the texel size, and center UV coordinates.
	vec2 texel = 1.0F / pixelSize;
	vec2 center = floor(coords * pixelSize + 0.5F) / pixelSize;

	// Compute the fraction part of the texture coordinates
	vec2 fraction = fract(coords * pixelSize + 0.5F);

	// Sample the Bottom Left, Bottom Right, Top Left and Top Right texels,
	// relative to the center fragment.
	float cmp = curDepth - bias;
	float bL = step(cmp, texture2D(map, center + texel * vec2(0.0F, 0.0F)).r);
	float bR = step(cmp, texture2D(map, center + texel * vec2(1.0F, 0.0F)).r);
	float tL = step(cmp, texture2D(map, center + texel * vec2(0.0F, 1.0F)).r);
	float tR = step(cmp, texture2D(map, center + texel * vec2(1.0F, 1.0F)).r);
	
	// Bilinear Interpolation of all of the sampled texels.
	float mixA = mix(bL, tL, fraction.y);
	float mixB = mix(bR, tR, fraction.y);
	float mixC = mix(mixA, mixB, fraction.x);

	return mixC;
}

#endif