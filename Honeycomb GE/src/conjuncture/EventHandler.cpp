#include "../../include/conjuncture/EventHandler.h"

#include <algorithm>

#include "../../include/conjuncture/Event.h"

namespace Honeycomb { namespace Conjuncture {
	EventHandler::EventHandler() {

	}

	EventHandler::~EventHandler() {
		for (auto *e : this->events) 
			e->removeEventHandler(this);
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
		// Call all of the functions which are binded to this event handler
		for (auto i = this->actions.begin(); i < this->actions.end(); i++) 
			(*i)();
	}

	void EventHandler::operator()() const {
		this->onEvent();
	}
} }
