#include "..\..\include\object\Object.h"

namespace Honeycomb::Object {
	Object *Object::root = new Object("Root", NULL); // Initialize Root

	Object::Object() : Object("GameObject") {
		
	}

	Object::Object(std::string n, Object *p) {
		this->name = n;

		// If parent is provided -> Parent this to specified object
		if (p != NULL) p->addChild(*this);
	}

	Object::~Object() {
		// Delete all of the children and components
		for (int i = 0; i < this->children.size(); i++)
			delete this->children.at(i);
		for (int i = 0; i < this->components.size(); i++)
			delete this->components.at(i);
	}

	void Object::addChild(Object &o) {
		this->children.push_back(&o);

		o.setParent(*this);
	}

	void Object::addComponent(Component &c) {
		this->components.push_back(&c);

		c.setAttached(*this);
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

	void Object::render() {
		// Handle rendering for all children and components
		for (int i = 0; i < this->children.size(); i++) 
			this->children.at(i)->render();
		for (int i = 0; i < this->components.size(); i++)
			this->components.at(i)->render();
	}

	void Object::setParent(Object &o) {
		this->parent = &o;
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