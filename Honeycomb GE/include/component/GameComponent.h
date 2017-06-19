#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>

#include "../shader/ShaderProgram.h"

namespace Honeycomb { namespace Object { class GameObject; } }

namespace Honeycomb { namespace Component {
	typedef unsigned int GameComponentID;

	class GameComponent {
		friend class Honeycomb::Object::GameObject;
	public:
		/// <summary>
		/// Returns the Game Component Type ID of the specified type.
		/// </summary>
		/// <typeparam name="T">
		/// The type of the Game Component for which the type is to be fetched.
		/// This should be a type which has inherited from the Game Component,
		/// but this is not enforced.
		/// </typeparam>
		/// <returns>
		/// The unsigned integer representing the Game Component ID of the 
		/// type.
		/// </returns>
		template <typename T>
		static GameComponentID getGameComponentTypeID() noexcept {
			// Every time this function is called with a unique type parameter,
			// the type variable is instantiated to the current game component
			// ID value and then the game component ID value is incremented.
			// This allows for unique Component IDs for each different type.
			static GameComponentID type = GameComponent::getGameComponentID();
			return type;
		}

		/// Creates a Component instance with the "Component" name.
		GameComponent();
		
		/// <summary>
		/// No copy constructor exists for the Game Component class.
		/// </summary>
		GameComponent(const GameComponent &comp) = delete;

		/// <summary>
		/// Destroys this Game Component.
		/// </summary>
		virtual ~GameComponent();

		/// <summary>
		/// Clones this Game Component into a new, independent Game Component.
		/// The Game Component will not be attached to any Game Object, nor
		/// will it be started/active.
		/// </summary>
		/// <returns>
		/// The unique pointer to the Game Component clone.
		/// </returns>
		std::unique_ptr<GameComponent> clone() const;

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

		/// <summary>
		/// No assignment operator exists for the Game Component class.
		/// </summary>
		GameComponent& operator=(const GameComponent &object) = delete;
	protected:
		// The pointer to the Game Object to which this Component is attached.
		// If the Game Component is floating (not attached to anything), this
		// is a nullptr.
		Honeycomb::Object::GameObject* attached;

		bool isActive;             // Is this game component active in general?
		bool isSelfActive;         // Is this game component itself active?
	private:
		/// <summary>
		/// Returns the static Game Component ID variable and increments it
		/// after returning.
		/// </summary>
		/// <returns>
		/// The Game Component ID variable.
		/// </returns>
		static GameComponentID getGameComponentID() noexcept;

		/// <summary>
		/// Internal helper function for cloning this Game Component.
		/// </summary>
		/// <returns>
		/// The pointer to the new Game Component clone.
		/// </returns>
		virtual GameComponent* cloneInternal() const;
	};
} }

#endif
