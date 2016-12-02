#pragma once
#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "..\..\Honeycomb GE\include\base\BaseGame.h"

#include "..\..\Honeycomb GE\include\object\GameObject.h"
#include "..\..\Honeycomb GE\include\scene\GameScene.h"

namespace HoneycombTest {
	class TestGame : public Honeycomb::Base::BaseGame {
	public:
		void input();

		void render();

		void start();

		void stop();

		void update();
	private:
		Honeycomb::Scene::GameScene gameScene; // The main scene for this game
	};
}

#endif