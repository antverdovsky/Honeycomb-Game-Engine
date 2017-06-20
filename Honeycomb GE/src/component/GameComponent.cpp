#include "../../include/component/GameComponent.h"

#include "../../include/object/GameObject.h"

using Honeycomb::Object::GameObject;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb { namespace Component {
	GameComponent::GameComponent() {
		this->isActive = false;
		this->attached = nullptr;
	}

	GameComponent::~GameComponent() {
		// Notify object that I am no longer attached
//		this->detach();
	}

	std::unique_ptr<GameComponent> GameComponent::clone() const {
		return std::unique_ptr<GameComponent>(this->cloneInternal());
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

	GameComponentID GameComponent::getGameComponentID() noexcept {
		static GameComponentID type = 0U;
		return type++;
	}

	GameComponent* GameComponent::cloneInternal() const {
		return new GameComponent();
	}
} }
