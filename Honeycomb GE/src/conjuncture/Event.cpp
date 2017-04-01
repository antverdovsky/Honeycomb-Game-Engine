#include "../../include/conjuncture/Event.h"

#include <algorithm>

#include <iostream>

namespace Honeycomb { namespace Conjuncture {
	Event::Event() {

	}

	Event::~Event() {

	}

	void Event::addEventHandler(const EventHandler &eH) {
		this->eHandlers.push_back(&eH); // Add handler to list of handlers
	}

	void Event::clearEventHandlers() {
		this->eHandlers.clear();
	}

	void Event::onEvent() const {
		// Notifies all event handlers that the event is occuring
		for (const EventHandler *eH : this->eHandlers) eH->onEvent();
	}

	void Event::removeEventHandler(const EventHandler &eH) {
		if (this->eHandlers.size() == 0) return; // If empty, return
		const EventHandler *eH_ptr = &eH; // Pointer to reference, for compare

		this->eHandlers.erase( // Remove handler from list of handlers
			std::remove(eHandlers.begin(), eHandlers.end(), eH_ptr),
			eHandlers.end());
	}

	Event& Event::operator+=(const EventHandler &eH) {
		this->addEventHandler(eH);

		return *this;
	}

	Event& Event::operator-=(const EventHandler &eH) {
		this->removeEventHandler(eH);
		
		return *this;
	}

	void Event::operator() () {
		this->onEvent();
	}
} }
