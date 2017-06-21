#include "../../include/component/GameComponent.h"

#include <sstream>

#include "../../include/object/GameObject.h"

using Honeycomb::Object::GameObject;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb { namespace Component {
	GameComponentDisallowsMultipleException::
			GameComponentDisallowsMultipleException(const GameObject *g) :
			std::runtime_error("Game Component Disallows Multiple Instances") {
		this->object = g;
	}

	const char* GameComponentDisallowsMultipleException::what() const throw() {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << " but it is being doubly added"
			<< " to the Game Object, " << this->object->getName();
		return oss.str().c_str();
	}

	GameComponent::GameComponent() {
		this->isSelfActive = false;
		this->attached = nullptr;
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

	bool GameComponent::isAttached() const {
		return this->attached != nullptr;
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

	GameComponentID GameComponent::getGameComponentIDCounter() noexcept {
		static GameComponentID type = 0U;
		return type++;
	}

	bool GameComponent::getProperty_AllowsMultiple() const noexcept {
		return true;
	}
} }
