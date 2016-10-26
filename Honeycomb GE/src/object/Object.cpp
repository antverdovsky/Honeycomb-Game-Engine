#include "..\..\include\object\Object.h"

namespace Honeycomb::Object {
	Object *Object::root = new Object("Root"); // Initialize Root

	Object::Object() : Object("GameObject") {
		
	}

	Object::Object(std::string n, Object *p) {
		this->name = n;

		// If null is not provided -> Parent to object
		if (p != NULL) p->getChildren().push_back(this);
	}

	Object::~Object() {

	}

	Object* Object::getChild(std::string name) {
		// Go through all components and try to find one whose name matches
		for (int i = 0; i < this->children.size(); i++) {
			if (this->children.at(i)->name == name) {
				return this->children.at(i);
			}
		}

		// If unable to find a matching component -> 
		// Return empty component instead
		return new Object(""); // TODO
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

		// If unable to find a matching component -> 
		// Return empty component instead
		return new Component(""); // TODO
	}

	std::vector<Component*>& Object::getComponents() {
		return this->components;
	}

	Object* Object::getRoot() {
		return Object::root;
	}

	void Object::render() {
		// Render all children and components
		for (int i = 0; i < this->children.size(); i++) 
			this->children.at(i)->render();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->render();
	}

	void Object::update() {
		// Update all children and components
		for (int i = 0; i < this->children.size(); i++)
			this->children.at(i)->update();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->update();
	}
}