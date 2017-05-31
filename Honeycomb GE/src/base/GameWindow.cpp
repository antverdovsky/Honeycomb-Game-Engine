#include <GL/glew.h>

#include "../../include/base/GameWindow.h"

using Honeycomb::Conjuncture::Event;

namespace Honeycomb { namespace Base {
	GameWindow* GameWindow::getGameWindow() {
		static GameWindow *gameWindow = new GameWindow();
		return gameWindow; // Return the game window instance
	}

	GLFWwindow* GameWindow::getGLFWwindow() {
		return this->glfwWindow;
	}

	Event& GameWindow::getResizeEvent() {
		return this->resizeEvent;
	}

	const int& GameWindow::getWindowHeight() const {
		return this->height;
	}

	const std::string& GameWindow::getWindowTitle() const {
		return this->title;
	}

	const int& GameWindow::getWindowWidth() const {
		return this->width;
	}

	bool GameWindow::isCloseRequested() const {
		// If the GLFW reports that the user is trying to close the window,
		// then consider it as a "close requested" event.
		return glfwWindowShouldClose(this->glfwWindow) == 1;
	}

	void GameWindow::refresh() {
		glfwPollEvents();                    // Update window input
		glfwSwapBuffers(this->glfwWindow);   // Swap the two buffers
	}

	void GameWindow::setWindowSize(
			const unsigned int &w, const unsigned int &h) {
		// Write the new window width & height to the singleton instance
		this->width = w;
		this->height = h;

		// Tell OpenGL of the frame buffer size change
		glViewport(0, 0, this->width, this->height);

		this->resizeEvent.onEvent(); // Notify everyone that window has resized
	}

	void GameWindow::setWindowTitle(const std::string &title) {
		this->title = title;
		glfwSetWindowTitle(this->glfwWindow, title.c_str());
	}

	GameWindow::GameWindow() {
		// Fetch video mode and set default parameters
		videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		this->width = 1024;
		this->height = 768;
		this->title = "Game1";

		// Create the GLFW window using the parameters and store it.
		this->glfwWindow = glfwCreateWindow(width, height, title.c_str(), 
			nullptr, nullptr);
		glfwMakeContextCurrent(this->glfwWindow);

		// Set the resize callback function for resize events
		glfwSetFramebufferSizeCallback(this->glfwWindow, 
			(GLFWframebuffersizefun)callbackFrameBuffersize);
	}

	GameWindow::~GameWindow() {
		glfwDestroyWindow(this->getGLFWwindow());
	}

	void GameWindow::callbackFrameBuffersize(GLFWwindow *window, 
			unsigned int w, unsigned int h) {
		getGameWindow()->setWindowSize(w, h);
	}
} }
