#pragma once
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>
#include <functional>

namespace Honeycomb { namespace Conjuncture {
	class EventHandler {
		friend class Event;

	public:
		/// Instantiates a new instance of the Event Handler structure.
		EventHandler();

		/// Deletes this instance of the Event Handler structure.
		~EventHandler();

		/// Adds the specified action, which will occur once the event occurs.
		/// function<void()> : The function to be called once the event occurs.
		void addAction(std::function<void()>);

		/// Clears all of the actions of this event handler, so that no actions
		/// are triggered once the event occurs.
		void clearActions();

		/// Adds the specified action, which will occur once the event occurs.
		/// function<void()> : The function to be called once the event occurs.
		EventHandler& operator+= (std::function<void()>);
	private:
		// List of all the functions which should be called once the event is
		// triggered.
		std::vector<std::function<void()>> actions;

		/// Called by an event when said event is occuring. All actions which
		/// are attached to this handler will be called, in the order in which
		/// they were originally added.
		void onEvent() const;

		/// Triggers the on event of this Event Handler.
		void operator()() const;
	};
} }

#endif
