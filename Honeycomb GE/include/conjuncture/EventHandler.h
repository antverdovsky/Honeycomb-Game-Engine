#pragma once
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>
#include <functional>

namespace Honeycomb::Conjuncture {
	class EventHandler {
	public:
		/// Instantiates a new instance of the Event Handler structure.
		EventHandler();

		/// Deletes this instance of the Event Handler structure.
		~EventHandler();

		/// Adds the specified action, which will occur once the event occurs.
		/// function<void()> : The function to be called once the event occurs.
		void addAction(std::function<void()>);

		/// Called by an event when said event is occuring.
		void onEvent();
	private:
		// List of all the functions which should be called once the event is
		// triggered.
		std::vector<std::function<void()>> actions;
	};
}

#endif