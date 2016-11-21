#pragma once
#ifndef BASE_MAIN_H
#define BASE_MAIN_H

#include "..\..\include\base\GameInput.h"
#include "..\..\include\base\GameTime.h"
#include "..\..\include\base\GameWindow.h"
#include "..\..\include\base\BaseGame.h"

namespace Honeycomb::Base::BaseMain {
	const static int FRAME_CAP = 999; // The FPS cap

	extern bool isGameRunning; // Is the game loop running?
	extern bool drawBackFaces; // Draw back faces?
	extern BaseGame *game; // Reference to the current game object

	/// Initializes OpenGL settings for the game.
	void initializeOpenGL();

	/// Renders the game and the game window.
	void render();

	/// The main game loop.
	void run();

	/// Starts the game by initializes the GLEW, Window and GLFW components (in
	/// that particular order).
	/// BaseGame *g : The game which will be used to run the engine.
	void start(BaseGame *g);

	/// Stops the game by destroying the game components and terminating the 
	/// OpenGL libraries.
	void stop();

	/// Updates the game and the game window.
	void update();
}

#endif