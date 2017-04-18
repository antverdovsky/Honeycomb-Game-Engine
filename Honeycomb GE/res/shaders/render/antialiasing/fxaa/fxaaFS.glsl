#version 410 core

#include <../../../standard/structs/stdCamera.glsl>
#include <../../../standard/vertex/stdVertexFS.glsl>

uniform sampler2D gBufferFinal; // The final texture to be FXAA processed
uniform Camera camera; // The scene Camera

out vec4 color; // The FXAA post-processed output image

uniform float spanMax;   // | Maximum Blur Direction Span (in texels) |
uniform float reduceMin; // Minimum Reduction (for picking direction reduction)
uniform float reduceMul; // Reduction Multiple (multiplies average luminance)

void main() {
	// Vector for which the dot of this and a color vector results in the 
	// floating point perceived brightness of the color.
	const vec3 luminance = vec3(0.299F, 0.587F, 0.114F);

	// Offset on X and Y coordinate axes to move by one pixel
	vec2 pixelOffset = vec2(1.0F / camera.width, 1.0F / camera.height);

	// Positions for the Middle pixel (this) and the surrounding Bottom Left,
	// Bottom Right, Top Left and Top Right pixels.
	vec2 texM  = vertexIn.texCoords0;
	vec2 texBL = texM + (vec2(-1.0F, -1.0F) * pixelOffset);
	vec2 texBR = texM + (vec2( 1.0F, -1.0F) * pixelOffset);
	vec2 texTL = texM + (vec2(-1.0F,  1.0F) * pixelOffset);
	vec2 texTR = texM + (vec2( 1.0F,  1.0F) * pixelOffset);

	// Color values at the Middle pixel (this) and the surrounding Bottom Left,
	// Bottom Right, Top Left and Top Right pixels.
	vec3 colorM  = texture2D(gBufferFinal, texM).xyz;
	vec3 colorBL = texture2D(gBufferFinal, texBL).xyz;
	vec3 colorBR = texture2D(gBufferFinal, texBR).xyz;
	vec3 colorTL = texture2D(gBufferFinal, texTL).xyz;
	vec3 colorTR = texture2D(gBufferFinal, texTR).xyz;

	// Luminance for the Middle pixel (this) and the luminances for the
	// surrounding Bottom Left, Bottom Right, Top Left and Top Right pixels.
	// All luminances are calculated as the dot product of the above defined
	// luminance vector and the color at each pixel.
	float luminanceM  = dot(colorM, luminance);
	float luminanceBL = dot(colorBL, luminance);
	float luminanceBR = dot(colorBR, luminance);
	float luminanceTL = dot(colorTL, luminance);
	float luminanceTR = dot(colorTR, luminance);

	// Determine the Blur on the X and Y directions. For X, we calculate the
	// difference between the sums of the top and bottom luminances. A large
	// difference indicates we need a strong blur on the X direction. We repeat
	// this for the Y direction. Nonzero values will indicate an edge.
	vec2 blurDirection = vec2(
		(luminanceTL + luminanceTR) - (luminanceBL + luminanceBR),
		(luminanceTL + luminanceBL) - (luminanceTR + luminanceBR));

	// Calculate the average luminance of the surrounding pixels. Set the
	// reduce variable to either the product of the average and the multiple
	// reduction factor, or to the minimum reduction factor, depending on which
	// value is bigger.
	float avg = (luminanceTL + luminanceTR + luminanceBL + luminanceBR) / 4.0F;
	float reduce = max(reduceMul * avg, reduceMin);

	// Scale the blur direction vector so that the smallest component becomes
	// nearly equal to 1.0F and the largest component becomes equal to itself 
	// divided by the smallest component. Clamp values between -spanMax and 
	// +spanMax.
	float scale = 1.0F / 
		(reduce + min(abs(blurDirection.x), abs(blurDirection.y)));
	blurDirection = max(vec2(-spanMax, -spanMax), blurDirection * scale);
	blurDirection = min(vec2( spanMax,  spanMax), blurDirection);

	// Transform the blur direction into texel space
	blurDirection *= pixelOffset;

	// Compute how far we will actually go when blurring the image. For offset
	// A, we go a very small amount; for offset B we go a very large amount.
	vec2 blurOffsetA = vec2(1.0F / 6.0F);
	vec2 blurOffsetB = vec2(1.0F / 2.0F);

	// Compute the color for the small offset by sampling the textures at the
	// coordinates which are blurDirection * (+/-)blurOffsetA.
	vec3 colorA = (1.0F / 2.0F) * (
		texture2D(gBufferFinal, texM + (blurDirection * -blurOffsetA)).xyz +
		texture2D(gBufferFinal, texM + (blurDirection *  blurOffsetA)).xyz);

	// Compute the color for the large offset by sampling the textures at the
	// coordinate which are blurDirection * (+/-)blurOffsetB. Combine these
	// with a decreased value of colorA.
	vec3 colorB = (1.0F / 2.0F) * colorA + (1.0F / 4.0F) * (
		texture2D(gBufferFinal, texM + (blurDirection * -blurOffsetB)).xyz +
		texture2D(gBufferFinal, texM + (blurDirection *  blurOffsetB)).xyz);

	// Calculate the dot product of the color for the large offset and the
	// luminance.
	float luminanceB = dot(colorB, luminance);

	// Calculate the minimum and maximum luminance of all of the sampled
	// pixels.
	float minLuminance = min(luminanceM, min(
		min(luminanceBL, luminanceBR),
		min(luminanceTL, luminanceTR)));
	float maxLuminance = max(luminanceM, max(
		max(luminanceBL, luminanceBR),
		max(luminanceTL, luminanceTR)));

	// Calculate a 'bool' representing whether or not the luminance of color B
	// is outside of the range. If outOfRange is true, color A will remain
	// color A and color B will go to zero. If outOfRange is false, color A
	// will go to zero and color B will remain colorB. Return the maximum of
	// color A or color B as the FXAA color. (This code is written in this
	// confusing way to avoid branching).
	bool outOfRange = (luminanceB < minLuminance || luminanceB > maxLuminance);
	colorA = int(outOfRange) * colorA;
	colorB = (1 - int(outOfRange)) * colorB;
	color = vec4(max(colorA, colorB), 1.0F);
}