#pragma once
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

namespace Honeycomb::Math::Utils {
	const double PI = 3.14159265358979323846;

	/// Converts the specified angle in degrees to radians.
	/// float deg : The input angle (in degrees).
	/// return : The output angle (in radians).
	float degToRad(float deg);

	/// Converts the specified angle in radians to degrees.
	/// float rad : The input angle (in radians).
	/// return : The output angle (in degrees).
	float radToDeg(float rad);
}

#endif