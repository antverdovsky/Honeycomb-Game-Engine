#pragma once
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <GLFW/glfw3.h>

#include <string>

#include "../conjuncture/Event.h"

namespace Honeycomb { namespace Base {
	class GameWindow {
	public:
		/// <summary>
		/// Gets the singleton Game Window instance.
		/// </summary>
		/// <returns>
		/// The pointer to the Game Window instance.
		/// </returns>
		static GameWindow *getGameWindow();

		/// <summary>
		/// Gets the GLFW Window instance of this Game Window.
		/// </summary>
		/// <returns>
		/// The constant pointer to the GLFW Window instance.
		/// </returns>
		GLFWwindow *getGLFWwindow();

		/// Returns the resize event for this window.
		/// return : The window resize event.
		/// <summary>
		/// Gets the resize event for this window. This event is automatically
		/// triggered any time the game window is resized.
		/// </summary>
		/// <returns>
		/// The reference to the resize event.
		/// </returns>
		Honeycomb::Conjuncture::Event& getResizeEvent();

		/// <summary>
		/// Gets the height of this window, in pixels.
		/// </summary>
		/// <returns>
		/// The height of the window.
		/// </returns>
		const int& getWindowHeight() const;

		/// <summary>
		/// Gets the title of this window, as a string.
		/// </summary>
		/// <returns>
		/// The title of the window.
		/// </returns>
		const std::string& getWindowTitle() const;

		/// <summary>
		/// Gets the width of this window, in pixels.
		/// </summary>
		/// <returns>
		/// The width of the window.
		/// </returns>
		const int& getWindowWidth() const;

		/// <summary>
		/// Checks if a window close request has been raised by the operating
		/// system.
		/// </summary>
		/// <returns>
		/// True if a window close request has been raised, false otherwise.
		/// </returns>
		bool isCloseRequested() const;

		/// <summary>
		/// Updates the window input and swaps the window buffers.
		/// </summary>
		void refresh();

		/// <summary>
		/// Sets the size of the window to the specified width and height
		/// values. The viewport is also changed and the resize event is
		/// automatically triggered.
		/// </summary>
		/// <param name="w">
		/// The new width of the game window, in pixels.
		/// </param>
		/// <param name="h">
		/// The new height of the game window, in pixels.
		/// </param>
		void setWindowSize(const unsigned int &w, const unsigned int &h);

		/// <summary>
		/// Sets the title of the window to the specified string.
		/// </summary>
		/// <param name="title">
		/// The new window title.
		/// </param>
		void setWindowTitle(const std::string &title);
	private:
		const GLFWvidmode *videoMode;              // GLFW Video Mode
		GLFWwindow *glfwWindow;                    // Reference to GLFW window
		Honeycomb::Conjuncture::Event resizeEvent; // Called on window resize
		
		int width;                          // The current width of the window
		int height;                         // The current height of the window
		std::string title;                  // Title of the Game Window

		/// <summary>
		/// Constructs a new Game Window with the default dimensions of 
		/// 1024x768 and a title of "Game1".
		/// </summary>
		GameWindow();

		/// <summary>
		/// Destroys this window from GLFW.
		/// </summary>
		~GameWindow();

		/// <summary>
		/// Callback function for setting the width and height dimensions of
		/// the specified window. Since this is a singleton class, the
		/// dimensions are always set only for the active window.
		/// </summary>
		/// <param name="window">
		/// The window whose dimensions are to be changed.
		/// </param>
		/// <param name="w">
		/// The new width of the game window, in pixels.
		/// </param>
		/// <param name="h">
		/// The new height of the game window, in pixels.
		/// </param>
		static void callbackFrameBuffersize(GLFWwindow *window, 
			unsigned int w, unsigned int h);
	};
} }

#endif