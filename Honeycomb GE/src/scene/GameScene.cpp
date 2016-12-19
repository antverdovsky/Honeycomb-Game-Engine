#include "..\..\include\scene\GameScene.h"

using Honeycomb::Object::GameObject;
using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Light::PointLight;
using Honeycomb::Component::Light::SpotLight;

namespace Honeycomb::Scene {
	GameScene* GameScene::activeScene = nullptr;

	GameScene::GameScene() : GameScene("GameScene") {

	}

	GameScene::GameScene(const std::string &nam) : GameObject(nam) {

	}

	void GameScene::addChild(GameObject &obj) {
		obj.scene = this;

		GameObject::addChild(obj);
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

	std::vector<AmbientLight*>& GameScene::getAmbientLights() {
		return this->ambientLights;
	}

	const std::vector<AmbientLight*>& GameScene::getAmbientLights() const {
		return this->ambientLights;
	}

	std::vector<DirectionalLight*>& GameScene::getDirectionalLights() {
		return this->directionalLights;
	}

	const std::vector<DirectionalLight*>& GameScene::getDirectionalLights() 
			const {
		return this->directionalLights;
	}

	std::vector<PointLight*>& GameScene::getPointLights() {
		return this->pointLights;
	}

	const std::vector<PointLight*>& GameScene::getPointLights() const {
		return this->pointLights;
	}

	std::vector<SpotLight*>& GameScene::getSpotLights() {
		return this->spotLights;
	}

	const std::vector<SpotLight*>& GameScene::getSpotLights() const {
		return this->spotLights;
	}

	void GameScene::setActiveScene(GameScene &scene) {
		GameScene::activeScene = &scene;
	}
}