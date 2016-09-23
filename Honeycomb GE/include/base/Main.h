#pragma once
#ifndef MAIN_H
#define MAIN_H

class Game;
class GameInput;
class GameWindow;

namespace Honeycomb::Base::Main {
	const static int FRAME_CAP = 60; // The FPS cap

	extern GameWindow *window; // Reference to the Game Window component.
	extern GameInput *input; // Reference to the Game Input component.
	extern Game *game; // Reference to the Game component.
	
	extern bool isGameRunning; // Is the game loop running?
	extern bool drawBackFaces; // Draw back faces?

	/// Initializes OpenGL settings for the game.
	void initializeOpenGL();

	/// Renders the game and the game window.
	void render();

	/// The main game loop.
	void run();

	/// Starts the game by initializes the GLEW, Window and GLFW components (in
	/// that particular order).
	void start();

	/// Stops the game by destroying the game components and terminating the 
	/// OpenGL libraries.
	void stop();

	/// Updates the game and the game window.
	void update();
}

#endif