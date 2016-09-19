#pragma once
#ifndef MAIN_H
#define MAIN_H

class Game;
class Window;

namespace Main {
	// The game window width, height and title.
	const static int SCREEN_SIZE_WIDTH = 800;
	const static int SCREEN_SIZE_HEIGHT = 600;
	const static std::string TITLE = "Honeycomb";

	const static int FRAME_CAP = 60; // The FPS cap

	Window* window; // Reference to the Game Window component.
	Game* game; // Reference to the Game component.
	bool isGameRunning = false; // Boolean representing whether the game is running

	bool drawBackFaces = false; // Boolean whether or not to draw back faces

	/// Initializes the GLEW using the specified game window. The method should
	/// be called after GLFW has been initialized, and after a game window instance
	/// has been created.
	/// Window *window : The game window instance.
	void initializeGLEW(Window *window);

	/// Initializes the GLFW. The method should be called before GLEW or the game
	/// window components are initialized.
	void initializeGLFW();

	/// Initializes OpenGL settings for the game.
	void initializeOpenGL();

	/// Renders the game and the game window.
	void render();

	/// The main game loop.
	void run();

	/// Starts the game by initializes the GLEW, Window and GLFW components (in
	/// that particular order).
	void start();

	/// Stops the game by destroying the game components and terminating the OpenGL
	/// libraries.
	void stop();

	/// Updates the game and the game window.
	void update();
}

#endif