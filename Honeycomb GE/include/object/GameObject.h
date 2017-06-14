#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

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

		/// Instantializes a Game Object with the specified name.
		/// const string &n : The name of this Game Object.
		GameObject(const std::string &n);

		/// Deletes this Game Object, its children and its components.
		virtual ~GameObject();

		/// Clones this Game Object into a new, dynamically allocated, Game
		/// Object.
		/// return : The cloned Game Object.
		GameObject* clone() const;

		/// Adds the specified object as a child to this game object, if it is
		/// not already a child of this game object.
		/// Object &o : The object to be parented to this game object.
		void addChild(GameObject &o);

		/// Adds the specified component to this game object, if it is not
		/// already a child of this game object.
		/// Component &c : The component to be parented to this game object.
		void addComponent(Honeycomb::Component::GameComponent &c);

		/// Deparents this object from whatever parent it may currently have
		/// so that its new parent becomes NULL.
		void deparent();

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

		/// Gets all the children game objects of this game object.
		/// return : The list containing the children game objects.
		std::vector<GameObject*>& getChildren();

		/// Gets all the children game objects of this game object.
		/// return : The constant list containing the children game objects.
		const std::vector<GameObject*>& getChildren() const;

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
			for (auto *comp : this->components) {
				if (dynamic_cast<Type*>(comp) != nullptr) {
					return dynamic_cast<const Type&>(*comp);
				}
			}

			throw GameEntityNotAttachedException(this, typeid(Type).name());
		}

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
				if (dynamic_cast<Type*>(comp) != nullptr &&
					comp->getName() == name) {
					return dynamic_cast<const Type&>(*comp);
				}
			}

			throw GameEntityNotAttachedException(this, typeid(Type).name);
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

		/// Returns the scene of this Game Object.
		/// return : The pointer to the Game Scene.
		Honeycomb::Scene::GameScene* getScene();

		/// Returns the scene of this Game Object.
		/// return : The constant pointer to the Game Scene.
		const Honeycomb::Scene::GameScene* getScene() const;

		/// Checks if this Game Object has the specified child.
		/// const GameObject &child : The game object which is to be checked.
		/// return : True if the specified game object is a child of this.
		///			 False otherwise.
		bool hasChild(const GameObject &child) const;

		/// Checks if this Game Object has the specified component.
		/// const GameComponent &comp : The component which is to be checked.
		/// return : True if the specified game component is a child of this.
		///			 False otherwise.
		bool hasComponent(const Honeycomb::Component::GameComponent &comp) 
				const;

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
	protected:
		bool isActive; // Is this object active?
		std::string name; // Name of this Game Object
		
		GameObject *parent; // The parent of this Game Object
		Honeycomb::Scene::GameScene *scene; // Scene to which this belongs to

		// The children and components of this Game Object
		std::vector<GameObject*> children;
		std::vector<Honeycomb::Component::GameComponent*> components;
	};
} }

#endif
