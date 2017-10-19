#pragma once
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>
#include <functional>

namespace Honeycomb { namespace Conjuncture {
	class Event;

	class EventHandler {
		friend class Event;
	public:
		/// <summary>
		/// Initializes a new instance of the Event Handler class. By default,
		/// the Event Handler is not subscribed to any events.
		/// </summary>
		EventHandler();

		/// <summary>
		/// Removes this Event Handler from any events which it may be 
		/// subscribed to.
		/// </summary>
		~EventHandler();

		/// <summary>
		/// Copying of Event Handlers is forbidden.
		/// </summary>
		EventHandler(const EventHandler &) = delete;
		
		/// <summary>
		/// Adds a function which is to be called when an event that this
		/// handler is subscribed to is triggered.
		/// </summary>
		/// <param name="">
		/// The function which should be called when the event is triggered.
		/// </param>
		void addAction(std::function<void()>);

		/// <summary>
		/// Clears all of the actions of this Event Handler.
		/// </summary>
		void clearActions();

		/// <summary>
		/// Adds the specified action to this Event Handler.
		/// </summary>
		/// <param name="">
		/// The function which should be called when the event is triggered.
		/// </param>
		/// <returns>
		/// This instance.
		/// </returns>
		EventHandler& operator+=(std::function<void()>);

		/// <summary>
		/// Assignment of Event Handlers is forbidden.
		/// </summary>
		EventHandler& operator=(const EventHandler &) = delete;
	private:
		// List of all functions which are called once the event is triggered
		std::vector<std::function<void()>> actions;

		// The events to which this Event Handler is subscribed
		std::vector<Event*> events;

		/// <summary>
		/// Calls all of the action functions of this Event Handler.
		/// </summary>
		void onEvent() const;

		/// <summary>
		/// Calls all of the action functions of this Event Handler.
		/// </summary>
		void operator()() const;
	};
} }

#endif
