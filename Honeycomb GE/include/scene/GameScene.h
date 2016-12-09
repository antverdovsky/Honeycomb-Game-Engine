#pragma once
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <string>

#include "..\component\GameComponent.h"
#include "..\object\GameObject.h"

namespace Honeycomb::Scene {
	/// Wrapper class for the Game Object class. The Scene is a special object 
	/// to which all game objects in the scene should be added to, in order for
	/// them to be updated, rendered, etc.
	class GameScene : public Honeycomb::Object::GameObject {
	public:
		/// Initializes an empty Game Scene with the name "GameScene".
		GameScene();

		/// Initializes an empty Game Scene with the specified name.
		/// const string &nam : The name of the game scene.
		GameScene(const std::string &nam);

		/// Clones this Game Scene into a new, dynamically allocated, 
		/// independent game scene. All game objects and game components will
		/// be duplicated into the new scene, as well.
		/// return : The pointer to the cloned Game Scene.
		GameScene* clone() const;

		/// Returns the pointer to the active game scene.
		/// return : The pointer to the active Game Scene.
		static GameScene* getActiveScene();

		/// Sets the active game scene for which rendering, updating, etc. will
		/// be handled.
		/// GameScene &scene : The reference to the new active game scene.
		static void setActiveScene(GameScene &scene);
	private:
		static GameScene *activeScene; // The active game scene
	};
}

#endif