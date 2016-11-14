#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <vector>

#include "EventHandler.h"

namespace Honeycomb::Conjuncture {
	class Event {
	public:
		/// Instantiates a new event.
		Event();

		/// Deletes this event.
		~Event();

		/// Adds the specified event handler to this event, so that it may be
		/// notified once the event occurs.
		void addEventHandler(EventHandler *eH);

		/// Should be called when an event occurs. This will notify all event 
		/// handlers that this event is occuring.
		void onEvent();
	private:
		std::vector<EventHandler*> eHandlers; // All event handlers
	};
}

#endif