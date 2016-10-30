#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

#include "Component.h"

namespace Honeycomb::Object {
	class Object {
	public:
		/// Initializes a Game Object with the "GameObject" name and root as
		/// parent.
		Object();

		/// Instantializes a Game Object with the specified name and parent
		/// (root by default).
		/// string n : The name of this Game Object.
		/// Object p : The parent of this Game Object. If none is specified,
		///			   the object will be parented to the root. NULL may also
		///			   be provided but the object will have NO parent (use at
		///			   own risk).
		Object(std::string n, Object *p = root);

		/// Deletes this Game Object, its children and its components.
		~Object();

		/// Adds the specified object as a child to this game object.
		/// Object &o : The object to be parented to this game object.
		void addChild(Object &o);

		/// Adds the specified component to this game object.
		/// Component &c : The component to be parented to this game object.
		void addComponent(Component &c);

		/// Gets the child with the specified name, or NULL if no such child
		/// exists.
		/// string name : The name of the child.
		/// return : The child object.
		Object* getChild(std::string name);

		/// Gets all the children game objects of this game object.
		/// return : The list containing the children game objects.
		std::vector<Object*>& getChildren();

		/// Gets the component with the specified name, or NULL if no such
		/// component exists.
		/// string name : The name of the component.
		/// return : The component object.
		Component* getComponent(std::string name);

		/// Gets the component with the specified name, downcast to the
		/// specific type of component.
		/// class Type : The type of the component.
		/// string name : The name of the component.
		/// return : The component object.
		template<class Type>
		inline Type* getComponentOfType(std::string name) {
			Component *comp = this->getComponent(name); // Get component

			// If the component does not exist -> Return NULL.
			// Otherwise, return the component, cast down to its specific type.
			if (comp == NULL) return NULL;
			else return dynamic_cast<Type*>(this->getComponent(name));
		}

		/// Gets all the components of this game object.
		/// return : The list containing the components.
		std::vector<Component*>& getComponents();

		/// Gets the name of this game object.
		std::string getName();

		/// Returns the parent of this Game Object.
		/// return : The pointer to the parent.
		Object* getParent();

		/// Returns the Root game object.
		/// return : The Root object.
		static Object* getRoot();

		/// Handles any input events for this component, if necessary.
		virtual void input();

		/// Handles any render events for this component, if necessary.
		virtual void render();

		/// Sets the parent of this game object to the specified game object.
		/// Object &o : The new parent of this game object.
		void setParent(Object &o);

		/// Handles any starting events for this component, if necessary.
		virtual void start();

		/// Handles any stopping events for this component, if necessary.
		virtual void stop();

		/// Handles any update events for this component, if necessary.
		virtual void update();
	private:
		static Object *root; // The root object of the game scene

		Object* parent; // The parent of this Game Object
		std::string name; // Name of this Game Object
		std::vector<Object*> children; // Children of this Game Object
		std::vector<Component*> components; // Components of this Game Object
	};
}

#endif