#pragma once
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <string>
#include <vector>

#include "../component/GameComponent.h"
#include "../component/light/AmbientLight.h"
#include "../component/light/BaseLight.h"
#include "../component/light/DirectionalLight.h"
#include "../component/light/PointLight.h"
#include "../component/light/SpotLight.h"
#include "../object/GameObject.h"

namespace Honeycomb { namespace Scene {
	class GameScene : public Honeycomb::Object::GameObject {
		friend class Honeycomb::Component::Light::BaseLight;
	public:
		/// <summary>
		/// Returns the pointer to the active Game Scene. If no Game Scene is
		/// active, the returned pointer is a nullptr.
		/// </summary>
		/// <returns>
		/// The pointer to the Game Scene.
		/// </returns>
		static GameScene* getActiveScene();

		/// <summary>
		/// Initializes a new Game Scene with the name "Game Scene".
		/// </summary>
		GameScene();

		/// <summary>
		/// Initializes a new Game Scene with the specified name.
		/// </summary>
		/// <param name="name">
		/// The name of the scene.
		/// </param>
		GameScene(const std::string &name);

		/// <summary>
		/// Adds the specified Game Object as a child of this Game Scene. If 
		/// the specified Game Object is already a child of this Game Scene,
		/// no further action is taken and the reference to the child is 
		/// returned. If the specified Game Object is already a child of some 
		/// other Game Object, the child is detached from its current parent 
		/// and reattached to this Game Scene. Since the child is passed as a 
		/// unique pointer, this Game Scene instance will take ownership of 
		/// the pointer. This function automatically fetches any lights of the
		/// object and adds them to the scene's lights list.
		/// </summary>
		/// <param name="object">
		/// The object to be parented to this Game Scene. This should be moved
		/// to the Game Object using the <see cref="std::move"/> function.
		/// </param>
		/// <returns>
		/// The reference to the new child Game Object.
		/// </returns>
		Honeycomb::Object::GameObject& addChild(
			std::unique_ptr<Honeycomb::Object::GameObject> object) override;

		/// <summary>
		/// Clones this Game Scene into a new, independent Game Scene. The
		/// Game Scene will have all of the same properties, components and
		/// children of this Game Scene, but they will all be cloned and 
		/// independent of this Game Scene. The cloned Game Scene will not be
		/// parented to any Scene or Game Object, nor will it be active by
		/// default.
		/// </summary>
		/// <returns>
		/// The unique pointer to the Game Object clone instance.
		/// </returns>
		std::unique_ptr<GameScene> clone() const;

		/// <summary>
		/// Checks if this Game Scene is active.
		/// </summary>
		/// <returns>
		/// True if this is the active Game Scene, false otherwise.
		/// </returns>
		bool getIsActive() const;

		/// <summary>
		/// Returns a list of references to all of the lights of this Game
		/// Scene.
		/// </summary>
		/// <returns>
		/// The list of references to the lights.
		/// </returns>
		const std::vector<std::reference_wrapper<
				Honeycomb::Component::Light::BaseLight>>& getSceneLights()
				const;

		/// <summary>
		/// Disables this as the active Game Scene. After this method is called
		/// no active game scene will exist.
		/// </summary>
		void onDisable() override;

		/// <summary>
		/// Enables this as the active Game Scene. Any other currently enabled
		/// Game Scene is automatically disabled by this method.
		/// </summary>
		void onEnable() override;

		/// <summary>
		/// Removes the specified child from this Game Scene and returns a
		/// unique pointer to it. If the specified Game Object is not attached
		/// to this Game Scene, a GameEntityNotAttached exception will be
		/// thrown 
		/// </summary>
		/// <param name="object">
		/// The pointer to the child which is to be removed.
		/// </param>
		/// <returns>
		/// The unique pointer to the child after it has been removed from this
		/// Game Scene.
		/// </returns>
		/// <exception cref="GameEntityNotAttachedException">
		/// Thrown if the Game Object specified is not attached to this.
		/// </exception>
		std::unique_ptr<Honeycomb::Object::GameObject> removeChild(
				Honeycomb::Object::GameObject *object) override;
	private:
		static GameScene *activeScene; // The active game scene

		// List of all of the lights of this scene
		std::vector<
			std::reference_wrapper<Honeycomb::Component::Light::BaseLight>> 
			sceneLights;
	};
} }

#endif
