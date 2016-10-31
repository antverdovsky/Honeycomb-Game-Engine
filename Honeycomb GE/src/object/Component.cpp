#include "..\..\include\object\Component.h"

#include "..\..\include\object\Object.h"

namespace Honeycomb::Object {
	Component::Component() : Component("Component") {

	}

	Component::Component(std::string name) {
		this->name = name;
		this->attached = nullptr;
	}

	Component::~Component() {
		// Notify object that I am no longer attached
		this->detach();
	}

	void Component::detach() {
		if (this->attached != nullptr) this->attached->removeComponent(this);
		this->setAttached(nullptr); // Set NULL as the new attached object
	}

	Object* Component::getAttached() {
		return this->attached;
	}

	std::string Component::getName() {
		return this->name;
	}

	void Component::input() {

	}

	void Component::render() {

	}

	void Component::setAttached(Object *o) {
		this->attached = o;
	}

	void Component::start() {

	}

	void Component::stop() {

	}
	
	void Component::update() {

	}
}