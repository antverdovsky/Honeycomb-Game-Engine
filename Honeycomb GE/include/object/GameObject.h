#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

#include "..\component\GameComponent.h"

namespace Honeycomb::Component { class GameComponent; }

namespace Honeycomb::Object {
	class GameObject {
	public:
		/// Initializes a Game Object with the "GameObject" name and root as
		/// parent.
		GameObject();

		/// Instantializes a Game Object with the specified name.
		/// const string &n : The name of this Game Object.
		GameObject(const std::string &n);

		/// Deletes this Game Object, its children and its components.
		~GameObject();

		/// Clones this Game Object into a new, dynamically allocated, Game
		/// Object.
		/// return : The cloned Game Object.
		GameObject* clone() const;

		/// Adds the specified object as a child to this game object.
		/// Object &o : The object to be parented to this game object.
		void addChild(GameObject &o);

		/// Adds the specified component to this game object.
		/// Component &c : The component to be parented to this game object.
		void addComponent(Honeycomb::Component::GameComponent &c);

		/// Deparents this object from whatever parent it may currently have
		/// so that its new parent becomes NULL.
		void deparent();

		/// Gets the child with the specified name, or NULL if no such child
		/// exists.
		/// const string &name : The name of the child.
		/// return : The pointer to the child object.
		GameObject* getChild(const std::string &name);

		/// Gets the child with the specified name, or NULL if no such child
		/// exists.
		/// const string &name : The name of the child.
		/// return : The constant pointer to the child object.
		const GameObject* getChild(const std::string &name) const;

		/// Gets all the children game objects of this game object.
		/// return : The list containing the children game objects.
		std::vector<GameObject*>& getChildren();

		/// Gets all the children game objects of this game object.
		/// return : The constant list containing the children game objects.
		const std::vector<GameObject*>& getChildren() const;

		/// Gets the component with the specified name, or NULL if no such
		/// component exists.
		/// const string &name : The name of the component.
		/// return : The component object.
		Honeycomb::Component::GameComponent*
			getComponent(const std::string &name);

		/// Gets the component with the specified name, or NULL if no such
		/// component exists.
		/// const string &name : The name of the component.
		/// return : The component object.
		const Honeycomb::Component::GameComponent*
				getComponent(const std::string &name) const;
		
		/// Gets the component with the specified name, downcast to the
		/// specific type of component.
		/// class Type : The type of the component.
		/// const string &name : The name of the component.
		/// return : The pointer to the component object.
		template<class Type>
		inline Type* getComponentOfType(const std::string &name) {
			Honeycomb::Component::GameComponent *comp =
				this->getComponent(name); // Get component

			// If the component does not exist -> Return NULL.
			// Otherwise, return the component, cast down to its specific type.
			if (comp == NULL) return NULL;
			else return dynamic_cast<Type*>(this->getComponent(name));
		}

		/// Gets the component with the specified name, downcast to the
		/// specific type of component.
		/// class Type : The type of the component.
		/// const string &name : The name of the component.
		/// return : The constant pointer to the component object.
		template<class Type>
		const inline Type* getComponentOfType(const std::string &name) const {
			Honeycomb::Component::GameComponent *comp = 
				this->getComponent(name); // Get component

			// If the component does not exist -> Return NULL.
			// Otherwise, return the component, cast down to its specific type.
			if (comp == NULL) return NULL;
			else return dynamic_cast<Type*>(this->getComponent(name));
		}

		/// Gets all the components of this game object.
		/// return : The list containing the components.
		std::vector<Honeycomb::Component::GameComponent*>& getComponents();

		/// Gets all the components of this game object.
		/// return : The constant list containing the components.
		const std::vector<Honeycomb::Component::GameComponent*>& 
				getComponents() const;

		/// Gets a boolean representing whether this game object is active
		/// or not.
		/// return : A boolean representing whether the game object is active.
		const bool& getIsActive() const;

		/// Gets the name of this game object.
		const std::string& getName() const;

		/// Returns the parent of this Game Object.
		/// return : The pointer to the parent.
		GameObject* getParent();

		/// Returns the parent of this Game Object.
		/// return : The constant pointer to the parent.
		const GameObject* getParent() const;

		/// Handles any input events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void input();

		/// Removes the specified child from the children of this object, if
		/// it exists as a child. Once the child is removed, its new parent
		/// will be the root object.
		/// Object *o : The object to be removed.
		void removeChild(GameObject *o);

		/// Removes the component from the components of this object, if it
		/// exists as an attached component. Once the component is removed, it
		/// will be "attached" to NULL.
		/// Component *c : The component to be removed.
		void removeComponent(Honeycomb::Component::GameComponent *c);

		/// Handles any render events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void render();

		/// Handles any starting events for this component, if necessary.
		/// Additionally, this method will make this object active when
		/// called.
		virtual void start();

		/// Handles any stopping events for this component, if necessary.
		/// Additionally, this method will make this object inactive when
		/// called.
		virtual void stop();

		/// Handles any update events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void update();
	protected:
		bool isActive; // Is this object active?
		std::string name; // Name of this Game Object
		
		GameObject* parent; // The parent of this Game Object

		// The children and components of this Game Object
		std::vector<GameObject*> children;
		std::vector<Honeycomb::Component::GameComponent*> components;
	};
}

#endif