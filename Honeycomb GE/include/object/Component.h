#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

namespace Honeycomb::Object { class Object; }

namespace Honeycomb::Object {
	class Component {
	public:
		/// Creates a Component instance with the "Component" name.
		Component();

		/// Creates a Component instance with the specified name.
		/// string name : The name of this Component.
		Component(std::string name);
		
		/// Deletes this Component.
		~Component();

		/// Detaches this Component from its current object, and sets the
		/// current object to which it is attached to NULL.
		void detach();

		/// Returns the object to which this component is attached to.
		/// return : The pointer to the object.
		Object* getAttached();

		/// Gets a boolean representing whether this game object is active
		/// or not.
		/// return : A boolean representing whether the game object is active.
		bool& getIsActive();

		/// Returns the name of this component.
		virtual std::string getName();

		/// Handles any input events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void input();

		/// Handles any render events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void render();

		/// Sets the object to which this component is attached to.
		/// Object *o : The object to which to attach this component.
		void setAttached(Object *o);

		/// Handles any starting events for this component, if necessary.
		/// Additionally, this method will make this component active when
		/// called.
		virtual void start();

		/// Handles any stopping events for this component, if necessary.
		/// Additionally, this method will make this component inactive when
		/// called.
		virtual void stop();

		/// Handles any update events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void update();
	protected:
		bool isActive; // Is this game component active?
		Object* attached; // The object to which this component is attached
		std::string name; // The name of this component
	};
}

#endif