#pragma once
#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

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
		/// This must be a type which has inherited from the Game Component,
		/// and this is enforced by an assertion.
		/// </typeparam>
		/// <returns>
		/// The unsigned integer representing the Game Component ID of the 
		/// type.
		/// </returns>
		template <typename T>
		static GameComponentID getGameComponentTypeID() noexcept {
			GameComponent::assertIsBaseOf<T>();

			// Every time this function is called with a unique type parameter,
			// the type variable is instantiated to the current game component
			// ID value and then the game component ID value is incremented.
			// This allows for unique Component IDs for each different type.
			static GameComponentID type = 
					GameComponent::getGameComponentIDCounter(true);
			return type;
		}

		/// <summary>
		/// Performs a static assertion which checks if the specified type T
		/// is inherited from this Game Component class. The assertion fails if
		/// GameComponent is not the base class of type T.
		/// </summary>
		/// <typeparam name="T">
		/// The type of class which is to be checked.
		/// </typeparam>
		template <typename T>
		static void assertIsBaseOf() noexcept {
			static_assert(std::is_base_of<GameComponent, T>::value,
				"Type \"T\" must inherit from the GameComponent class.");
		}

		/// <summary>
		/// Creates a new, empty Game Component. The Game Component will not be
		/// attached to anything, nor will it be active or self active.
		/// </summary>
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

		/// <summary>
		/// Disables this Game Component. This has no effect if the Game 
		/// Component is already disabled.
		/// </summary>
		void doDisable();
		
		/// <summary>
		/// Enables this Game Component. This has no effect if the Game 
		/// Component is already enabled.
		/// </summary>
		void doEnable();

		/// <summary>
		/// Gets the pointer to the Game Object to which this Game Component is
		/// attached to. If the Game Component is not attached to anything,
		/// this will return a nullptr.
		/// </summary>
		/// <returns>
		/// The pointer to the Game Object this is attached to, or a nullptr if
		/// this is not attached to anything.
		/// </returns>
		Honeycomb::Object::GameObject* getAttached();

		/// <summary>
		/// Gets the pointer to the Game Object to which this Game Component is
		/// attached to. If the Game Component is not attached to anything,
		/// this will return a nullptr.
		/// </summary>
		/// <returns>
		/// The constant pointer to the Game Object this is attached to, or a 
		/// nullptr if this is not attached to anything.
		/// </returns>
		const Honeycomb::Object::GameObject* getAttached() const;

		/// <summary>
		/// Returns the Component ID integer representation of this Game
		/// Component. This must be overriden by any derived class to return 
		/// its own, unique Game Component ID.
		/// </summary>
		/// <returns>
		/// The integer representation of the Component ID of this Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept = 0;

		/// <summary>
		/// Gets a boolean representation of whether or not the Game Component
		/// is currently active. A component is to be considered active if it
		/// is both self active and its parent is active.
		/// </summary>
		/// <returns>
		/// True if the component is active.
		/// </returns>
		bool getIsActive() const;

		/// <summary>
		/// Gets a boolean representation of whether or not the Game Component
		/// is currently self active. A component's self activeness does not
		/// depent on the activeness of its parent.
		/// </summary>
		/// <returns>
		/// True if the component is self active.
		/// </returns>
		const bool& getIsSelfActive() const;

		/// <summary>
		/// Checks if this Game Component is attached to any Game Object.
		/// </summary>
		/// <returns>
		/// True if the Game Component is attached to something, false 
		/// otherwise.
		/// </returns>
		bool isAttached() const;

		/// <summary>
		/// Handles any events when this component is attached to a Game
		/// Object, if necessary. This is called immediately after the 
		/// component has been attached to something.
		/// </summary>
		virtual void onAttach();

		/// <summary>
		/// Handles any events when this component is detached from a Game
		/// Object, if necessary. This is called immediately before the
		/// component has been detached from something.
		/// </summary>
		virtual void onDetach();

		/// <summary>
		/// Handles any events when this component is disabled.
		/// </summary>
		virtual void onDisable();

		/// <summary>
		/// Handles any events when this component is enabled.
		/// </summary>
		virtual void onEnable();

		/// <summary>
		/// Handles any input events for this component, if necessary. This
		/// method should only perform its task when the object is active.
		/// </summary>
		virtual void onInput();
		
		/// <summary>
		/// Handles any rendering events for this component, if necessary.
		/// This method should only perform its task when the object is active.
		/// </summary>
		/// <param name="shader">
		/// The shader using which the object is to be rendered.
		/// </param>
		virtual void onRender(Honeycomb::Shader::ShaderProgram &shader);
		
		/// <summary>
		/// Handles any starting events for this component, if necessary. This
		/// method should only be called once and it should only initialize the
		/// component. The Game Component is enabled at the end of this
		/// method.
		/// </summary>
		virtual void onStart();

		/// <summary>
		/// Handles any stopping events for this component, if necessary. This
		/// method should only be called once and it should only deinitialize
		/// the component. The Game Component is disabled at the end of this
		/// method.
		/// </summary>
		virtual void onStop();

		/// <summary>
		/// Handles any update events for this component, if necessary. This
		/// method should only perform its task when the object is active.
		/// </summary>
		virtual void onUpdate();

		/// <summary>
		/// No assignment operator exists for the Game Component class.
		/// </summary>
		GameComponent& operator=(const GameComponent &object) = delete;
	protected:
		// The pointer to the Game Object to which this Component is attached.
		// If the Game Component is floating (not attached to anything), this
		// is a nullptr. If the Game Component is attached to something, its
		// lifetime is managed by the specified Game Object.
		Honeycomb::Object::GameObject* attached;

		bool isSelfActive;         // Is this game component itself active?
	private:
		/// <summary>
		/// Returns the static Game Component ID variable and increments it
		/// after returning.
		/// </summary>
		/// <param name="inc">
		/// Should the variable be incremented? False should be used if this
		/// method is called simply to check the value of the counter. True
		/// should be used if a new Game Component is being created.
		/// </param>
		/// <returns>
		/// The Game Component ID variable.
		/// </returns>
		static GameComponentID getGameComponentIDCounter(bool inc) noexcept;

		/// <summary>
		/// Internal helper function for cloning this Game Component. This must
		/// be overriden and implemented by any derived class.
		/// </summary>
		/// <returns>
		/// The pointer to the new Game Component clone.
		/// </returns>
		virtual GameComponent* cloneInternal() const = 0;

		/// <summary>
		/// Returns a boolean representation of whether or not this Game
		/// Component allows multiple instances of itself per Game Object. If
		/// not overriden, this will return true by default.
		/// </summary>
		/// <returns>
		/// False if only one instance of the component may be added to a 
		/// single Game Object. True if more than one instance of the component
		/// may be added to a single Game Object.
		/// </returns>
		virtual bool getProperty_AllowsMultiple() const noexcept;

		/// <summary>
		/// Returns a boolean representation of whether or not this Game
		/// Component is permanent (i.e. once added can the Game Component be
		/// detached?). If not overriden, this will return false by default.
		/// </summary>
		/// <returns>
		/// False if the Game Component can be removed once it is added to a
		/// Game Object. True if the Game Component cannot be removed once
		/// attached.
		/// </returns>
		virtual bool getProperty_Permanent() const noexcept;
	};

	/// <summary>
	/// Class which contains the exception to be thrown when the user attempts
	/// to add multiple instances of a component to the same object if that
	/// component has the allows multiple property turned off.
	/// </summary>
	class GameComponentDisallowsMultipleException : std::runtime_error {
	public:
		/// <summary>
		/// Creates a new Game Component Disallows Multiple Exception.
		/// </summary>
		/// <param name="object">
		/// The game object to which the game component was to be added to.
		/// </param>
		/// <param name="component">
		/// The component which the user tried to add to the object.
		/// </param>
		GameComponentDisallowsMultipleException(
			const Honeycomb::Object::GameObject *object,
			const GameComponent *component);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info containing the name
		/// of the Game Object for which the Game Component could not be added
		/// and the ID of the Game Component.
		/// </returns>
		virtual const char* what() const throw();
	private:
		const Honeycomb::Object::GameObject *object;
		const GameComponent *component;
	};

	/// <summary>
	/// Class which contains the exception to be thrown when the user attempts
	/// to remove a permanent Game Component.
	/// </summary>
	class GameComponentPermanentException : std::runtime_error {
	public:
		/// <summary>
		/// Creates a new Game Component Permanent Exception.
		/// </summary>
		/// <param name="object">
		/// The game object from which the game component was to be removed 
		/// from.
		/// </param>
		/// <param name="component">
		/// The component which the user tried to remove from the object.
		/// </param>
		GameComponentPermanentException(
			const Honeycomb::Object::GameObject *object,
			const GameComponent *component);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info containing the name
		/// of the Game Object for which the Game Component could not be 
		/// removed and the ID of the Game Component.
		/// </returns>
		virtual const char* what() const throw();
	private:
		const Honeycomb::Object::GameObject *object;
		const GameComponent *component;
	};
} }

#endif
