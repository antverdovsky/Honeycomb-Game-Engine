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
#if _DEBUG // If debug -> Print out the new x and y positions.
		//	std::cout << "MOUSE X: " << x << " | MOUSE Y: " << y << std::endl;
#endif
		getGameInput()->mousePos->set(x, y);
	}

	void GameInput::callbackKey(GLFWWindow *window, int key, int scanCode,
			int action, int mods) {
#if _DEBUG // If debug -> Print out the key pressed & the other specified info
		//	 std::cout << "KEY PRESSED: " << key << " | SC: " << scanCode <<
		//	 	" | ACTION: " << action << " | MODS: " << mods << std::endl;
#endif

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
#if _DEBUG // If debug -> Print out the button pressed
		//	std::cout << "BUTTON PRESSED: " << button << " | ACTION: " << action <<
		//		" | MODS: " << mods << std::endl;
#endif

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
		for (int i = 0; i < MAX_NUM_KEYS; i++)
			keysReleased[i] = false;

		for (int i = 0; i < MAX_NUM_BUTTONS; i++)
			buttonsReleased[i] = false;
	}

	GameInput::GameInput() {
		mousePos = new Vector2f();

		// Set up the GLFW Input
		glfwSetInputMode(Main::window->getGLFWwindow(), GLFW_STICKY_KEYS, 
			GL_TRUE);

		// Link all of the callback functions so OpenGL notifies us when
		// something is inputted into the window.
		glfwSetKeyCallback(Main::window->getGLFWwindow(),
			(GLFWkeyfun)callbackKey);
		glfwSetCursorPosCallback(Main::window->getGLFWwindow(),
			(GLFWcursorposfun)callbackCursorPosition);
		glfwSetMouseButtonCallback(Main::window->getGLFWwindow(),
			(GLFWmousebuttonfun)callbackMouseButton);
	}
}