#include "../../include/conjuncture/Event.h"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace Honeycomb { namespace Conjuncture {
	Event::Event() {

	}

	Event::~Event() {
		for (int i = this->handlers.size() - 1; i >= 0; --i)
			this->removeEventHandler(this->handlers.at(i));
	}

	void Event::addEventHandler(EventHandler *eH) {
		assert(eH != nullptr);

		if (std::find(this->handlers.begin(), this->handlers.end(), eH)
				!= this->handlers.end()) 
			return;

		this->handlers.push_back(eH);
		eH->events.push_back(this);
	}

	void Event::clearEventHandlers() {
		this->handlers.clear();
	}

	void Event::onEvent() const {
		for (const EventHandler *eH : this->handlers) 
			eH->onEvent();
	}

	void Event::removeEventHandler(EventHandler *eH) {
		assert(eH != nullptr);

		this->handlers.erase(
			std::remove(handlers.begin(), handlers.end(), eH),
			handlers.end());
		eH->events.erase(
			std::remove(eH->events.begin(), eH->events.end(), this),
			eH->events.end());
	}

	Event& Event::operator+=(EventHandler *eH) {
		this->addEventHandler(eH);

		return *this;
	}

	Event& Event::operator-=(EventHandler *eH) {
		this->removeEventHandler(eH);
		
		return *this;
	}

	void Event::operator() () {
		this->onEvent();
	}
} }
