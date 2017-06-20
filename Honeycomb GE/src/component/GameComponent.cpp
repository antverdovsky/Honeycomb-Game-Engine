#include "../../include/component/GameComponent.h"

#include "../../include/object/GameObject.h"

using Honeycomb::Object::GameObject;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb { namespace Component {
	GameComponent::GameComponent() {
		this->isSelfActive = false;
		this->attached = nullptr;

		this->componentID = getGameComponentTypeID<GameComponent>();
	}

	GameComponent::~GameComponent() {

	}

	std::unique_ptr<GameComponent> GameComponent::clone() const {
		return std::unique_ptr<GameComponent>(this->cloneInternal());
	}

	void GameComponent::doDisable() {
		this->isSelfActive = false;
		this->onDisable();
	}

	void GameComponent::doEnable() {
		this->isSelfActive = true;
		this->onEnable();
	}

	GameObject* GameComponent::getAttached() {
		return this->attached;
	}

	const GameObject* GameComponent::getAttached() const {
		return this->attached;
	}

	bool GameComponent::getIsActive() const {
		if (!this->attached) return false;

		return this->getIsSelfActive() && this->attached->getIsActive();
	}

	const bool& GameComponent::getIsSelfActive() const {
		return this->isSelfActive;
	}

	void GameComponent::onAttach() {

	}

	void GameComponent::onDetach() {

	}

	void GameComponent::onDisable() {
	
	}

	void GameComponent::onEnable() {

	}

	void GameComponent::onInput() {
		
	}

	void GameComponent::onRender(ShaderProgram &shader) {

	}

	void GameComponent::onStart() {
		this->doEnable();
	}

	void GameComponent::onStop() {
		this->doDisable();
	}

	void GameComponent::onUpdate() {

	}

	GameComponentID GameComponent::getGameComponentID() noexcept {
		static GameComponentID type = 0U;
		return type++;
	}

	GameComponent* GameComponent::cloneInternal() const {
		return new GameComponent();
	}
} }
