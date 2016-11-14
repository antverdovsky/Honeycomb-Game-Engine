#include "..\..\include\conjuncture\EventHandler.h"

#include <algorithm>

namespace Honeycomb::Conjuncture {
	EventHandler::EventHandler() {

	}

	EventHandler::~EventHandler() {

	}

	void EventHandler::addAction(std::function<void()> f) {
		this->actions.push_back(f); // Add function to actions
	}

	EventHandler& EventHandler::operator+= (std::function<void()> f) {
		this->addAction(f);

		return *this;
	}

	void EventHandler::onEvent() {
		std::vector<std::function<void()>>::iterator i; // Get Iterator

		// Call all of the functions which are binded to this event handler
		for (i = this->actions.begin(); i < this->actions.end(); i++) (*i)();
	}

	void EventHandler::operator() () {
		this->onEvent();
	}
}