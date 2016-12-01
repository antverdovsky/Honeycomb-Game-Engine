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

	void EventHandler::clearActions() {
		this->actions.clear();
	}

	EventHandler& EventHandler::operator+=(std::function<void()> f) {
		this->addAction(f);

		return *this;
	}

	void EventHandler::onEvent() const {
		std::vector<std::function<void()>>::const_iterator i; // Get Iterator

		// Call all of the functions which are binded to this event handler
		for (i = this->actions.begin(); i < this->actions.end(); i++) (*i)();
	}

	void EventHandler::operator()() const {
		this->onEvent();
	}
}