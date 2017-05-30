#include "../../include/base/GameTime.h"

#include <ctime>

namespace Honeycomb { namespace Base {
	const float GameTime::SECOND = 1000.0F;

	const float& GameTime::getDeltaTimeMS() const {
		return this->deltaTime;
	}

	float GameTime::getDeltaTimeS() const {
		return (this->deltaTime / SECOND);
	}

	float GameTime::getElapsedTimeMS() const {
		return ((float)clock() / CLOCKS_PER_SEC * 1000.0F);
	}

	float GameTime::getElapsedTimeS() const {
		return ((float)clock() / CLOCKS_PER_SEC);
	}

	GameTime* GameTime::getGameTime() {
		static GameTime *gameTime = new GameTime();
		return gameTime;
	}

	void GameTime::setDeltaTimeMS(const float &ms) {
		this->deltaTime = ms;
	}
} }
