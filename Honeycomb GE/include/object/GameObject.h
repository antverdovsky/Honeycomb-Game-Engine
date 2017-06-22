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
		/// <summary>
		/// Initializes a new Game Object with the name "Game Object" and no
		/// parent or scene. The Game Object is not active by default and comes
		/// with no added components.
		/// </summary>
		GameObject();

		/// <summary>
		/// Initializes a new Game Object with the specified name, and no
		/// parent or scene. The Game Object is not active by default and comes
		/// with no added components.
		/// </summary>
		/// <param name="n">
		/// The name of the Game Object.
		/// </param>
		GameObject(const std::string &n);

		/// <summary>
		/// No copy constructor exists for the Game Object class.
		/// </summary>
		GameObject(const GameObject &object) = delete;

		/// <summary>
		/// Virtual Destructor for the Game Object class.
		/// </summary>
		virtual ~GameObject();

		/// <summary>
		/// Adds the specified Game Object as a child of this Game Object. If 
		/// the specified Game Object is already a child of this Game Object,
		/// no further action is taken and the reference to the child is 
		/// returned. If the specified Game Object is already a child of some 
		/// other Game Object, the child is detached from its current parent 
		/// and reattached to this Game Object. Since the child is passed as a 
		/// unique pointer, this Game Object instance will take ownership of 
		/// the pointer.
		/// </summary>
		/// <param name="object">
		/// The object to be parented to this Game Object. This should be moved
		/// to the Game Object using the <see cref="std::move"/> function.
		/// </param>
		/// <returns>
		/// The reference to the new child Game Object.
		/// </returns>
		GameObject& addChild(std::unique_ptr<GameObject> object);

		/// <summary>
		/// Adds the specified Game Component to this Game Object. If the
		/// specified Game Component is already attached to this Game Object,
		/// no further action is taken and the reference to the component is
		/// returned. If the specified Game Component is already attached to
		/// some other Game Object, the component is detached from its current
		/// parent and reattached to this Game Object. Since the component is
		/// passed as a unique pointer, this Game Object instance will take
		/// ownership of the pointer.
		/// 
		/// If the component has the DisallowMultiple property and there is
		/// already a Game Component of the same type attached to this, a
		/// GameComponentDisallowsMultipleException will be thrown.
		/// </summary>
		/// <param name="component">
		/// The component to be parented to this Game Object. This should be
		/// moved to the Game Component using the <see cref="std::move"/>
		/// function.
		/// </param>
		/// <exception cref="GameComponentDisallowsMultipleException">
		/// Thrown if a Game Component of the same type as the argument is
		/// already attached to this Game Component.
		/// </exception>
		Honeycomb::Component::GameComponent& addComponent(std::unique_ptr<
				Honeycomb::Component::GameComponent> component);

		/// <summary>
		/// Creates and adds a Game Component of the specified type to this
		/// Game Object. The Game Component is constructed using the arguments
		/// specified as parameters to this function.
		/// 
		/// If the component has the DisallowMultiple property and there is
		/// already a Game Component of the same type attached to this, a
		/// GameComponentDisallowsMultipleException will be thrown.
		/// </summary>
		/// <typeparam name="T">
		/// The type of Game Component to be created and attached to this
		/// Game Object.
		/// </typeparam>
		/// <typeparam name="...TArgs">
		/// The arguments types to be passed to the constructor of the Game
		/// Component.
		/// </typeparam>
		/// <param name="args">
		/// The arguments to be passed to the constructor of the Game 
		/// Component.
		/// </param>
		template<typename T, typename ...TArgs>
		Honeycomb::Component::GameComponent& addComponent(TArgs&&... args) {
			std::unique_ptr<Honeycomb::Component::GameComponent> component =
				std::make_unique<T>(std::forward<TArgs>(args)...);

			return this->addComponent(std::move(component));
		}

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
		/// Disables this Game Object. This has no effect if the Game Object is
		/// already disabled. Note that this only disables the self-activeness
		/// property of the Game Object.
		/// </summary>
		virtual void doDisable();

		/// <summary>
		/// Enables this Game Object. This has no effect if the Game Object is
		/// already enabled. Note that this only enables the self-activeness
		/// property of the Game Object.
		/// </summary>
		virtual void doEnable();

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

		/// <summary>
		/// Gets the component of this Game Object which has the specified Type
		/// and downcasts it to that type. If the game object has multiple game
		/// components of the specified type, the first component of that type
		/// is returned.
		/// </summary>
		/// <typeparam name="T">
		/// The type of the game component which is attached to this Game 
		/// Object.
		/// </typeparam>
		/// <returns>
		/// The reference to the game component found.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no component of the specified name.
		/// </exception>
		template<class T> 
		T& getComponent() {
			return const_cast<T&>(static_cast<const GameObject*>
				(this)->getComponent<T>());
		}

		/// <summary>
		/// Gets the component of this Game Object which has the specified Type
		/// and downcasts it to that type. If the game object has multiple game
		/// components of the specified type, the first component of that type
		/// is returned.
		/// </summary>
		/// <typeparam name="T">
		/// The type of the game component which is attached to this Game 
		/// Object.
		/// </typeparam>
		/// <returns>
		/// The constant reference to the game component found.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the game object has no component of the specified name.
		/// </exception>
		template<class T> 
		const T& getComponent() const {
			auto &componentsOfType = this->getComponentsOfType<T>();

			for (auto &comp : componentsOfType)
				return dynamic_cast<const T&>(*comp.get());

			throw GameEntityNotAttachedException(this, typeid(T).name());
		}

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

		/// <summary>
		/// Gets a boolean representing whether or not the Game Object is
		/// enabled. This is true only if this is self active and its parent
		/// is active.
		/// </summary>
		/// <returns>
		/// True if the object is active, false otherwise.
		/// </returns>
		virtual bool getIsActive() const;

		/// <summary>
		/// Gets a boolean representing whether or not the Game Object is self
		/// enabled. The self-activeness of the Game Object is independent of
		/// its parent's activeness.
		/// </summary>
		/// <returns>
		/// True if the object is self active, false otherwise.
		/// </returns>
		const bool& getIsSelfActive() const;

		/// <summary>
		/// Gets the name of this Game Object.
		/// </summary>
		/// <returns>
		/// The name of this Game Object.
		/// </returns>
		const std::string& getName() const;

		/// <summary>
		/// Returns the total number of components attached to this Game 
		/// Object. Since the Game Object structure uses a hash table to store
		/// its components, this should be used to find the number of 
		/// components, rather than checking the size of the vector returned by
		/// the <see cref="getComponents"/> method.
		/// </summary>
		/// <returns>
		/// The number of components attached to this Game Object.
		/// </returns>
		const unsigned int& getNumberOfComponents() const;

		/// <summary>
		/// Returns the total number of components of the specified type which
		/// are attached to this Game Object.
		/// </summary>
		/// <typeparam name="T">
		/// The type of the component.
		/// </typeparam>
		/// <returns>
		/// The number of components of type T attached to this Game Object.
		/// </returns>
		template<typename T>
		unsigned int getNumberOfComponents() const {
			return this->getComponentsOfType<T>().size();
		}

		/// <summary>
		/// Returns the number of components attached to this Game Object which
		/// have the same Component ID as the specified parameter.
		/// </summary>
		/// <param name="id">
		/// The Component ID of the Component Type.
		/// </param>
		/// <returns>
		/// The number of components attached to this Game Object which share
		/// the Component ID with the parameter.
		/// </returns>
		unsigned int getNumberOfComponents(const unsigned int &id) const;

		/// <summary>
		/// Returns the list of components attached to this Game Object which
		/// share the same Component ID as the specified parameter.
		/// </summary>
		/// <param name="id">
		/// The Component ID.
		/// </param>
		/// <returns>
		/// The list of components attached to this Game Object which have the
		/// same Component ID as the parameter, by means of a constant 
		/// reference.
		/// </returns>
		const std::vector<std::unique_ptr<
				Honeycomb::Component::GameComponent>>&getComponentsOfType(
				const unsigned int &id) const;

		/// <summary>
		/// Returns the list of components of the specified type which are
		/// attached to this Game Object.
		/// </summary>
		/// <typeparam name="T">
		/// The type of the component.
		/// </typeparam>
		/// <returns>
		/// The list of components of type T attached to this Game Object, by
		/// means of a constant reference.
		/// </returns>
		template<typename T>
		const std::vector<std::unique_ptr<
				Honeycomb::Component::GameComponent>>& getComponentsOfType() 
				const {
			// Get the list of components of the specified type and return it
			unsigned int id = Honeycomb::Component::GameComponent::
				getGameComponentTypeID<T>();
			return this->components.at(id);
		}

		/// <summary>
		/// Returns the parent of this Game Object, or null if this object has
		/// no parent.
		/// </summary>
		/// <returns>
		/// The pointer to the parent.
		/// </returns>
		GameObject* getParent();

		/// <summary>
		/// Returns the parent of this Game Object, or null if this object has
		/// no parent.
		/// </summary>
		/// <returns>
		/// The constant pointer to the parent.
		/// </returns>
		const GameObject* getParent() const;

		/// <summary>
		/// Returns the scene of this Game Object, or null if this object is
		/// not part of a scene.
		/// </summary>
		/// <returns>
		/// The pointer to the scene.
		/// </returns>
		Honeycomb::Scene::GameScene* getScene();

		/// <summary>
		/// Returns the scene of this Game Object, or null if this object is
		/// not part of a scene.
		/// </summary>
		/// <returns>
		/// The constant pointer to the scene.
		/// </returns>
		const Honeycomb::Scene::GameScene* getScene() const;

		/// <summary>
		/// Checks if the specified child is attached to this Game Object.
		/// </summary>
		/// <param name="child">
		/// The game object which is to be checked.
		/// </param>
		/// <returns>
		/// True if that specified child instance is attached to this Game
		/// Object.
		/// </returns>
		bool hasChild(const GameObject *child) const;

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
		/// Checks if the Game Object has a Game Component of the specified ID
		/// attached to it.
		/// </summary>
		/// <param name="id">
		/// The Game Component ID.
		/// </param>
		/// <returns>
		/// True if the Game Object has at least one component with the 
		/// specified ID attached to it, false otherwise.
		/// </returns>
		bool hasComponent(const unsigned int &id) const;

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
			return this->getNumberOfComponents<T>() > 0;
		}

		/// <summary>
		/// Checks if this Game Object has a parent.
		/// </summary>
		/// <returns>
		/// True if this Game Object has a parent, false otherwise.
		/// </returns>
		bool hasParent() const;

		/// <summary>
		/// Checks if this Game Object has a scene.
		/// </summary>
		/// <returns>
		/// True if the Game Object is attached to a scene, false otherwise.
		/// </returns>
		bool hasScene() const;

		/// <summary>
		/// This function is called after the Game Object is attached to a
		/// parent game object or scene, and should handle any attach events.
		/// </summary>
		virtual void onAttach();

		/// <summary>
		/// This function is called after the Game Object is detached from a
		/// parent game object or scene, and should handle any detach events.
		/// </summary>
		virtual void onDetach();

		/// <summary>
		/// This function is called after the Game Object is disabled, and
		/// should handle any (re)disabiling events for the object.
		/// </summary>
		virtual void onDisable();

		/// <summary>
		/// This function is called after the Game Object is enabled, and
		/// should handle any (re)enabling events for the object.
		/// </summary>
		virtual void onEnable();

		/// <summary>
		/// This function is called once per frame if the Game Object is 
		/// active, and should handle any input events for the object.
		/// This function is recursively called for each child.
		/// </summary>
		virtual void onInput();

		/// <summary>
		/// This function is called once per frame if the Game Object is 
		/// active, and should handle any rendering events for the object.
		/// This function is recursively called for each child.
		/// </summary>
		/// <param name="shader">
		/// The shader, using which, the Game Object is to be rendered.
		/// </param>
		virtual void onRender(Honeycomb::Shader::ShaderProgram &shader);

		/// <summary>
		/// Called when the Game Object first starts. This function should only
		/// be called once and should initialize all of the properties of this
		/// Object. This automatically enables the Game Object. This function 
		/// is recursively called for each child.
		/// </summary>
		virtual void onStart();

		/// <summary>
		/// Called when the Game Object ends. This function should only
		/// be called once and should de-initialize all of the properties of 
		/// this Object. This automatically disables the Game Object. This 
		///	function is recursively called for each child.
		/// </summary>
		virtual void onStop();

		/// <summary>
		/// This function is called once per frame if the Game Object is 
		/// active, and should handle any updating events for the object.
		/// This function is recursively called for each child.
		/// </summary>
		virtual void onUpdate();

		/// <summary>
		/// Removes the specified child from this Game Object and returns a
		/// unique pointer to it. If the specified Game Object is not attached
		/// to this Game Object, a GameEntityNotAttached exception will be
		/// thrown 
		/// </summary>
		/// <param name="object">
		/// The pointer to the child which is to be removed.
		/// </param>
		/// <returns>
		/// The unique pointer to the child after it has been removed from this
		/// Game Object.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the Game Object specified is not attached to this.
		/// </exception>
		std::unique_ptr<GameObject> removeChild(GameObject *object);

		/// <summary>
		/// Removes the specfied Game Component from this Game Object. If the
		/// specified Game Component is not attached to this Game Object, a
		/// GameEntityNotAttached exception will be thrown. Once the Game
		/// Component is detached, it's onDetach method will be called and the
		/// unique pointer containing it will be returned.
		/// </summary>
		/// <param name="component">
		/// The component to be detached from this Game Object.
		/// </param>
		/// <returns>
		/// The unique pointer to the newly independent game component.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the Game Component specified is not attached to this.
		/// </exception>
		std::unique_ptr<Honeycomb::Component::GameComponent> 
				removeComponent(Honeycomb::Component::GameComponent 
				*component);

		/// <summary>
		/// No assignment operator exists for the Game Object class.
		/// </summary>
		GameObject& operator=(const GameObject &object) = delete;
	protected:
		bool isSelfActive;                 // Is this object self active?
		std::string name;                  // Name of this Game Object
		
		GameObject *parent;                 // The parent of this Game Object
		Honeycomb::Scene::GameScene *scene; // Scene to which this belongs to

		// The children and components of this Game Object
		std::vector<std::unique_ptr<GameObject>> children;

		// The 2D array of all of the components of the Game Object. For each
		// Game Component, there exists an array, at the index of the Game
		// Component ID, which contains all of the Game Components of that
		// type which are attached to this Game Object.
		std::vector<std::vector<std::unique_ptr<
				Honeycomb::Component::GameComponent>>> components;
		unsigned int numComponents;

		/// <summary>
		/// Returns the list of components attached to this Game Object which
		/// share the same Component ID as the specified parameter.
		/// </summary>
		/// <param name="id">
		/// The Component ID.
		/// </param>
		/// <returns>
		/// The list of components attached to this Game Object which have the
		/// same Component ID as the parameter, by means of a reference.
		/// </returns>
		std::vector<std::unique_ptr<Honeycomb::Component::GameComponent>>&
				getComponentsOfType(const unsigned int &id);

		/// <summary>
		/// Returns the list of components of the specified type which are
		/// attached to this Game Object.
		/// </summary>
		/// <typeparam name="T">
		/// The type of the component.
		/// </typeparam>
		/// <returns>
		/// The list of components of type T attached to this Game Object, by
		/// means of a reference.
		/// </returns>
		template<typename T>
		std::vector<std::unique_ptr<Honeycomb::Component::GameComponent>>&
				getComponentsOfType() {
			// Get the list of components of the specified type and return it
			unsigned int id = Honeycomb::Component::GameComponent::
				getGameComponentTypeID<T>();

			return this->components.at(id);
		}

		/// <summary>
		/// Sets the scene of this Game Object and all of its children.
		/// </summary>
		/// <param name="scene">
		/// The new scene of the Game Object hierarchy.
		/// </param>
		void setScene(Honeycomb::Scene::GameScene *scene);
	};
} }

#endif
