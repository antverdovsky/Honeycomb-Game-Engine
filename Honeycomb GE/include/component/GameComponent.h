#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

namespace Honeycomb::Object { class GameObject; }

namespace Honeycomb::Component {
	class GameComponent {
	public:
		/// Creates a Component instance with the "Component" name.
		GameComponent();

		/// Creates a Component instance with the specified name.
		/// string name : The name of this Component.
		GameComponent(std::string name);

		/// Deletes this Component.
		~GameComponent();

		/// Clones this Component into a new, dynamically allocated, component.
		/// This function should be used instead of the copy constructor to
		/// prevent object slicing.
		/// return : The cloned Component.
		virtual GameComponent* clone();

		/// Detaches this Component from its current object, and sets the
		/// current object to which it is attached to NULL.
		void detach();

		/// Returns the object to which this component is attached to.
		/// return : The pointer to the object.
		Honeycomb::Object::GameObject* getAttached();

		/// Gets a boolean representing whether this game object is active
		/// or not.
		/// return : A boolean representing whether the game object is active.
		bool& getIsActive();

		/// Returns the name of this component.
		virtual std::string getName() const;

		/// Handles any input events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void input();

		/// Handles any render events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void render();

		/// Sets the object to which this component is attached to.
		/// Object *o : The object to which to attach this component.
		void setAttached(Honeycomb::Object::GameObject *o);

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
		// Object to which the component is attached to
		Honeycomb::Object::GameObject* attached;

		bool isActive; // Is this game component active?
		std::string name; // The name of this component
	};
}

#endif