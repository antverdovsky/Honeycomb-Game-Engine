#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include "..\shader\ShaderProgram.h"

namespace Honeycomb::Object { class GameObject; }

namespace Honeycomb::Component {
	class GameComponent {
		friend class Honeycomb::Object::GameObject;

	public:
		/// Creates a Component instance with the "Component" name.
		GameComponent();

		/// Creates a Component instance with the specified name.
		/// const string &name : The name of this Component.
		GameComponent(const std::string &name);

		/// Deletes this Component.
		virtual ~GameComponent();

		/// Clones this Component into a new, dynamically allocated, component.
		/// Do note that the object to which this component is attached will
		/// not add the cloned component as a component.
		/// return : The pointer to the newly cloned Component.
		virtual GameComponent* clone() const;

		/// Detaches this Component from its current object, and sets the
		/// current object to which it is attached to pointer to nullptr.
		void detach();

		/// Returns the object to which this component is attached to.
		/// return : The pointer to the object.
		Honeycomb::Object::GameObject* getAttached();

		/// Returns the object to which this component is attached to.
		/// return : The constant pointer to the object.
		const Honeycomb::Object::GameObject* getAttached() const;

		/// Gets a boolean representing whether this game object is active
		/// or not.
		/// return : A boolean reference representing whether the game object 
		///			 is active.
		bool& getIsActive();

		/// Gets a boolean representing whether this game object is active
		/// or not.
		/// return : A constant boolean reference representing whether the game
		///			 object is active.
		const bool& getIsActive() const;

		/// Returns the name of this component.
		/// return : A constant string reference containing the name of this
		///			 Game Component.
		virtual const std::string& getName() const;

		/// Handles any input events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void input();

		/// Handles any render events for this component, if necessary. This 
		/// method will only do something if the object is active.
		/// ShaderProgram &shader : The shader to be used when rendering
		///							this game component.
		virtual void render(Honeycomb::Shader::ShaderProgram &shader);
		
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