#pragma once
#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "..\..\Honeycomb GE\include\base\BaseGame.h"

#include "..\..\Honeycomb GE\include\object\GameObject.h"

namespace HoneycombTest {
	class TestGame : public Honeycomb::Base::BaseGame {
	public:
		void input();

		void render();

		void start();

		void stop();

		void update();
	private:
		static std::string CUBE_MODEL_LOC;
		static std::string CUBE_TEXTURE_LOC;

		Honeycomb::Object::GameObject *cubeObject;
		Honeycomb::Object::GameObject *cameraObject;
	};
}

#endif