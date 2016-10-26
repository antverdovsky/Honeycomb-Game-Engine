#include "..\..\include\object\Component.h"

namespace Honeycomb::Object {
	Component::Component() : Component("Component") {

	}

	Component::Component(std::string name) {
		this->name = name;
	}

	Component::~Component() {

	}

	std::string Component::getName() {
		return this->name;
	}

	void Component::render() {

	}
	
	void Component::update() {

	}
}