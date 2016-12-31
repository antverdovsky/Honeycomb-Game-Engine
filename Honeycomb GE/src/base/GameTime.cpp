#include "..\..\include\base\GameTime.h"

#include <ctime>

namespace Honeycomb::Base {
	const float GameTime::SECOND = 1000.0F;
	GameTime* GameTime::gameTime = nullptr;

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
		if (gameTime == nullptr) gameTime = new GameTime();

		return gameTime;
	}

	void GameTime::setDeltaTimeMS(const float &ms) {
		this->deltaTime = ms;
	}

	GameTime::GameTime() {

	}

	GameTime::~GameTime() {

	}
}