#include "../../include/component/GameComponent.h"

#include "../../include/object/GameObject.h"

using Honeycomb::Object::GameObject;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Component {
	GameComponent::GameComponent() : GameComponent("GameComponent") {

	}

	GameComponent::GameComponent(const std::string &name) {
		this->name = name;

		this->isActive = false;
		this->attached = nullptr;
	}

	GameComponent::~GameComponent() {
		// Notify object that I am no longer attached
		this->detach();
	}

	GameComponent* GameComponent::clone() const {
		return new GameComponent(this->name);
	}

	void GameComponent::detach() {
		if (this->attached != nullptr) this->attached->removeComponent(this);
		
		this->attached = nullptr;
	}

	GameObject* GameComponent::getAttached() {
		return this->attached;
	}

	const GameObject* GameComponent::getAttached() const {
		return this->attached;
	}

	bool& GameComponent::getIsActive() {
		return this->isActive;
	}

	const bool& GameComponent::getIsActive() const {
		return this->isActive;
	}

	const std::string& GameComponent::getName() const {
		return this->name;
	}

	void GameComponent::input() {

	}

	void GameComponent::render(ShaderProgram &shader) {
		
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