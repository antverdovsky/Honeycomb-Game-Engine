#include "..\..\include\conjuncture\Event.h"

#include <algorithm>

#include <iostream>

namespace Honeycomb::Conjuncture {
	Event::Event() {

	}

	Event::~Event() {

	}

	void Event::addEventHandler(EventHandler *eH) {
		this->eHandlers.push_back(eH); // Add handler to list of handlers
	}

	void Event::onEvent() {
		// Notifies all event handlers that the event is occuring
		for (EventHandler *eH : this->eHandlers) eH->onEvent();
	}

	void Event::removeEventHandler(EventHandler *eH) {
		this->eHandlers.erase( // Remove handler from list of handlers
			std::remove(eHandlers.begin(), eHandlers.end(), eH), 
			eHandlers.end());
	}

	Event& Event::operator+=(EventHandler *eH) {
		this->addEventHandler(eH);

		return *this;
	}

	Event& Event::operator-=(EventHandler *eH) {
		this->addEventHandler(eH);
		
		return *this;
	}

	void Event::operator() () {
		this->onEvent();
	}
}