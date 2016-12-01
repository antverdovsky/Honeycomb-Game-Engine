#include "..\..\include\math\MathUtils.h"

namespace Honeycomb::Math::Utils {
	float degToRad(const float &deg) {
		return deg * PI / 180.0F;
	}

	float radToDeg(const float &rad) {
		return rad / PI * 180.0F;
	}
}