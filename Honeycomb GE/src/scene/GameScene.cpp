#include "../../include/scene/GameScene.h"

using Honeycomb::Component::GameComponent;
using Honeycomb::Object::GameObject;
using Honeycomb::Component::Light::BaseLight;

namespace Honeycomb { namespace Scene {
	GameScene* GameScene::activeScene = nullptr;

	GameScene* GameScene::getActiveScene() {
		return GameScene::activeScene;
	}

	GameScene::GameScene() : GameScene("GameScene") {

	}

	GameScene::GameScene(const std::string &name) : GameObject(name) {
		this->scene = this;
		this->isSelfActive = false;
	}

	GameObject& GameScene::addChild(std::unique_ptr<GameObject> object) {
		// Add the object as a child of this, using the GameObject class
		auto &child = GameObject::addChild(std::move(object));

		// Fetch all of the lights of the object and its children and add them
		// to the scene's lights list.
		auto lights = child.getComponentsInheritedInDescendants<BaseLight>();
		this->sceneLights.insert(this->sceneLights.end(), 
				lights.begin(), lights.end());

		return child;
	}

	std::unique_ptr<GameScene> GameScene::clone() const {
		auto clone = std::make_unique<GameScene>(this->name);

		// Copy over all of the children and the components, once duplicated
		for (auto &child : this->children) {
			clone->addChild(child->clone());
		}
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				clone->addComponent(component->clone());
			}
		}

		return clone;
	}

	bool GameScene::getIsActive() const {
		return GameScene::activeScene == this &&
			this->isSelfActive;
	}

	const std::vector<std::reference_wrapper<
			Honeycomb::Component::Light::BaseLight>>& 
			GameScene::getSceneLights() const {
		return this->sceneLights;
	}

	void GameScene::onDisable() {
		if (GameScene::activeScene == this)
			GameScene::activeScene = nullptr;
	}

	void GameScene::onEnable() {
		// If any other scene is already enabled, disable it
		if (GameScene::activeScene != nullptr) 
			GameScene::activeScene->doDisable();

		GameScene::activeScene = this;
	}

	std::unique_ptr<GameObject> GameScene::removeChild(GameObject *object) {
		// Remove the child from this using the GameObject class
		auto child = GameObject::removeChild(object);

		// Fetch all of the lights of the object and its children and remove 
		// them from the scene's lights list.
		auto lights = child->getComponentsInheritedInDescendants<BaseLight>();
		this->sceneLights.erase(
			std::remove_if(this->sceneLights.begin(), this->sceneLights.end(),
				[&](const auto &sceneLight) {
					return std::find_if(lights.begin(), lights.end(), 
						[&](const auto &light) {
							return &light.get() == &sceneLight.get();
						}) != lights.end();
				}),
			this->sceneLights.end());

		return child;
	}
} }
