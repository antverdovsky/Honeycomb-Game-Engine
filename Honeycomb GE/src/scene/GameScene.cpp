#include "../../include/scene/GameScene.h"

using Honeycomb::Component::GameComponent;
using Honeycomb::Object::GameObject;
using Honeycomb::Component::Light::BaseLight;

namespace Honeycomb { namespace Scene {
	GameScene* GameScene::activeScene = nullptr;

	GameScene::GameScene() : GameScene("GameScene") {

	}

	GameScene::GameScene(const std::string &nam) : GameObject(nam) {

	}

	void GameScene::addChild(std::unique_ptr<GameObject> obj) {
		obj->setScene(this);

		GameObject::addChild(std::move(obj));
	}

	GameScene* GameScene::clone() const {
		GameScene *clone = new GameScene();

		clone->name = this->name;
		clone->isActive = this->isActive;

		// Copy over all of the children and the components, once duplicated
		for (auto &child : this->children)
			clone->addChild(child->clone());
		for (const GameComponent *comp : this->components)
			clone->addComponent(*comp->clone());

		return clone;
	}

	GameScene* GameScene::getActiveScene() {
		return GameScene::activeScene;
	}

	std::vector<BaseLight*>& GameScene::getActiveLights() {
		return this->activeLights;
	}

	const std::vector<BaseLight*>& GameScene::getActiveLights() const {
		return this->activeLights;
	}

	void GameScene::setActiveScene(GameScene &scene) {
		GameScene::activeScene = &scene;
	}
} }
