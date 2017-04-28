#ifndef MATH_GLSL
#define MATH_GLSL

/// Linear Step Function which returns a value between 0 and 1 which represents
/// the value's distance between the low and high values. If the value is lower
/// than low or higher than high, 0.0F or 1.0F will be returned, respectively.
/// float low : The low value.
/// float high : The high value.
/// float value : The value for which the linear space function is to be 
///				  computed.
float linstep(float low, float high, float value);

float linstep(float low, float high, float value) {
	// Calculate the linearized distance of the value between [low, high] 
	float d = (value - low) / (high - low);

	// If the value is outside of the [low, high] range, clamp it
	return clamp(d, 0.0F, 1.0F);
}

#endif