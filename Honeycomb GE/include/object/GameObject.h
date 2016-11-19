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

		/// Instantializes a Game Object with the specified name and parent
		/// (root by default).
		/// string n : The name of this Game Object.
		/// Object p : The parent of this Game Object. If none is specified,
		///			   the object will be parented to the root. NULL may also
		///			   be provided but the object will have NO parent (use at
		///			   own risk).
		GameObject(std::string n, GameObject *p = root);

		/// Copies the specified Game Object into a new Game Object.
		/// GameObejct &o : The Game Object to be copied into this game object.
		GameObject::GameObject(GameObject &o);

		/// Deletes this Game Object, its children and its components.
		~GameObject();

		/// Clones this Game Object into a new, dynamically allocated, Game
		/// Object.
		/// return : The cloned Game Object.
		GameObject* clone();

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
		/// string name : The name of the child.
		/// return : The child object.
		GameObject* getChild(std::string name);

		/// Gets all the children game objects of this game object.
		/// return : The list containing the children game objects.
		std::vector<GameObject*>& getChildren();

		/// Gets the component with the specified name, or NULL if no such
		/// component exists.
		/// string name : The name of the component.
		/// return : The component object.
		Honeycomb::Component::GameComponent* getComponent(std::string name);

		/// Gets the component with the specified name, downcast to the
		/// specific type of component.
		/// class Type : The type of the component.
		/// string name : The name of the component.
		/// return : The component object.
		template<class Type>
		inline Type* getComponentOfType(std::string name) {
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

		/// Gets a boolean representing whether this game object is active
		/// or not.
		/// return : A boolean representing whether the game object is active.
		bool& getIsActive();

		/// Gets the name of this game object.
		std::string getName();

		/// Returns the parent of this Game Object.
		/// return : The pointer to the parent.
		GameObject* getParent();

		/// Returns the Root game object.
		/// return : The Root object.
		static GameObject* getRoot();

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

		/// Sets the parent of this game object to the specified game object.
		/// Object *o : The new parent of this game object.
		void setParent(GameObject *o);

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
	private:
		static GameObject *root; // The root object of the game scene

		bool isActive; // Is this object active?
		GameObject* parent; // The parent of this Game Object
		std::string name; // Name of this Game Object

		std::vector<GameObject*> children;
		std::vector<Honeycomb::Component::GameComponent*> components;
	};
}

#endif