#include "..\..\include\object\Object.h"

#include <algorithm>
#include <iostream>

namespace Honeycomb::Object {
	Object *Object::root = new Object("Root", nullptr); // Initialize Root

	Object::Object() : Object("GameObject") {
		
	}

	Object::Object(std::string n, Object *p) {
		this->name = n;

		// If parent is provided -> Parent this to specified object
		if (p != nullptr) p->addChild(*this);
		else this->parent = nullptr;
	}

	Object::~Object() {
		// Delete all of the children and components
		while (this->children.size() != 0)
			delete this->children.at(0);
		while (this->components.size() != 0)
			delete this->components.at(0);

		// Notify parent that I am no longer a child
		this->deparent();
	}

	void Object::addChild(Object &o) {
		this->children.push_back(&o);
		
		if (o.parent != nullptr) o.parent->removeChild(&o);
		o.setParent(this);
	}

	void Object::addComponent(Component &c) {
		this->components.push_back(&c);
		
		if (c.getAttached()) c.getAttached()->removeComponent(&c);
		c.setAttached(this);
	}

	void Object::deparent() {
		// Remove this object from its parents' children and set the parent of
		// this object to nothing.
		if (this->parent != nullptr) this->parent->removeChild(this);
		this->setParent(nullptr);
	}

	Object* Object::getChild(std::string name) {
		// Go through all components and try to find one whose name matches
		for (int i = 0; i < this->children.size(); i++) {
			if (this->children.at(i)->getName() == name) {
				return this->children.at(i);
			}
		}

		// If unable to find a matching child -> Return NULL
		return NULL;
	}

	std::vector<Object*>& Object::getChildren() {
		return this->children;
	}

	Component* Object::getComponent(std::string name) {
		// Go through all components and try to find one whose name matches
		for (int i = 0; i < this->components.size(); i++) {
			if (this->components.at(i)->getName() == name) {
				return this->components.at(i);
			}
		}

		// If unable to find a matching component -> Return NULL
		return NULL;
	}

	std::vector<Component*>& Object::getComponents() {
		return this->components;
	}

	std::string Object::getName() {
		return this->name;
	}

	Object* Object::getParent() {
		return this->parent;
	}
	
	Object* Object::getRoot() {
		return Object::root;
	}

	void Object::input() {
		// Handle input for all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->input();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->input();
	}

	void Object::removeChild(Object *o) {
		children.erase( // Erase object from my children
			std::remove(children.begin(), children.end(), o), children.end());

		int i;
	}

	void Object::removeComponent(Component *c) {
		components.erase( // Erase component from my components
			std::remove(components.begin(), components.end(), c), 
			components.end());
	}

	void Object::render() {
		// Handle rendering for all children and components
		for (int i = 0; i < this->children.size(); i++) 
			this->children.at(i)->render();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->render();
	}

	void Object::setParent(Object *o) {
		this->parent = o;
	}

	void Object::start() {
		// Handle starting for all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->start();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->start();
	}

	void Object::stop() {
		// Handle starting for all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->stop();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->stop();
	}

	void Object::update() {
		// Handle updating for all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->update();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->update();
	}
}