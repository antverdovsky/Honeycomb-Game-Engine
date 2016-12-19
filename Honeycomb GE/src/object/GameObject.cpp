#include "..\..\include\object\GameObject.h"

#include <algorithm>
#include <iostream>

#include "..\..\include\debug\Logger.h"
#include "..\..\include\shader\ShaderProgram.h"

using Honeycomb::Component::GameComponent;
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

		if (this->parent != nullptr) this->parent->addChild(*clone);

		// Copy over all of the children and the components, once duplicated
		for (int i = 0; i < this->children.size(); i++)
			clone->addChild(*this->children.at(i)->clone());
		for (int i = 0; i < this->components.size(); i++)
			clone->addComponent(*this->components.at(i)->clone());

		return clone;
	}

	void GameObject::addChild(GameObject &o) {
		this->children.push_back(&o);

		if (o.parent != nullptr) o.parent->removeChild(&o);
		o.parent = this;
	}

	void GameObject::addComponent(GameComponent &c) {
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
	}

	GameObject* GameObject::getChild(const std::string &name) {
		// Go through all components and try to find one whose name matches
		for (int i = 0; i < this->children.size(); i++) {
			if (this->children.at(i)->getName() == name) {
				return this->children.at(i);
			}
		}

		Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
			"Object " + this->name + " does not contain child " + name);

		// If unable to find a matching child -> Return NULL
		return nullptr;
	}

	const GameObject* GameObject::getChild(const std::string &name) const {
		// Go through all components and try to find one whose name matches
		for (int i = 0; i < this->children.size(); i++) {
			if (this->children.at(i)->getName() == name) {
				return this->children.at(i);
			}
		}

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
		// Go through all components and try to find one whose name matches
		for (int i = 0; i < this->components.size(); i++) {
			if (this->components.at(i)->getName() == name) {
				return this->components.at(i);
			}
		}

		Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
			"Object " + this->name + " does not contain component " + name);

		// If unable to find a matching component -> Return NULL
		return NULL;
	}

	const GameComponent* GameObject::getComponent(const std::string &name)
		const {
		// Go through all components and try to find one whose name matches
		for (int i = 0; i < this->components.size(); i++) {
			if (this->components.at(i)->getName() == name) {
				return this->components.at(i);
			}
		}

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

	void GameObject::input() {
		if (!this->isActive) return; // If not active -> It should not update!

		// Handle input for all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->input();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->input();
	}

	void GameObject::removeChild(GameObject *o) {
		children.erase( // Erase object from my children
			std::remove(children.begin(), children.end(), o), children.end());

		o->parent = nullptr;
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
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->render(shader);
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->render(shader);
	}

	void GameObject::start() {
		if (this->isActive) return;
		this->isActive = true;

		// Handle starting for all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->start();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->start();
	}

	void GameObject::stop() {
		if (!this->isActive) return;
		this->isActive = false;

		// Handle starting for all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->stop();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->stop();
	}

	void GameObject::update() {
		if (!this->isActive) return;

		// Handle updating for all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->update();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->update();
	}
}