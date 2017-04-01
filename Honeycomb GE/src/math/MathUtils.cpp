#include "../../include/math/MathUtils.h"

namespace Honeycomb { namespace Math { namespace Utils {
	float clamp(const float &min, const float &max, const float &val) {
		if (val < min) return min;
		else if (val > max) return max;
		else return val;
	}

	float degToRad(const float &deg) {
		return deg * PI / 180.0F;
	}

	float radToDeg(const float &rad) {
		return rad / PI * 180.0F;
	}
} } }
