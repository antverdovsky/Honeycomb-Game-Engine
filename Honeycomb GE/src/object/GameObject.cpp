#include "../../include/object/GameObject.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "../../include/scene/GameScene.h"
#include "../../include/shader/ShaderProgram.h"
#include "../../include/component/physics/Transform.h"

using Honeycomb::Component::GameComponent;
using Honeycomb::Component::GameComponentDisallowsMultipleException;
using Honeycomb::Component::GameComponentPermanentException;
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

	GameObject::GameObject(const std::string &name) : GameObject(name, true) {
		
	}

	GameObject::~GameObject() {

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
		
		// Trigger the onAttach event function with this as the new parent of
		// the child.
		childRef.onAttach(this);
		
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
			throw GameComponentDisallowsMultipleException(
				this, component.get());
		}

		// Get the components of the same type as the Game Component passed in
		// and move the Game Component into the list. Get a reference to the
		// back of the list since that is where the Component was moved to.
		auto& componentsOfType = this->getComponentsInternal(
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

	std::unique_ptr<GameObject> GameObject::clone() const {
		// Create a new Game Object with the same name, but without a Transform
		// component since we will copy the Transform of this.
		std::unique_ptr<GameObject> clone =
			std::unique_ptr<GameObject>(new GameObject(this->name, false));

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

	void GameObject::doDisable() {
		this->isSelfActive = false;
		this->onDisable();
	}

	void GameObject::doEnable() {
		this->isSelfActive = true;
		this->onEnable();
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

	std::vector<std::reference_wrapper<GameObject>> GameObject::getChildren() {
		std::vector<std::reference_wrapper<GameObject>> refChildren;

		for (auto &childPtr : this->children)
			refChildren.push_back(std::ref(*childPtr.get()));

		return refChildren;
	}

	std::vector<std::reference_wrapper<const GameObject>> 
			GameObject::getChildren() const {
		std::vector<std::reference_wrapper<const GameObject>> refChildren;

		for (auto &childPtr : this->children)
			refChildren.push_back(std::cref(*childPtr.get()));

		return refChildren;
	}

	std::vector<std::reference_wrapper<GameObject>> GameObject::getChildren(
			const std::string &name) {
		std::vector<std::reference_wrapper<GameObject>> refChildren;

		for (auto &childPtr : this->children) {
			if (childPtr->getName() == name) {
				refChildren.push_back(std::ref(*childPtr.get()));
			}
		}

		return refChildren;
	}

	std::vector<std::reference_wrapper<const GameObject>> 
			GameObject::getChildren(const std::string &name) const {
		std::vector<std::reference_wrapper<const GameObject>> refChildren;

		for (auto &childPtr : this->children) {
			if (childPtr->getName() == name) {
				refChildren.push_back(std::cref(*childPtr.get()));
			}
		}

		return refChildren;
	}

	bool GameObject::getIsActive() const {
		if (!this->hasParent()) return false;

		return this->isSelfActive && this->parent->getIsActive();
	}

	const bool& GameObject::getIsSelfActive() const {
		return this->isSelfActive;
	}

	const std::string& GameObject::getName() const {
		return this->name;
	}

	const unsigned int& GameObject::getNumberOfComponents() const {
		return this->numComponents;
	}

	unsigned int GameObject::getNumberOfComponents(const unsigned int &id) 
			const {
		return this->getComponentsInternal(id).size();
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

	void GameObject::onDisable() {
		
	}

	void GameObject::onEnable() {

	}

	void GameObject::onInput() {
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				if (component->getIsActive()) component->onInput();
			}
		}

		for (auto &child : this->children) {
			if (child->getIsActive()) child->onInput();
		}
	}

	void GameObject::onRender(ShaderProgram &shader) {
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				if (component->getIsActive()) component->onRender(shader);
			}
		}

		for (auto &child : this->children) {
			if (child->getIsActive()) child->onRender(shader);
		}
	}

	void GameObject::onStart() {
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				component->onStart();
			}
		}

		for (auto &child : this->children) {
			child->onStart();
		}

		this->doEnable();
	}

	void GameObject::onStop() {
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				component->onStop();
			}
		}

		for (auto &child : this->children) {
			child->onStop();
		}

		this->doDisable();
	}

	void GameObject::onUpdate() {
		for (auto &componentsOfType : this->components) {
			for (auto &component : componentsOfType) {
				if (component->getIsActive()) component->onUpdate();
			}
		}

		for (auto &child : this->children) {
			if (child->getIsActive()) child->onUpdate();
		}
	}

	std::unique_ptr<GameObject> GameObject::removeChild(GameObject *object) {
		// Try to find the Game Object by comparing the pointers for equality.
		// If failed, throw the exception.
		auto child = std::find_if(this->children.begin(), this->children.end(),
			[&](const std::unique_ptr<GameObject>& child) {
				return object == child.get();
		});
		if (child == this->children.end())
			throw GameEntityNotAttachedException(this, object->getName());

		// Move the unique pointer out of the vector, so that this Game Object
		// no longer owns it.
		std::unique_ptr<GameObject> childPtr = std::move(*child);
		childPtr->parent = nullptr;
		childPtr->scene = nullptr;

		// Trigger the onDetach event for the child
		childPtr->onDetach(this);
		
		// Erase the child from my children vector, and move the pointer out
		// of this instance.
		this->children.erase(child);
		return std::move(childPtr);
	}

	std::unique_ptr<GameComponent> GameObject::removeComponent(
			GameComponent *component) {
		// Assert Game Component is not permanent. If it is, throw.
		if (component->getProperty_Permanent())
			throw GameComponentPermanentException(this, component);

		// Get the list of components which have the same type as the component
		// paramter specified.
		auto& componentsOfType = this->getComponentsInternal(
			component->getGameComponentID());
		
		// Try to find the Game Component by comparing the pointers for 
		// equality. If failed, throw the exception.
		auto comp = std::find_if(
			componentsOfType.begin(),
			componentsOfType.end(),
			[&](const std::unique_ptr<GameComponent>& comp) {
				return component == comp.get();
		});
		if (comp == componentsOfType.end()) {
			throw GameEntityNotAttachedException(
				this, typeid(component).name());
		}

		// Move the unique pointer out of the vector, so that this Game Object
		// no longer owns it.
		std::unique_ptr<GameComponent> compPtr = std::move(*comp);
		
		// Notify the Game Component that it has lost a parent
		compPtr->onDetach();
		compPtr->attached = nullptr;
		
		// Erase the component from my components vector, and move the pointer
		// out of this instance.
		--this->numComponents;
		componentsOfType.erase(comp);
		return std::move(compPtr);
	}

	void GameObject::setName(const std::string &name) {
		this->name = name;
	}

	GameObject::GameObject(const std::string &name, 
			const bool &attachTransform) {
		this->name = name;
		this->isSelfActive = false;
		this->parent = nullptr;
		this->scene = nullptr;

		this->components.resize(32);
		this->numComponents = 0;

		if (attachTransform) this->addComponent<Transform>();
	}

	std::vector<std::unique_ptr<GameComponent>>& 
			GameObject::getComponentsInternal(const unsigned int &id) {
		this->resizeComponents();
		return this->components.at(id);
	}

	const std::vector<std::unique_ptr<GameComponent>>&
			GameObject::getComponentsInternal(const unsigned int &id) const {
		this->resizeComponents();
		return this->components.at(id);
	}

	void GameObject::onAttach(GameObject *object) {
		// Set the object as the parent in the GameObject class and the 
		// Transform component.
		this->parent = object;
		this->getComponent<Transform>().setParent(
			&object->getComponent<Transform>());

		// Attach this object to the same scene as the new parent
		this->onAttach(object->scene);
	}

	void GameObject::onAttach(GameScene *scene) {
		this->scene = scene;

		for (auto &child : this->children) {
			child->onAttach(scene);
		}
	}

	void GameObject::onDetach(GameObject *object) {
		this->parent = nullptr;
		this->getComponent<Transform>().setParent(nullptr);

		this->onDetach(this->scene);
	}

	void GameObject::onDetach(GameScene *scene) {
		this->scene = nullptr;

		for (auto &child : this->children) {
			child->onDetach(scene);
		}
	}

	void GameObject::resizeComponents() const {
		auto componentCount = GameComponent::getGameComponentIDCounter(false);

		if (componentCount >= this->components.size())
			this->components.resize(2 * componentCount);
	}
} }
