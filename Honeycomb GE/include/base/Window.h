#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW\glfw3.h>

class GLFWwindow;

class Window {
public:
	/// Constructs a new GLFW window using the specified parameters.
	/// int width : The width of the window (in pixels).
	/// int height : The height of the window (in pixels).
	/// string title : The title of the window.
	Window(int width, int height, std::string title);

	/// Empty Destructor.
	~Window();

	/// Clears the game window.
	void clear();

	/// Gets the instance of the GLFW window stored in this Window instance.
	/// return : The GLFW Window instance.
	GLFWwindow* getWindow();

	/// Checks if the window is requesting to be closed (the user has pressed
	/// the 'x' button on the window).
	/// return : True if the user has pressed 'x'; False otherwise.
	bool isCloseRequested();

	/// Refreshes the game window.
	void refresh();
private:
	GLFWwindow *window; // Stores the referencce to the GLFW window.
};

#endif