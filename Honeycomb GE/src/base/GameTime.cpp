#include "..\..\include\base\GameTime.h"

#include <ctime>

namespace Honeycomb::Base::Time {
	float deltaTime;

	float getDeltaTime() {
		return deltaTime;
	}

	float getDeltaTimeSeconds() {
		return getDeltaTime() / SECOND;
	}

	float getGameTime() {
		// Get the clock ticks, convert to seconds, then to ms and return
		return (float)clock() / CLOCKS_PER_SEC * 1000.0F;
	}

	float getGameTimeSeconds() {
		return getGameTime() / SECOND;
	}

	void setDeltaTime(float dT) {
		deltaTime = dT;
	}
}