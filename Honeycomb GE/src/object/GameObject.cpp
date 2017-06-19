#include "../../include/object/GameObject.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "../../include/shader/ShaderProgram.h"
#include "../../include/component/physics/Transform.h"

using Honeycomb::Component::GameComponent;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Debug::Logger;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Scene::GameScene;

namespace Honeycomb { namespace Object {
	GameObject::GameObject() : GameObject("GameObject") {

	}

	GameObject::GameObject(const std::string &n) {
		this->name = n;
		this->isActive = false;
		this->parent = nullptr;
		this->scene = nullptr;
	}

	GameObject::~GameObject() {
		// Delete all of the children and components
//		while (this->children.size() != 0)
//			delete this->children.at(0);s
//		while (this->components.size() != 0)
//			delete this->components.at(0);

		// Notify parent that I am no longer a child
//		this->deparent();
	}

	std::unique_ptr<GameObject> GameObject::clone() const {
		std::unique_ptr<GameObject> clone = 
				std::make_unique<GameObject>(this->name);

		// Copy over all of the children and the components, once duplicated
		// (Components must be copied over first since the Transform hierarchy
		// only gets copied for the child if the Transform component exists).
		for (const GameComponent *comp : this->components)
			clone->addComponent(*comp->clone());
		for (auto &child : this->children)
			clone->addChild(child->clone());
		
		return clone;
	}

	GameObject& GameObject::addChild(std::unique_ptr<GameObject> o) {
//		if (this->hasChild(o)) return;

		// If the object already has a parent, lose the parent
		if (o->parent != nullptr) o->parent->removeChild(o.get());

		// Make this the new parent of the Object
		this->children.push_back(std::move(o));
		this->children.back()->parent = this;

		// Parent the Transform of the child to this Transform, if it has one
		try {
			Transform &childTransf = this->children.back()->
				getComponent<Transform>();
			childTransf.setParent(&this->getComponent<Transform>());
		} catch (GameEntityNotAttachedException e) {
		
		}

		return *this->children.back();
	}

	void GameObject::addComponent(GameComponent &c) {
		if (this->hasComponent(c)) return;

		this->components.push_back(&c);

		if (c.getAttached() != nullptr) c.getAttached()->removeComponent(&c);
		c.attached = this;
	}

	/*
	void GameObject::deparent() {
		if (this->parent != nullptr) {
			// Remove this object from its parents' children and set the parent
			// of this to null.
			auto it = std::remove_if(this->parent->children.begin(), 
				this->parent->children.end(),
				[&](const std::unique_ptr<GameObject>& child) {
				return child.get() == this;
			});
			this->parent->children.erase(it, this->parent->children.end());
			this->parent = nullptr;
		
			// Unparent the Transform of this
			Transform &thisTransf = this->getComponent<Transform>();
			thisTransf.setParent(nullptr);
		}
	}
	*/

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
/*
	GameComponent& GameObject::getComponent(const std::string &name) {
		return const_cast<GameComponent&>(static_cast<const GameObject*>
			(this)->getComponent(name));
	}

	const GameComponent& GameObject::getComponent(const std::string &name)
			const {
		// Go through all components and try to find one whose name matches
		for (const GameComponent* comp : this->components) {
			if (comp->getName() == name) {
				return *comp;
			}
		}

		throw GameEntityNotAttachedException(this, name);
	}
*/
	std::vector<GameComponent*>& GameObject::getComponents() {
		return this->components;
	}

	const std::vector<GameComponent*>& GameObject::getComponents() const {
		return this->components;
	}

	const bool& GameObject::getIsActive() const {
		return this->isActive;
	}

	const std::string& GameObject::getName() const {
		return this->name;
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
/*
	bool GameObject::hasChild(const GameObject &child) const {
		return std::find(this->children.begin(), this->children.end(), &child)
			!= this->children.end();
	}
*/
	bool GameObject::hasComponent(const GameComponent &comp) const {
		return std::find(this->components.begin(), this->components.end(),
			&comp) != this->components.end();
	}

	void GameObject::input() {
		if (!this->isActive) return; // If not active -> It should not update!

		// Handle input for all children and components
		for (auto &child : this->children)
			child->input();
		for (GameComponent *comp : this->components)
			comp->input();
	}

	std::unique_ptr<GameObject> GameObject::removeChild(GameObject *o) {
		auto child = std::find_if(this->children.begin(), this->children.end(),
			[&](const std::unique_ptr<GameObject>& child) {
			return o == child.get();
		});
		std::unique_ptr<GameObject> childPtr = std::move(*child);

		this->children.erase(child);

		o->parent = nullptr;

		// Notify child's transform it no longer has a parent
		Transform &childTransf = o->getComponent<Transform>();
		childTransf.setParent(nullptr);

		return std::move(childPtr);
	}

	void GameObject::removeComponent(GameComponent *c) {
		components.erase( // Erase component from my components
			std::remove(components.begin(), components.end(), c),
			components.end());

		c->attached = nullptr;
	}

	void GameObject::render(ShaderProgram &shader) {
		if (!this->isActive) return;

		// Handle rendering for all children and components
		for (auto &child : this->children)
			child->render(shader);
		for (GameComponent *comp : this->components)
			comp->render(shader);
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
		for (GameComponent *comp : this->components)
			comp->start();
	}

	void GameObject::stop() {
		if (!this->isActive) return;
		this->isActive = false;

		// Handle starting for all children and components
		for (auto &child : this->children)
			child->stop();
		for (GameComponent *comp : this->components)
			comp->stop();
	}

	void GameObject::update() {
		if (!this->isActive) return;

		// Handle updating for all children and components
		for (auto &child : this->children)
			child->update();
		for (GameComponent *comp : this->components)
			comp->update();
	}

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
} }
