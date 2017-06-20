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

	void GameComponent::onInput() {
		
	}

	void GameComponent::onRender(ShaderProgram &shader) {

	}

	void GameComponent::onStart() {

	}

	void GameComponent::onStop() {

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
