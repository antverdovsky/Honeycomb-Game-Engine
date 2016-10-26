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

		/// Deletes the Game Object.
		~Object();

		/// Gets the child with the specified name. If such a child cannot be
		/// found, then a new object will be returned with no name. The object
		/// is not parented to this object, and is merely used to indicate that
		/// the search has failed.
		/// string name : The name of the child.
		/// return : The child object.
		Object* getChild(std::string name);

		/// Gets all the children game objects of this game object.
		/// return : The list containing the children game objects.
		std::vector<Object*>& getChildren();

		/// Gets the component with the specified name.
		/// string name : The name of the component.
		/// return : The component object.
		Component* getComponent(std::string name);

		/// Gets all the components of this game object.
		/// return : The list containing the components.
		std::vector<Component*>& getComponents();

		/// Returns the Root game object.
		/// return : The Root object.
		static Object* getRoot();

		/// Renders this Game Object and its children game objects.
		void render();

		/// Updates this Game Object and its children game objects.
		void update();
	private:
		static Object *root; // The root object of the game scene

		std::string name; // Name of this Game Object
		std::vector<Object*> children; // Children of this Game Object
		std::vector<Component*> components; // Components of this Game Object
	};
}

#endif