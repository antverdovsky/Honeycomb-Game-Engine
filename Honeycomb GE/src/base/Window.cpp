#include <GL\glew.h>

#include "..\..\include\base\Window.h"

Window::Window(int width, int height, std::string title) {
	// Create the GLFW window using the parameters and store it.
	this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, 
		nullptr);
}

Window::~Window() {
	delete this->window;
}

GLFWwindow* Window::getWindow() {
	return this->window;
}

bool Window::isCloseRequested() {
	// If the GLFW reports that the user is trying to close the window,
	// then consider it as a "close requested" event.
	return glfwWindowShouldClose(this->window);
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Window
}

void Window::refresh() {
	glfwPollEvents(); // Update window input
	glfwSwapBuffers(this->window); // Swap foreground and background buffers
}