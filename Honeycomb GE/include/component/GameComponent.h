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

		/// <summary>
		/// Creates a new, empty Game Component. The Game Component will not be
		/// attached to anything, nor will it be active or self active. The ID
		/// of the Component is initialized by this.
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
		/// Handles any events when this component is attached to a Game
		/// Object, if necessary.
		/// </summary>
		virtual void onAttach();

		/// <summary>
		/// Handles any events when this component is detached from a Game
		/// Object, if necessary.
		/// </summary>
		virtual void onDetach();

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
		/// component. The Game Component is not enabled by this method, use
		/// <see cref="onEnable"/> to enable the component.
		/// </summary>
		virtual void onStart();

		/// <summary>
		/// Handles any stopping events for this component, if necessary. This
		/// method should only be called once and it should only deinitialize
		/// the component. The Game Component is not disabled by this method,
		/// use <see cref="onDisable"/> to disable the component.
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

		int componentID;           // The Component ID of this Component
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
