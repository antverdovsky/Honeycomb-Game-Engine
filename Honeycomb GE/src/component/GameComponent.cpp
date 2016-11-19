#include "..\..\include\component\GameComponent.h"

#include "..\..\include\object\GameObject.h"

using Honeycomb::Object::GameObject;

namespace Honeycomb::Component {
	GameComponent::GameComponent() : GameComponent("GameComponent") {

	}

	GameComponent::GameComponent(std::string name) {
		this->name = name;
		this->isActive = false;
		this->attached = nullptr;
	}

	GameComponent::~GameComponent() {
		// Notify object that I am no longer attached
		this->detach();
	}

	GameComponent* GameComponent::clone() {
		return new GameComponent(*this);
	}

	void GameComponent::detach() {
		if (this->attached != nullptr) this->attached->removeComponent(this);
		this->setAttached(nullptr); // Set NULL as the new attached object
	}

	GameObject* GameComponent::getAttached() {
		return this->attached;
	}

	bool& GameComponent::getIsActive() {
		return this->isActive;
	}

	std::string GameComponent::getName() {
		return this->name;
	}

	void GameComponent::input() {

	}

	void GameComponent::render() {
		
	}

	void GameComponent::setAttached(GameObject *o) {
		this->attached = o;
	}

	void GameComponent::start() {
		this->isActive = true;
	}

	void GameComponent::stop() {
		this->isActive = false;
	}
	
	void GameComponent::update() {

	}
}