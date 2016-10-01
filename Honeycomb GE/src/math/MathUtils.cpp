#include "..\..\include\math\MathUtils.h"

namespace Honeycomb::Math::Utils {
	float degToRad(float deg) {
		return deg * PI / 180.0F;
	}

	float radToDeg(float rad) {
		return rad / PI * 180.0F;
	}
}