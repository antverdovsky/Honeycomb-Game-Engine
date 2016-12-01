#pragma once
#ifndef BASE_MAIN_H
#define BASE_MAIN_H

#include "..\..\include\base\GameInput.h"
#include "..\..\include\base\GameTime.h"
#include "..\..\include\base\GameWindow.h"
#include "..\..\include\base\BaseGame.h"

namespace Honeycomb::Base::BaseMain {
	extern const int FRAME_CAP; // The Frame Per Second cap
	extern const bool DRAW_BACK_FACES; // Draw back faces?
	
	extern bool isGameRunning; // Is the game loop running?

	extern BaseGame *game; // Reference to the current game

	/// Initializes OpenGL graphics settings for the game.
	void initializeOpenGL();

	/// Renders the game and the game window. The method should only be called
	/// once per frame.
	void render();

	/// The main game loop. Calls the appropriate render, update, and input
	/// functions each frame, and regulates how many frames exist in a given
	/// second. After this function is complete, the stop function should be
	/// called to clean up the game.
	void run();

	/// Starts the game by initializes the GLEW, Window and GLFW components (in
	/// that particular order). After all initializations are complete, the
	/// run function should be called to begin the game loop.
	/// BaseGame &g : The game which will be used to run the engine.
	void start(BaseGame &g);

	/// Stops the game by destroying the game components and terminating the 
	/// OpenGL libraries.
	void stop();

	/// Updates the game and the game window. The method should only be called 
	/// once per frame.
	void update();
}

#endif