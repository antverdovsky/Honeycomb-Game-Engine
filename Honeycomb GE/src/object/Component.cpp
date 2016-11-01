#include "..\..\include\object\Component.h"

#include "..\..\include\object\Object.h"

namespace Honeycomb::Object {
	Component::Component() : Component("Component") {

	}

	Component::Component(std::string name) {
		this->name = name;
		this->isActive = false;
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

	bool& Component::getIsActive() {
		return this->isActive;
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
		this->isActive = true;
	}

	void Component::stop() {
		this->isActive = false;
	}
	
	void Component::update() {

	}
}