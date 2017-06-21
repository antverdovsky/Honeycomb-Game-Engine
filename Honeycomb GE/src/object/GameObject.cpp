#include "../../include/object/GameObject.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "../../include/scene/GameScene.h"
#include "../../include/shader/ShaderProgram.h"
#include "../../include/component/physics/Transform.h"

using Honeycomb::Component::GameComponent;
using Honeycomb::Component::GameComponentDisallowsMultipleException;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Debug::Logger;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Scene::GameScene;

namespace Honeycomb { namespace Object {
	GameEntityNotAttachedException::GameEntityNotAttachedException(
			const GameObject *g, const std::string &name) :
		std::runtime_error("Unable to fetch Game Entity") {
		this->gameObject = g;
		this->entityName = name;
	}

	const char* GameEntityNotAttachedException::what() const throw() {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << " of name " <<
			this->entityName << " from object " << this->gameObject->getName();
		return oss.str().c_str();
	}

	GameObject::GameObject() : GameObject("GameObject") {

	}

	GameObject::GameObject(const std::string &n) {
		this->name = n;
		this->isActive = false;
		this->parent = nullptr;
		this->scene = nullptr;

		// todo, while 256 should be 10x more components than needed, this will
		// still cause issues if there are more than 256...
		this->components.resize(256);
		this->numComponents = 0;
	}

	GameObject::~GameObject() {

	}

	std::unique_ptr<GameObject> GameObject::clone() const {
		// Create a new Game Object with the same name
		std::unique_ptr<GameObject> clone = 
				std::make_unique<GameObject>(this->name);

		// Copy over all of the children and the components, once duplicated
		// (Components must be copied over first since the Transform hierarchy
		// only gets copied for the child if the Transform component exists).
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				clone->addComponent(component->clone());
			}
		}
		for (auto &child : this->children) {
			clone->addChild(child->clone());
		}
		
