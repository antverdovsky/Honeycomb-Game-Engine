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
		/// EventHandler *eH : Pointer to the event handler to be added.
		void addEventHandler(EventHandler *eH);

		/// Should be called when an event occurs. This will notify all event 
		/// handlers that this event is occuring, in the order in which they
		/// were added.
		void onEvent();

		/// Removes the specified event handler from this event, so that it may
		/// no longer be notified once the event occurs.
		/// EventHandler *eH : Pointer to the event handler to be deleted.
		void removeEventHandler(EventHandler *eH);

		/// Adds the specified event handler to this event, so that it may be
		/// notified once the event occurs.
		/// EventHandler *eH : The event handler to be added.
		Event& operator+= (EventHandler *eH);

		/// Removes the specified event handler from this event, so that it may
		/// no longer be notified once the event occurs.
		/// EventHandler *eH : The event handler to be removed.
		Event& operator-= (EventHandler *eH);

		/// Triggers the on event of this Event.
		void operator() ();
	private:
		std::vector<EventHandler*> eHandlers; // All event handlers
	};
}

#endif