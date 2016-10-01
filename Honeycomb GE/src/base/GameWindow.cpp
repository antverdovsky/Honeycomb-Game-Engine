#include <GL\glew.h>

#include "..\..\include\base\GameWindow.h"

using Honeycomb::Render::Camera;

namespace Honeycomb::Base {
	// Set the initial Game Window value to NULL, as it is not created until
	// the getGameWindow() creates it.
	GameWindow *GameWindow::gameWindow = NULL;

	GameWindow::~GameWindow() {
		glfwDestroyWindow(this->getGLFWwindow());
	}

	void GameWindow::callbackFrameBuffersize(GLFWwindow *window, int width,
		int height) {
		// Write the new window width & height to the singleton instance
		getGameWindow()->width = width;
		getGameWindow()->height = height;

		// Tell OpenGL of the frame buffer size change
		glViewport(0, 0, width, height);
	}

	void GameWindow::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Window
	}

	GameWindow* GameWindow::getGameWindow() {
		// If the game window instance does not yet exist -> Create a new one
		if (gameWindow == NULL)
			gameWindow = new GameWindow();
		
		return gameWindow; // Return the game window instance
	}

	GLFWwindow* GameWindow::getGLFWwindow() {
		return this->glfwWindow;
	}

	int GameWindow::getWindowHeight() {
		return this->height;
	}

	int GameWindow::getWindowWidth() {
		return this->width;
	}

	bool GameWindow::isCloseRequested() {
		// If the GLFW reports that the user is trying to close the window,
		// then consider it as a "close requested" event.
		return glfwWindowShouldClose(this->glfwWindow) == 1 ? true : false;
	}

	void GameWindow::refresh() {
		glfwPollEvents(); // Update window input
		glfwSwapBuffers(this->glfwWindow); // Swap the two buffers
	}

	GameWindow::GameWindow() {
		// Create the GLFW window using the parameters and store it.
		this->glfwWindow = glfwCreateWindow(width, height, title.c_str(), 
			nullptr, nullptr);

		glfwSetFramebufferSizeCallback(this->glfwWindow, 
			(GLFWframebuffersizefun)callbackFrameBuffersize);

		glfwWindowHint(GLFW_RESIZABLE, resizeable);
		glfwMakeContextCurrent(this->glfwWindow);
	}
}