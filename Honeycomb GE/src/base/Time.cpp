#include "..\..\include\base\Time.h"

#include <ctime>

float Time::deltaTime;

float Time::getDeltaTime() {
	return Time::deltaTime;
}

float Time::getGameTime() {
	// Get the clock ticks, convert to seconds, then to ms and return
	return (float)clock() / CLOCKS_PER_SEC * 1000.0F;
}

void Time::setDeltaTime(float dT) {
	Time::deltaTime = dT;
}