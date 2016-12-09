#include "..\..\include\scene\GameScene.h"

using Honeycomb::Object::GameObject;

namespace Honeycomb::Scene {
	GameScene* GameScene::activeScene = nullptr;

	GameScene::GameScene() : GameScene("GameScene") {

	}

	GameScene::GameScene(const std::string &nam) : GameObject(nam) {

	}

	GameScene* GameScene::clone() const {
		GameScene *clone = new GameScene();

		clone->name = this->name;
		clone->isActive = this->isActive;

		// Copy over all of the children and the components, once duplicated
		for (int i = 0; i < this->children.size(); i++)
			clone->addChild(*this->children.at(i)->clone());
		for (int i = 0; i < this->components.size(); i++)
			clone->addComponent(*this->components.at(i)->clone());

		return clone;
	}

	GameScene* GameScene::getActiveScene() {
		return GameScene::activeScene;
	}

	void GameScene::setActiveScene(GameScene &scene) {
		GameScene::activeScene = &scene;
	}
}