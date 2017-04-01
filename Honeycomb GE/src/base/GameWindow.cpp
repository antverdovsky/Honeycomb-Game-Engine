#include <GL/glew.h>

#include "../../include/base/GameWindow.h"

using Honeycomb::Conjuncture::Event;

namespace Honeycomb::Base {
	// Set the initial Game Window value to NULL, as it is not created until
	// the getGameWindow() creates it.
	GameWindow *GameWindow::gameWindow = nullptr;

	void GameWindow::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Window
	}

	GameWindow* GameWindow::getGameWindow() {
		// If the game window instance does not yet exist -> Create a new one
		if (gameWindow == nullptr) gameWindow = new GameWindow();
		
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
		return glfwWindowShouldClose(this->glfwWindow) == 1 ? true : false;
	}

	void GameWindow::refresh() {
		glfwPollEvents(); // Update window input
		glfwSwapBuffers(this->glfwWindow); // Swap the two buffers
	}

	GameWindow::GameWindow() {
		videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_SAMPLES, this->MSAA_SAMPLES);
		glfwWindowHint(GLFW_RESIZABLE, this->RESIZABLE);
		glfwWindowHint(GLFW_DECORATED, !this->FULL_SCREEN);
		glfwWindowHint(GLFW_MAXIMIZED,  this->FULL_SCREEN);

		if (this->FULL_SCREEN) {
			this->width = videoMode->width;
			this->height = videoMode->height;
		}

		// Create the GLFW window using the parameters and store it.
		this->glfwWindow = glfwCreateWindow(width, height, title.c_str(), 
			nullptr, nullptr);
		glfwMakeContextCurrent(this->glfwWindow);

		glfwSetFramebufferSizeCallback(this->glfwWindow, 
			(GLFWframebuffersizefun)callbackFrameBuffersize);
	}

	GameWindow::~GameWindow() {
		glfwDestroyWindow(this->getGLFWwindow());
	}

	void GameWindow::callbackFrameBuffersize(GLFWwindow *window, 
			int w, int h) {
		getGameWindow()->setWindowSize(w, h);
	}

	void GameWindow::setWindowSize(const int &w, const int &h) {
		// Write the new window width & height to the singleton instance
		this->width = w;
		this->height = h;

		// Tell OpenGL of the frame buffer size change
		glViewport(0, 0, this->width, this->height);

		this->resizeEvent.onEvent(); // Notify everyone that window has resized
	}
}