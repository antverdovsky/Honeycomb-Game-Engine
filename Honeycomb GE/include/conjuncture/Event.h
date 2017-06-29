#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <vector>

#include "EventHandler.h"

namespace Honeycomb { namespace Conjuncture {
	class Event {
	public:
		/// <summary>
		/// Instantiates a new, empty event.
		/// </summary>
		Event();

		/// <summary>
		/// Copying of the Event class is forbidden.
		/// </summary>
		Event(const Event &) = delete;

		/// <summary>
		/// Unsubscribes all of the event handlers from this Event, as it is
		/// killed.
		/// </summary>
		~Event();

		/// <summary>
		/// Adds the specified Event Handler to this event. If the Event 
		/// Handler is already added to this, it is not added again.
		/// </summary>
		/// <param name="eH">
		/// The constant pointer to the Event Handler to be added. Note that
		/// this may not be null, this is checked by a runtime assertion.
		/// </param>
		void addEventHandler(EventHandler *eH);

		/// <summary>
		/// Removes all of the Event Handlers from this event.
		/// </summary>
		void clearEventHandlers();

		/// <summary>
		/// Function which triggers the event. For each event handler attached
		/// to this Event, the event handler is notified of the event.
		/// </summary>
		void onEvent() const;

		/// <summary>
		/// Removes the specified event handler from the event handlers of this
		/// event. If the event handler is not attached to this event, no 
		/// further action is taken.
		/// </summary>
		/// <param name="eH">
		/// The constant pointer to the Event Handler to be removed. Note that
		/// this may not be null, this is checked by a runtime assertion.
		/// </param>
		void removeEventHandler(EventHandler *eH);

		/// <summary>
		/// Adds the specified Event Handler to this event. If the Event 
		/// Handler is already added to this, it is not added again.
		/// </summary>
		/// <param name="eH">
		/// The event handler to be added to the event. This may not be null,
		/// this is checked by a runtime assertion.
		/// </param>
		/// <returns>
		/// This instance.
		/// </returns>
		Event& operator+=(EventHandler *eH);

		/// <summary>
		/// Removes the specified Event Handler from this event. If the event
		/// handler is not attached to this event, no further action is taken.
		/// </summary>
		/// <param name="eH">
		/// The event handler to be removed from the event. This may not be
		/// null, this is checked by a runtime assertion.
		/// </param>
		/// <returns>
		/// This instance.
		/// </returns>
		Event& operator-=(EventHandler *eH);

		/// <summary>
		/// Triggers this Event.
		/// </summary>
		void operator()();

		/// <summary>
		/// Assignment of Event class is forbidden.
		/// </summary>
		Event& operator=(Event &eH) = delete;
	private:
		std::vector<EventHandler*> handlers; // The Event Handlers
	};
} }

#endif
