#include "..\..\include\conjuncture\Event.h"

namespace Honeycomb::Conjuncture {
	Event::Event() {

	}

	Event::~Event() {

	}

	void Event::addEventHandler(EventHandler *eH) {
		this->eHandlers.push_back(eH);
	}

	void Event::onEvent() {
		// Notifies all event handlers that the event is occuring
		for (EventHandler *eH : this->eHandlers) eH->onEvent();
	}
}