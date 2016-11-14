#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW\glfw3.h>

#include "..\conjuncture\Event.h"

struct GLFWwindow;

namespace Honeycomb::Base {
	class GameWindow {
	public:
		/// Cleans up the Window, and destroys the GLFW window instance.
		~GameWindow();

		/// Callback function for when the size of the window is modified.
		/// GLFWwindow *window : The reference to the GLFW window instance.
		/// int width : The new width of the window.
		/// int height : The new height of the window.
		static void callbackFrameBuffersize(GLFWwindow *window, int width,
			int height);

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
		int getWindowHeight();

		/// Gets the width of this window (in pixels).
		/// return : The width.
		int getWindowWidth();

		/// Checks if the window is requesting to be closed (the user has
		/// pressed the 'x' button on the window).
		/// return : True if the user has pressed 'x'; False otherwise.
		bool isCloseRequested();

		/// Refreshes the game window.
		void refresh();

		/// Sets the size of the window.
		/// int w : The width of the window.
		/// int h : The height of the window.
		void setWindowSize(int w, int h);
	private:
		static GameWindow *gameWindow; // Instance stored by the singleton

		GLFWwindow *glfwWindow; // Stores the reference to the GLFW window
		Honeycomb::Conjuncture::Event resizeEvent; // Called on window resize

		int width = 1024; // The width of the window.
		int height = 768; // The height of the window.
		bool resizeable = false; // Allow & check for resizing?
		std::string title = "Honeycomb GE"; // Title of the Game Window

		/// Constructs a new GLFW window using the width, height, resizeable,
		/// and title parameters stored in this header file.
		GameWindow();
	};
}

#endif