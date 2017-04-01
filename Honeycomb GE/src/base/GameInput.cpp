#include <iostream>

#include "../../include/base/BaseMain.h"
#include "../../include/base/GameInput.h"
#include "../../include/base/GameWindow.h"

using Honeycomb::Math::Vector2f;

namespace Honeycomb::Base {
	GameInput *GameInput::gameInput = nullptr;

	bool GameInput::getButtonDown(const int &button) const {
		if (button < 0 || button > MAX_NUM_BUTTONS) return false; // In range?

		return buttonsDown[button];
	}

	bool GameInput::getButtonReleased(const int &button) const {
		if (button < 0 || button > MAX_NUM_BUTTONS) return false; // In range?

		return buttonsReleased[button];
	}

	GameInput* GameInput::getGameInput() {
		if (gameInput == nullptr) gameInput = new GameInput();

		return gameInput;
	}

	bool GameInput::getKeyDown(const int &key) const {
		if (key < 0 || key > MAX_NUM_KEYS) return false; // In range?

		return keysDown[key];
	}

	bool GameInput::getKeyReleased(const int &key) const {
		if (key < 0 || key > MAX_NUM_KEYS) return false; // In range?

		return keysReleased[key];
	}

	const Vector2f& GameInput::getMousePosition() const {
		return mousePos;
	}

	void GameInput::clear() {
		// Set the released state of all buttons and keys to false. (The down 
		// state is not modified as that is automatically cleared when the use 
		// lets go of the button).
		for (int i = 0; i < MAX_NUM_KEYS; i++)
			keysReleased[i] = false;
		for (int i = 0; i < MAX_NUM_BUTTONS; i++)
			buttonsReleased[i] = false;
	}

	GameInput::GameInput() {
		// Set up the GLFW Input
		glfwSetInputMode(GameWindow::getGameWindow()->getGLFWwindow(), 
			GLFW_STICKY_KEYS, GL_TRUE);

		// Link all of the callback functions so OpenGL notifies us when
		// something is inputted into the window.
		glfwSetKeyCallback(GameWindow::getGameWindow()->getGLFWwindow(),
			(GLFWkeyfun)GameInput::callbackKey);
		glfwSetCursorPosCallback(GameWindow::getGameWindow()->getGLFWwindow(),
			(GLFWcursorposfun)GameInput::callbackCursorPosition);
		glfwSetMouseButtonCallback(
			GameWindow::getGameWindow()->getGLFWwindow(),
			(GLFWmousebuttonfun)GameInput::callbackMouseButton);

		// By default, keys are not down and they have not just been released,
		// same for the mouse buttons.
		for (int i = 0; i < MAX_NUM_KEYS; i++) {
			this->keysDown[i] = false;
			this->keysReleased[i] = false;
		}
		for (int i = 0; i < MAX_NUM_BUTTONS; i++) {
			this->buttonsDown[i] = false;
			this->buttonsReleased[i] = false;
		}
	}

	GameInput::~GameInput() {

	}

	void GameInput::callbackCursorPosition(GLFWWindow *window, double x,
			double y) {
		GameInput::gameInput->mousePos.set((float)x, (float)y);
	}

	void GameInput::callbackKey(GLFWWindow *window, int key, int scanCode, 
			int action, int mods) {
		if (key < 0 || key > MAX_NUM_KEYS) return; // In range?

		switch (action) { // Switch the action which was done to the key
		case GLFW_RELEASE: // If just released -> Key is UP
			GameInput::gameInput->keysReleased[key] = true;
			GameInput::gameInput->keysDown[key] = false;
			break;
		case GLFW_PRESS: // If just pressed -> Key is DOWN
			GameInput::gameInput->keysDown[key] = true;
			break;
		}
	}

	void GameInput::callbackMouseButton(GLFWWindow *window, int button,
			int action, int mods) {
		if (button < 0 || button > MAX_NUM_BUTTONS) return; // In range?

		switch (action) { // 
		case GLFW_RELEASE: // If just released -> Button is up
			GameInput::gameInput->buttonsReleased[button] = true;
			GameInput::gameInput->buttonsDown[button] = false;
			break;
		case GLFW_PRESS: // If just pressed -> Button is down
			GameInput::gameInput->buttonsDown[button] = true;
			break;
		}
	}
}