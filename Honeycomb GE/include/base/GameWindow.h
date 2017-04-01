#pragma once
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <GLFW/glfw3.h>

#include <string>

#include "../conjuncture/Event.h"

namespace Honeycomb { namespace Base {
	class GameWindow {
	public:
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

		/// Returns the resize event for this window.
		/// return : The window resize event.
		Honeycomb::Conjuncture::Event& getResizeEvent();

		/// Gets the height of this window (in pixels).
		/// return : The height.
		const int& getWindowHeight() const;

		/// Gets the title of this window.
		/// return : The title.
		const std::string& getWindowTitle() const;

		/// Gets the width of this window (in pixels).
		/// return : The width.
		const int& getWindowWidth() const;

		/// Checks if the window is requesting to be closed (the user has
		/// pressed the 'X' button on the window).
		/// return : True if the user has pressed 'X'; False otherwise.
		bool isCloseRequested() const;

		/// Refreshes the game window.
		void refresh();
	private:
		static GameWindow *gameWindow; // Instance stored by the singleton

		const GLFWvidmode *videoMode; // GLFW Video Mode
		GLFWwindow *glfwWindow; // Stores the reference to the GLFW window
		Honeycomb::Conjuncture::Event resizeEvent; // Called on window resize
		
		const bool FULL_SCREEN = false; // Is the window full screen?
		const int MSAA_SAMPLES = 4; // Number of samples for MultiSampling AA
		const bool RESIZABLE = true; // Is the window resizable?

		int width = 1024; // The current width of the window.
		int height = 768; // The current height of the window.
		std::string title = "Honeycomb GE"; // Title of the Game Window

		/// Constructs a new GLFW window using the width, height, resizeable,
		/// and title parameters stored in this header file.
		GameWindow();

		/// Cleans up the Window, and destroys the GLFW window instance.
		~GameWindow();

		/// Callback function for when the size of the window is modified.
		/// GLFWwindow *window : The reference to the GLFW window instance.
		/// int w : The new width of the window.
		/// int h : The new height of the window.
		static void callbackFrameBuffersize(GLFWwindow *window, int w, int h);

		/// Sets the size of the window.
		/// const int &w : The width of the window.
		/// const int &h : The height of the window.
		void setWindowSize(const int &w, const int &h);
	};
} }

#endif