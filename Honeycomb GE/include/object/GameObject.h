#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <string>
#include <vector>

#include "../component/GameComponent.h"
#include "../debug/Logger.h"

namespace Honeycomb { namespace Component { class GameComponent; } }
namespace Honeycomb { namespace Scene { class GameScene; } }

namespace Honeycomb { namespace Object {
	/// <summary>
	/// Exception which is to be thrown when a Game Object does not have a
	/// component or child which the user is trying to access.
	/// </summary>
	class GameEntityNotAttachedException : public std::runtime_error {
	public:
		/// <summary>
		/// Creates a new Game Entity Not Attached Exception for the object
		/// of the specified name.
		/// </summary>
		/// <param name="g">
		/// The game object which does not contain the Game Entity of the
		/// given name.
		/// </param>
		/// <param name="name">
		/// The name of the Game Entity which is not attached.
		/// </param>
		GameEntityNotAttachedException(const GameObject *g,
			const std::string &name);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info containing the name
		/// of the Game Object and the name of the entity which could not be
		/// fetched from the Game Object.
		/// </returns>
		virtual const char* what() const throw();
	private:
		const GameObject *gameObject;   // Game Object for which exc. is thrown
		std::string entityName;         // Name of entity which D.N.E.
	};

	class GameObject {
		friend class Honeycomb::Scene::GameScene;
	public:
		/// Initializes a Game Object with the "GameObject" name and root as
		/// parent.
		GameObject();

		/// <summary>
		/// No copy constructor exists for the Game Object class.
		/// </summary>
		GameObject(const GameObject &object) = delete;

		/// Instantializes a Game Object with the specified name.
		/// const string &n : The name of this Game Object.
		GameObject(const std::string &n);

		/// Deletes this Game Object, its children and its components.
		virtual ~GameObject();

		/// <summary>
		/// Adds the specified Game Object as a child of this Game Object. If
		/// the specified Game Object is already a child of this Game Object,
		/// no further action is taken. If the specified Game Object is already
		/// a child of some other Game Object, the child is detached from its
		/// current parent and reattached to this Game Object. Since the child
		/// is passed as a unique pointer, this Game Object instance will take
		/// ownership of the pointer.
		/// </summary>
		/// <param name="object">
		/// The object to be parented to this Game Object.
		/// </param>
		/// <returns>
		/// The reference to the new child Game Object.
		/// </returns>
		GameObject& addChild(std::unique_ptr<GameObject> object);

		/// Adds the specified component to this game object, if it is not
		/// already a child of this game object.
		/// Component &c : The component to be parented to this game object.
		Honeycomb::Component::GameComponent& addComponent(std::unique_ptr<
				Honeycomb::Component::GameComponent> c);

		/// <summary>
		/// Clones this Game Object into a new, independent Game Object. The
		/// Game Object will have all of the same properties, components and
		/// children of this Game Object, but they will all be cloned and 
		/// independent of this Game Object. The cloned Game Object will not be
		/// parented to any Scene or Game Object, nor will it be active by
		/// default.
		/// </summary>
		/// <returns>
		/// The unique pointer to the Game Object clone instance.
		/// </returns>
		std::unique_ptr<GameObject> clone() const;

		/// <summary>
		/// Deparents this Game Object from its parent, if it has one. If the
		/// Game Object has no parent, no action is taken.
		/// </summary>
//		void deparent();

		/// <summary>
		/// Gets the child of this Game Object which has the specified name. If
		/// the object has multiple children of the specified name, the first
		/// child found in the children vector is returned.
		/// </summary>
		/// <param name="name">
		/// The name of the Game Object child.
		/// </param>
		/// <returns>
		/// The reference to the child Game Object.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no child of the specified name.
		/// </exception>
		GameObject& getChild(const std::string &name);

		/// <summary>
		/// Gets the child of this Game Object which has the specified name. If
		/// the object has multiple children of the specified name, the first
		/// child found in the children vector is returned.
		/// </summary>
		/// <param name="name">
		/// The name of the Game Object child.
		/// </param>
		/// <returns>
		/// The constant reference to the child Game Object.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no child of the specified name.
		/// </exception>
		const GameObject& getChild(const std::string &name) const;

