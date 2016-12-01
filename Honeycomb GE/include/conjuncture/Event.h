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
		/// const EventHandler &eH : The event handler to be attached to this
		///							 Event.
		void addEventHandler(const EventHandler &eH);

		/// Clears all of the event handlers attached to this event. The event
		/// handlers will no longer be notified once the event occurs, however,
		/// the event handler itself is not modified.
		void clearEventHandlers();

		/// Should be called when an event occurs. This will notify all event 
		/// handlers that this event is occuring, in the order in which they
		/// were added.
		void onEvent() const;

		/// Removes the specified event handler from this event, so that it may
		/// no longer be notified once the event occurs.
		/// const EventHandler &eH : The event handler which is to be detached
		///							 from this event.
		void removeEventHandler(const EventHandler &eH);

		/// Adds the specified event handler to this event, so that it may be
		/// notified once the event occurs.
		/// const EventHandler &eH : The event handler to be attached to this
		///							 Event.
		Event& operator+=(const EventHandler &eH);

		/// Removes the specified event handler from this event, so that it may
		/// no longer be notified once the event occurs.
		/// const EventHandler &eH : The event handler to be detached from this
		///							 Event.
		Event& operator-=(const EventHandler &eH);

		/// Triggers the on event of this Event.
		void operator()();
	private:
		std::vector<const EventHandler*> eHandlers; // All event handlers
	};
}

#endif