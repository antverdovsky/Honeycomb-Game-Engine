#pragma once
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

namespace Honeycomb { namespace Math { namespace Utils {
	const double PId = 3.14159265358979323846; // Mathematical PI
	const float PI = 3.14159265F;

	/// Clamps the specified value between the minimum and maximum values.
	/// const float &min : The minimum possible value.
	/// const float &max : The maximum possible value.
	/// const float &val : The value which is to be clamped.
	/// return : The clamped value.
	float clamp(const float &min, const float &max, const float &val);

	/// Converts the specified angle in degrees to radians.
	/// const float &deg : The input angle (in degrees).
	/// return : The output angle (in radians).
	float degToRad(const float &deg);

	/// Converts the specified angle in radians to degrees.
	/// const float &rad : The input angle (in radians).
	/// return : The output angle (in degrees).
	float radToDeg(const float &rad);
} } }

#endif