		/// <summary>
		/// Returns a list of all of the children of this Game Object.
		/// </summary>
		/// <returns>
		/// The list of the children, returned by constant reference.
		/// </returns>
		const std::vector<std::unique_ptr<GameObject>>& getChildren() const;
/*
		/// <summary>
		/// Gets the component of this Game Object which has the specified
		/// name. If the object has multiple game components of the specified
		/// name, the first component found in the components vector is
		/// returned.
		/// </summary>
		/// <param name="name">
		/// The name of the Game Component attached to this Game Object.
		/// </param>
		/// <returns>
		/// The reference to the attached Game Component.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no component of the specified name.
		/// </exception>
		Honeycomb::Component::GameComponent&
			getComponent(const std::string &name);

		/// <summary>
		/// Gets the component of this Game Object which has the specified
		/// name. If the object has multiple game components of the specified
		/// name, the first component found in the components vector is
		/// returned.
		/// </summary>
		/// <param name="name">
		/// The name of the Game Component attached to this Game Object.
		/// </param>
		/// <returns>
		/// The constant reference to the attached Game Component.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no component of the specified name.
		/// </exception>
		const Honeycomb::Component::GameComponent&
				getComponent(const std::string &name) const;
*/
		/// <summary>
		/// Gets the component of this Game Object which has the specified Type
		/// and downcasts it to that type. If the game object has multiple game
		/// components of the specified type, the first component found in the
		/// components vector is returned.
		/// </summary>
		/// <typeparam name="Type">
		/// The type of the game component which is attached to this Game 
		/// Object.
		/// </typeparam>
		/// <returns>
		/// The reference to the game component found.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no component of the specified name.
		/// </exception>
		template<class Type> 
		Type& getComponent() {
			return const_cast<Type&>(static_cast<const GameObject*>
				(this)->getComponent<Type>());
		}

		/// <summary>
		/// Gets the component of this Game Object which has the specified Type
		/// and downcasts it to that type. If the game object has multiple game
		/// components of the specified type, the first component found in the
		/// components vector is returned.
		/// <summary>
		/// <typeparam name="Type">
		/// The type of the game component which is attached to this Game 
		/// Object.
		/// </typeparam>
		/// <returns>
		/// The constant reference to the game component found.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no component of the specified name.
		/// </exception>
		template<class Type> 
		const Type& getComponent() const {
			unsigned int id = Honeycomb::Component::GameComponent::getGameComponentTypeID<Type>();
			const std::vector<std::unique_ptr<Honeycomb::Component::GameComponent>>&
				componentsOfType = this->components.at(id);

			for (auto &comp : componentsOfType) {
				return dynamic_cast<const Type&>(*comp.get());
			}

			throw GameEntityNotAttachedException(this, typeid(Type).name());
		}
/*
		/// Gets the component with the specified name, downcast to the
		/// specific type of component.
		/// class Type : The type of the component.
		/// const string &name : The name of the component.
		/// return : The pointer to the component object.
		template<class Type> 
		Type& getComponent(const std::string &name) {
			return const_cast<Type&>(static_cast<const GameObject*>
				(this)->getComponent<Type>(name));
		}

		/// <summary>
		/// Gets the component of this Game Object which has the specified Type
		/// and name and downcasts it to that type. If the game object has 
		/// multiple game components of the specified type, the first component
		/// found in the components vector is returned.
		/// <summary>
		/// <param name="name">
		/// The name of the game component to be found.
		/// </param>
		/// <typeparam name="Type">
		/// The type of the game component which is attached to this Game 
		/// Object.
		/// </typeparam>
		/// <returns>
		/// The constant reference to the game component found.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no component of the specified name.
		/// </exception>
		template<class Type> 
		const Type& getComponent(const std::string &name) const {
			for (auto comp : this->components) {
				if (dynamic_cast<Type*>(comp.get()) != nullptr &&
					comp->getName() == name) {
					return dynamic_cast<const Type&>(*comp.get());
				}
			}

			throw GameEntityNotAttachedException(this, typeid(Type).name);
		}
*/
		/// <summary>
		/// Gets a 2D representation of the Game Components attached to this
		/// Game Object. For each Game Component, there exists a 1D array 
		/// inside the 2D array, at the index of the Game Component ID, such
		/// that the 1D array contains pointers to all of the Game Components
		/// of that type that are attached to this Game Object.
		/// </summary>
		/// <returns>
		/// The 2D representation of the Game Components.
		/// </returns>
		const std::vector<std::vector<std::unique_ptr<
				Honeycomb::Component::GameComponent>>>& getComponents() const;

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

