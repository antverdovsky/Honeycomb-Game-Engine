#include "..\..\include\base\GameTime.h"

#include <ctime>

namespace Honeycomb::Base::Time {
	float deltaTime;

	float getDeltaTime() {
		return deltaTime;
	}

	float getGameTime() {
		// Get the clock ticks, convert to seconds, then to ms and return
		return (float)clock() / CLOCKS_PER_SEC * 1000.0F;
	}

	void setDeltaTime(float dT) {
		deltaTime = dT;
	}
}