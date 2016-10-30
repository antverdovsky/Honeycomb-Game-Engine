#include "..\..\include\object\Component.h"

namespace Honeycomb::Object {
	Component::Component() : Component("Component") {

	}

	Component::Component(std::string name) {
		this->name = name;
	}

	Component::~Component() {

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

	void Component::setAttached(Object &o) {
		this->attached = &o;
	}

	void Component::start() {

	}

	void Component::stop() {

	}
	
	void Component::update() {

	}
}