		/// Returns the scene of this Game Object.
		/// return : The pointer to the Game Scene.
		Honeycomb::Scene::GameScene* getScene();

		/// Returns the scene of this Game Object.
		/// return : The constant pointer to the Game Scene.
		const Honeycomb::Scene::GameScene* getScene() const;
/*
		/// Checks if this Game Object has the specified child.
		/// const GameObject &child : The game object which is to be checked.
		/// return : True if the specified game object is a child of this.
		///			 False otherwise.
		bool hasChild(const GameObject &child) const;
*/
		/// <summary>
		/// Checks if the specified component is attached to this Game Object.
		/// </summary>
		/// <param name="component">
		/// The component which is to be checked.
		/// </param>
		/// <returns>
		/// True if that specific component instance is attached to this Game
		/// Object.
		/// </returns>
		bool hasComponent(const Honeycomb::Component::GameComponent 
				*component) const;

		/// <summary>
		/// Checks if this Game Object has at least one component of the
		/// specified type.
		/// </summary>
		/// <typeparam name="T">
		/// The type of the Game Component.
		/// </typeparam>
		/// <returns>
		/// True if this Game Object has at least one component of the 
		/// specified type. False otherwise.
		/// </returns>
		template<typename T>
		bool hasComponent() const {
			// Get the list of components of the specified type
			unsigned int id = Honeycomb::Component::GameComponent::
				getGameComponentTypeID<T>();
			std::vector<std::unique_ptr<Honeycomb::Component::GameComponent>>&
				componentsOfType = this->components.at(id);

			// If at least one component of that type is owned by this, return
			// true.
			return componentsOfType.size() > 0;
		}

		/// Handles any input events for this component, if necessary. This 
		/// method will only do something if the object is active.
		virtual void input();

		/// Removes the component from the components of this object, if it
		/// exists as an attached component. Once the component is removed, it
		/// will be "attached" to NULL.
		/// Component *c : The component to be removed.
		std::unique_ptr<Honeycomb::Component::GameComponent> 
				removeComponent(Honeycomb::Component::GameComponent *c);

		/// <summary>
		/// Removes the specified child from this Game Object and returns a
		/// unique pointer to it.
		/// </summary>
		/// <param name="child">
		/// The pointer to the child which is to be removed.
		/// </param>
		/// <returns>
		/// The unique pointer to the child after it has been removed from this
		/// Game Object.
		/// </returns>
		std::unique_ptr<GameObject> removeChild(GameObject *child);

		/// Handles any render events for this component, if necessary. This 
		/// method will only do something if the object is active.
		/// ShaderProgram &shader : The shader to be used when rendering.
		virtual void render(Honeycomb::Shader::ShaderProgram &shader);

		/// Sets the Game Scene of this Game Object and all of the children of
		/// this Game Object.
		/// GameScene *scene : The new scene of this Game Object.
		void setScene(Honeycomb::Scene::GameScene *scene);

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

		/// <summary>
		/// No assignment operator exists for the Game Object class.
		/// </summary>
		GameObject& operator=(const GameObject &object) = delete;
	protected:
		bool isActive; // Is this object active?
		std::string name; // Name of this Game Object
		
		GameObject *parent; // The parent of this Game Object
		Honeycomb::Scene::GameScene *scene; // Scene to which this belongs to

		// The children and components of this Game Object
		std::vector<std::unique_ptr<GameObject>> children;

		// The 2D array of all of the components of the Game Object. For each
		// Game Component, there exists an array, at the index of the Game
		// Component ID, which contains all of the Game Components of that
		// type which are attached to this Game Object.
		std::vector<std::vector<std::unique_ptr<
				Honeycomb::Component::GameComponent>>> components;
	};
} }

#endif
