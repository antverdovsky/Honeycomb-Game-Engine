#pragma once
#ifndef TEST_GAME_H
#define TEST_GAME_H

#include <memory>
#include "../../Honeycomb GE/include/HoneycombEngine.h"

#include "../../Honeycomb GE/include/base/BaseGame.h"

#include "../../Honeycomb GE/include/object/GameObject.h"
#include "../../Honeycomb GE/include/scene/GameScene.h"

namespace HoneycombTest {
	class TestGame : public Honeycomb::Base::BaseGame {
	public:
		void input();

		void render();

		void start();

		void stop();

		void update();
	private:
		Honeycomb::Scene::GameScene gameScene;	 // The main scene

		Honeycomb::Object::GameObject *carPtr;

		std::unique_ptr<Honeycomb::Object::GameObject> plane;		// The plane Game Object
		std::unique_ptr<Honeycomb::Object::GameObject> cube;		// The cube Game Object
		std::unique_ptr<Honeycomb::Object::GameObject> car;			// The car Game Object

		std::unique_ptr<Honeycomb::Object::GameObject> camera;		// The scene Camera
		std::unique_ptr<Honeycomb::Object::GameObject> ambient;		// The ambient lighting
		std::unique_ptr<Honeycomb::Object::GameObject> directional; // The directional lighting
	};
}

#endif