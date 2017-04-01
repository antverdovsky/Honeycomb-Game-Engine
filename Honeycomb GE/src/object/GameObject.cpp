#include "../../include/object/GameObject.h"

#include <algorithm>
#include <iostream>

#include "../../include/shader/ShaderProgram.h"
#include "../../include/component/physics/Transform.h"

using Honeycomb::Component::GameComponent;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Debug::Logger;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Scene::GameScene;

namespace Honeycomb::Object {
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
		while (this->children.size() != 0)
			delete this->children.at(0);
		while (this->components.size() != 0)
			delete this->components.at(0);

		// Notify parent that I am no longer a child
		this->deparent();
	}

	GameObject* GameObject::clone() const {
		GameObject *clone = new GameObject();

		clone->name = this->name;
		clone->isActive = this->isActive;

		// Copy over all of the children and the components, once duplicated
		// (Components must be copied over first since the Transform hierarchy
		// only gets copied for the child if the Transform component exists).
		for (const GameComponent *comp : this->components)
			clone->addComponent(*comp->clone());
		for (const GameObject *child : this->children)
			clone->addChild(*child->clone());
		
		return clone;
	}

	void GameObject::addChild(GameObject &o) {
		if (this->hasChild(o)) return;

		this->children.push_back(&o);

		if (o.parent != nullptr) o.parent->removeChild(&o);
		o.parent = this;

		// Parent the Transform of the child to this Transform
		Transform *childTransf = o.getComponent<Transform>();
		if (childTransf != nullptr)
			childTransf->setParent(this->getComponent<Transform>());
	}

	void GameObject::addComponent(GameComponent &c) {
		if (this->hasComponent(c)) return;

		this->components.push_back(&c);

		if (c.getAttached() != nullptr) c.getAttached()->removeComponent(&c);
		c.attached = this;
	}

	void GameObject::deparent() {
		// Remove this object from its parents' children and set the parent of
		// this object to nothing.
		if (this->parent != nullptr) {
			this->parent->removeChild(this);
			this->parent = nullptr;
		}

		// Unparent the Transform of this
		Transform *thisTransf = this->getComponent<Transform>();
		if (thisTransf != nullptr)
			thisTransf->setParent(nullptr);
	}

	GameObject* GameObject::getChild(const std::string &name) {
		return const_cast<GameObject*>(static_cast<const GameObject*>
			(this)->getChild(name));
	}

	const GameObject* GameObject::getChild(const std::string &name) const {
		// Go through all components and try to find one whose name matches
		for (const GameObject* child : this->children)
			if (child->getName() == name)
				return child;
		
		Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
			"Object " + this->name + " does not contain child " + name);

		// If unable to find a matching child -> Return NULL
		return nullptr;
	}

	std::vector<GameObject*>& GameObject::getChildren() {
		return this->children;
	}

	const std::vector<GameObject*>& GameObject::getChildren() const {
		return this->children;
	}

	GameComponent* GameObject::getComponent(const std::string &name) {
		return const_cast<GameComponent*>(static_cast<const GameObject*>
			(this)->getComponent(name));
	}

	const GameComponent* GameObject::getComponent(const std::string &name)
			const {
		// Go through all components and try to find one whose name matches
		for (const GameComponent* comp : this->components)
			if (comp->getName() == name)
				return comp;

		Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
			"Object " + this->name + " does not contain component " + name);

		// If unable to find a matching component -> Return NULL
		return NULL;
	}

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

	bool GameObject::hasChild(const GameObject &child) const {
		return std::find(this->children.begin(), this->children.end(), &child)
			!= this->children.end();
	}

	bool GameObject::hasComponent(const GameComponent &comp) const {
		return std::find(this->components.begin(), this->components.end(),
			&comp) != this->components.end();
	}

	void GameObject::input() {
		if (!this->isActive) return; // If not active -> It should not update!

		// Handle input for all children and components
		for (GameObject *child : this->children)
			child->input();
		for (GameComponent *comp : this->components)
			comp->input();
	}

	void GameObject::removeChild(GameObject *o) {
		children.erase( // Erase object from my children
			std::remove(children.begin(), children.end(), o), children.end());

		o->parent = nullptr;

		// Notify child's transform it no longer has a parent
		Transform *childTransf = o->getComponent<Transform>();
		if (childTransf) childTransf->setParent(nullptr);
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
		for (GameObject *child : this->children)
			child->render(shader);
		for (GameComponent *comp : this->components)
			comp->render(shader);
	}

	void GameObject::setScene(GameScene *scene) {
		this->scene = scene;

		for (GameObject *child : this->children)
			child->setScene(scene);
	}

	void GameObject::start() {
		if (this->isActive) return;
		this->isActive = true;

		// Handle starting for all children and components
		for (GameObject *child : this->children)
			child->start();
		for (GameComponent *comp : this->components)
			comp->start();
	}

	void GameObject::stop() {
		if (!this->isActive) return;
		this->isActive = false;

		// Handle starting for all children and components
		for (GameObject *child : this->children)
			child->stop();
		for (GameComponent *comp : this->components)
			comp->stop();
	}

	void GameObject::update() {
		if (!this->isActive) return;

		// Handle updating for all children and components
		for (GameObject *child : this->children)
			child->update();
		for (GameComponent *comp : this->components)
			comp->update();
	}
}