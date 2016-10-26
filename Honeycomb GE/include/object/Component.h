#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

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

		/// Returns the name of this component.
		virtual std::string getName();

		/// Handles any render events for this component, if necessary.
		virtual void render();

		/// Handles any update events for this component, if necessary.
		virtual void update();
	private:
		std::string name; // The name of this component
	};
}

#endif