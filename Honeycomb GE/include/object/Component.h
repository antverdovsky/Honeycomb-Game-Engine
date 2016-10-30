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

		/// Returns the object to which this component is attached to.
		/// return : The pointer to the object.
		Object* getAttached();

		/// Returns the name of this component.
		virtual std::string getName();

		/// Handles any input events for this component, if necessary.
		virtual void input();

		/// Handles any render events for this component, if necessary.
		virtual void render();

		/// Sets the object to which this component is attached to.
		/// Object &o : The object to which to attach this component.
		void setAttached(Object &o);

		/// Handles any starting events for this component, if necessary.
		virtual void start();

		/// Handles any stopping events for this component, if necessary.
		virtual void stop();

		/// Handles any update events for this component, if necessary.
		virtual void update();
	private:
		Object* attached; // The object to which this component is attached
		std::string name; // The name of this component
	};
}

#endif