		return clone;
	}

	GameObject& GameObject::addChild(std::unique_ptr<GameObject> object) {
		// These should never happen because how would an external class steal
		// the unique pointer from a GameObject instance?
		if (this->hasChild(object.get())) return *object;
		if (object->hasParent()) object->parent->removeChild(object.get());

		// Since the unique pointer to the object gets moved to the back of the
		// vector, create a reference to the new unique pointer so that we may
		// continue to modify it.
		this->children.push_back(std::move(object));
		GameObject &childRef = *this->children.back();
		
		// Parent the Transform of the child to this Transform, if it has one
		childRef.parent = this;
		try {
			Transform &childTransf = childRef.getComponent<Transform>();
			childTransf.setParent(&this->getComponent<Transform>());
		} catch (GameEntityNotAttachedException e) {
		
		}

		return childRef;
	}

	GameComponent& GameObject::addComponent(std::unique_ptr<GameComponent> 
			component) {
		// These should never happen as well (refer to addChild).
		if (this->hasComponent(component.get())) return *component;
		if (component->isAttached()) 
			component->attached->removeComponent(component.get());

		// Check if the component DisallowsMultiple and if there already exists
		// a component of the same type. If so, throw exception.
		if (!component->getProperty_AllowsMultiple() &&
				this->hasComponent(component->getGameComponentID())) {
			throw GameComponentDisallowsMultipleException(this);
		}

		// Get the components of the same type as the Game Component passed in
		// and move the Game Component into the list. Get a reference to the
		// back of the list since that is where the Component was moved to.
		auto& componentsOfType = this->getComponentsOfType(
			component->getGameComponentID());
		componentsOfType.push_back(std::move(component));
		GameComponent &componentRef = *componentsOfType.back();

		// Increment the number of components, and notify the component that it
		// has been attached to a new Game Object.
		++this->numComponents;
		componentRef.attached = this;
		componentRef.onAttach();
		return componentRef;
	}

	GameObject& GameObject::getChild(const std::string &name) {
		return const_cast<GameObject&>(static_cast<const GameObject*>
			(this)->getChild(name));
	}

	const GameObject& GameObject::getChild(const std::string &name) const {
		for (auto &child : this->children) {
			if (child->getName() == name) {
				return *child;
			}
		}

		throw GameEntityNotAttachedException(this, name);
	}

	const std::vector<std::unique_ptr<GameObject>>& GameObject::getChildren()
			const {
		return this->children;
	}

	const std::vector<std::vector<std::unique_ptr<GameComponent>>>& 
			GameObject::getComponents() const {
		return this->components;
	}

	const std::vector<std::unique_ptr<GameComponent>>& 
			GameObject::getComponentsOfType(const unsigned int &id) const {
		return this->components.at(id);
	}

	const bool& GameObject::getIsActive() const {
		return this->isActive;
	}

	const std::string& GameObject::getName() const {
		return this->name;
	}

	const unsigned int& GameObject::getNumberOfComponents() const {
		return this->numComponents;
	}

	unsigned int GameObject::getNumberOfComponents(const unsigned int &id) 
			const {
		return this->components.at(id).size();
	}

	GameObject* GameObject::getParent() {
		return this->parent;
	}

	const GameObject* GameObject::getParent() const {
		return this->parent;
	}

	GameScene* GameObject::getScene() {
		return this->scene;
	}

	const GameScene* GameObject::getScene() const {
		return this->scene;
	}

	bool GameObject::hasChild(const GameObject *child) const {
		return child->parent == this;
	}

	bool GameObject::hasComponent(const GameComponent *component) const {
		return component->attached == this;
	}

	bool GameObject::hasComponent(const unsigned int &id) const {
		return this->getNumberOfComponents(id) > 0;
	}

	bool GameObject::hasParent() const {
		return this->parent != nullptr;
	}

	bool GameObject::hasScene() const {
		return this->scene != nullptr;
	}

	void GameObject::input() {
		if (!this->isActive) return; // If not active -> It should not update!

		// Handle input for all children and components
		for (auto &child : this->children)
			child->input();
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				component->onInput();
			}
		}
	}

	std::unique_ptr<GameObject> GameObject::removeChild(GameObject *o) {
		auto child = std::find_if(this->children.begin(), this->children.end(),
			[&](const std::unique_ptr<GameObject>& child) {
			return o == child.get();
		});
		std::unique_ptr<GameObject> childPtr = std::move(*child);

		this->children.erase(child);

		childPtr->parent = nullptr;

		// Notify child's transform it no longer has a parent
		Transform &childTransf = o->getComponent<Transform>();
		childTransf.setParent(nullptr);

		return std::move(childPtr);
	}

	std::unique_ptr<GameComponent> GameObject::removeComponent(GameComponent *c) {
		std::vector<std::unique_ptr<GameComponent>>& componentsOfType =
			this->components.at(c->getGameComponentID());
		auto comp = std::find_if(componentsOfType.begin(),
			componentsOfType.end(),
			[&](const std::unique_ptr<GameComponent>& comp) {
			return c == comp.get();
		});
		std::unique_ptr<GameComponent> compPtr = std::move(*comp);
		componentsOfType.erase(comp);

		--this->numComponents;

		compPtr->attached = nullptr;
		compPtr->onDetach();

		return std::move(compPtr);
	}

	void GameObject::render(ShaderProgram &shader) {
		if (!this->isActive) return;

		// Handle rendering for all children and components
		for (auto &child : this->children)
			child->render(shader);
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				component->onRender(shader);
			}
		}
	}

	void GameObject::setScene(GameScene *scene) {
		this->scene = scene;

		for (auto &child : this->children)
			child->setScene(scene);
	}

	void GameObject::start() {
		if (this->isActive) return;
		this->isActive = true;

		// Handle starting for all children and components
		for (auto &child : this->children)
			child->start();
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				component->onStart();
			}
		}
	}

	void GameObject::stop() {
		if (!this->isActive) return;
		this->isActive = false;

		// Handle starting for all children and components
		for (auto &child : this->children)
			child->stop();
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				component->onInput();
			}
		}
	}

	void GameObject::update() {
		if (!this->isActive) return;

		// Handle updating for all children and components
		for (auto &child : this->children)
			child->update();
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				component->onUpdate();
			}
		}
	}

	std::vector<std::unique_ptr<GameComponent>>& 
			GameObject::getComponentsOfType(const unsigned int &id) {
		return this->components.at(id);
	}
} }
