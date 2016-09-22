#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW\glfw3.h>

struct GLFWwindow;

namespace Honeycomb::Base {
	class GameWindow {
	public:
		/// Empty Destructor.
		~GameWindow();

		/// Clears the game window.
		void clear();

		/// Gets the current active game window instance. If no instance
		/// exists, a new instance will be created.
		/// return : The game window stored in this singleton.
		static GameWindow *getGameWindow();

		/// Gets the instance of the GLFW window stored in this Window 
		/// instance.
		/// return : The GLFW Window instance.
		GLFWwindow *getGLFWwindow();

		/// Checks if the window is requesting to be closed (the user has
		/// pressed the 'x' button on the window).
		/// return : True if the user has pressed 'x'; False otherwise.
		bool isCloseRequested();

		/// Refreshes the game window.
		void refresh();
	private:
		static GameWindow *gameWindow; // Instance stored by the singleton

		GLFWwindow *glfwWindow; // Stores the reference to the GLFW window.

		int width = 800; // The width of the window.
		int height = 600; // The height of the window.
		bool resizeable = true; // Allow & check for resizing?
		std::string title = "Honeycomb GE"; // Title of the Game Window

		/// Constructs a new GLFW window using the width, height, resizeable,
		/// and title parameters stored in this header file.
		GameWindow();
	};
}

#endif