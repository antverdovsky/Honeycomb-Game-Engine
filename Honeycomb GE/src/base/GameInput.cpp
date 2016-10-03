#include <iostream>

#include <GLFW\glfw3.h>

#include "..\..\include\base\GameInput.h"
#include "..\..\include\base\GameWindow.h"
#include "..\..\include\base\Main.h"
#include "..\..\include\math\Vector2f.h"

using Honeycomb::Math::Vector2f;

namespace Honeycomb::Base {
	GameInput *GameInput::gameInput = NULL;
	
	GameInput::~GameInput() {
		delete mousePos;
		delete gameInput;
	}

	void GameInput::callbackCursorPosition(GLFWWindow *window, double x, 
			double y) {
		getGameInput()->mousePos->set((float)x, (float)y);
	}

	void GameInput::callbackKey(GLFWWindow *window, int key, int scanCode,
			int action, int mods) {
		if (key < 0 || key > MAX_NUM_KEYS) return; // Verify key is in range

		switch (action) { // Switch the action which was done to the key
		case GLFW_RELEASE: // If just released -> Key is UP
			getGameInput()->keysReleased[key] = true;
			getGameInput()->keysDown[key] = false;
			break;
		case GLFW_PRESS: // If just pressed -> Key is DOWN
			getGameInput()->keysDown[key] = true;
			break;
		}
	}

	void GameInput::callbackMouseButton(GLFWWindow *window, int button,
			int action, int mods) {
		if (button < 0 || button > MAX_NUM_BUTTONS) return; // Verify in range

		switch (action) { // 
		case GLFW_RELEASE: // If just released -> Button is up
			getGameInput()->buttonsReleased[button] = true;
			getGameInput()->buttonsDown[button] = false;
			break;
		case GLFW_PRESS: // If just pressed -> Button is down
			getGameInput()->buttonsDown[button] = true;
			break;
		}
	}

	bool GameInput::getButtonDown(int button) {
		if (button < 0 || button > MAX_NUM_BUTTONS) return false; // In range?

		return buttonsDown[button];
	}

	bool GameInput::getButtonReleased(int button) {
		if (button < 0 || button > MAX_NUM_BUTTONS) return false;

		return buttonsReleased[button];
	}

	GameInput* GameInput::getGameInput() {
		if (gameInput == NULL)
			gameInput = new GameInput();

		return gameInput;
	}

	bool GameInput::getKeyDown(int key) {
		if (key < 0 || key > MAX_NUM_KEYS) return false;

		return keysDown[key];
	}

	bool GameInput::getKeyReleased(int key) {
		if (key < 0 || key > MAX_NUM_KEYS) return false;

		return keysReleased[key];
	}

	Vector2f* GameInput::getMousePosition() {
		return mousePos;
	}

	void GameInput::clear() {
		// Set the released state of all buttons and keys to false. (The down 
		// state is not modified as that is automatically cleared when the use 
		// lets go of the button).
		for (int i = 0; i < MAX_NUM_KEYS; i++) {
			keysReleased[i] = false;
		}

		for (int i = 0; i < MAX_NUM_BUTTONS; i++) {
			buttonsReleased[i] = false;
		}
	}

	GameInput::GameInput() {
		mousePos = new Vector2f();

		// Set up the GLFW Input
		glfwSetInputMode(GameWindow::getGameWindow()->getGLFWwindow(), 
			GLFW_STICKY_KEYS, GL_TRUE);

		// Link all of the callback functions so OpenGL notifies us when
		// something is inputted into the window.
		glfwSetKeyCallback(GameWindow::getGameWindow()->getGLFWwindow(),
			(GLFWkeyfun)callbackKey);
		glfwSetCursorPosCallback(GameWindow::getGameWindow()->getGLFWwindow(),
			(GLFWcursorposfun)callbackCursorPosition);
		glfwSetMouseButtonCallback(
			GameWindow::getGameWindow()->getGLFWwindow(),
			(GLFWmousebuttonfun)callbackMouseButton);

		for (int i = 0; i < MAX_NUM_KEYS; i++) {
			this->keysDown[i] = false;
			this->keysReleased[i] = false;
		}

		for (int i = 0; i < MAX_NUM_BUTTONS; i++) {
			this->buttonsDown[i] = false;
			this->buttonsReleased[i] = false;
		}
	}
}