#include "..\..\include\base\GameTime.h"

#include <ctime>

namespace Honeycomb::Base {
	const float GameTime::SECOND = 1000.0F;
	GameTime* GameTime::gameTime = nullptr;

	float GameTime::getDeltaTimeMS() {
		return this->deltaTime;
	}

	float GameTime::getDeltaTimeS() {
		return (this->deltaTime / SECOND);
	}

	float GameTime::getElapsedTimeMS() {
		return ((float)clock() / CLOCKS_PER_SEC * 1000.0F);
	}

	float GameTime::getElapsedTimeS() {
		return ((float)clock() / CLOCKS_PER_SEC);
	}

	GameTime* GameTime::getGameTime() {
		if (gameTime == nullptr)
			gameTime = new GameTime();

		return gameTime;
	}

	void GameTime::setDeltaTimeMS(float ms) {
		this->deltaTime = ms;
	}

	GameTime::GameTime() {

	}
}