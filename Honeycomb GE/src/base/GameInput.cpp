#include <iostream>

#include "../../include/base/BaseMain.h"
#include "../../include/base/GameInput.h"
#include "../../include/base/GameWindow.h"

using Honeycomb::Math::Vector2f;

namespace Honeycomb { namespace Base {
	// GLFW Keyboard Key Codes
	const int GameInput::KEY_CODE_SPACE                       = GLFW_KEY_SPACE;
	const int GameInput::KEY_CODE_APOSTROPHE             = GLFW_KEY_APOSTROPHE;
	const int GameInput::KEY_CODE_COMMA                       = GLFW_KEY_COMMA;
	const int GameInput::KEY_CODE_MINUS                       = GLFW_KEY_MINUS;
	const int GameInput::KEY_CODE_PERIOD                     = GLFW_KEY_PERIOD;
	const int GameInput::KEY_CODE_SLASH                       = GLFW_KEY_SLASH;
	const int GameInput::KEY_CODE_0                               = GLFW_KEY_0;
	const int GameInput::KEY_CODE_1                               = GLFW_KEY_1;
	const int GameInput::KEY_CODE_2                               = GLFW_KEY_2;
	const int GameInput::KEY_CODE_3                               = GLFW_KEY_3;
	const int GameInput::KEY_CODE_4                               = GLFW_KEY_4;
	const int GameInput::KEY_CODE_5                               = GLFW_KEY_5;
	const int GameInput::KEY_CODE_6                               = GLFW_KEY_6;
	const int GameInput::KEY_CODE_7                               = GLFW_KEY_7;
	const int GameInput::KEY_CODE_8                               = GLFW_KEY_8;
	const int GameInput::KEY_CODE_9                               = GLFW_KEY_9;
	const int GameInput::KEY_CODE_SEMICOLON               = GLFW_KEY_SEMICOLON;
	const int GameInput::KEY_CODE_EQUAL                       = GLFW_KEY_EQUAL;
	const int GameInput::KEY_CODE_A                               = GLFW_KEY_A;
	const int GameInput::KEY_CODE_B                               = GLFW_KEY_B;
	const int GameInput::KEY_CODE_C                               = GLFW_KEY_C;
	const int GameInput::KEY_CODE_D                               = GLFW_KEY_D;
	const int GameInput::KEY_CODE_E                               = GLFW_KEY_E;
	const int GameInput::KEY_CODE_F                               = GLFW_KEY_F;
	const int GameInput::KEY_CODE_G                               = GLFW_KEY_G;
	const int GameInput::KEY_CODE_H                               = GLFW_KEY_H;
	const int GameInput::KEY_CODE_I                               = GLFW_KEY_I;
	const int GameInput::KEY_CODE_J                               = GLFW_KEY_J;
	const int GameInput::KEY_CODE_K                               = GLFW_KEY_K;
	const int GameInput::KEY_CODE_L                               = GLFW_KEY_L;
	const int GameInput::KEY_CODE_M                               = GLFW_KEY_M;
	const int GameInput::KEY_CODE_N                               = GLFW_KEY_N;
	const int GameInput::KEY_CODE_O                               = GLFW_KEY_O;
	const int GameInput::KEY_CODE_P                               = GLFW_KEY_P;
	const int GameInput::KEY_CODE_Q                               = GLFW_KEY_Q;
	const int GameInput::KEY_CODE_R                               = GLFW_KEY_R;
	const int GameInput::KEY_CODE_S                               = GLFW_KEY_S;
	const int GameInput::KEY_CODE_T                               = GLFW_KEY_T;
	const int GameInput::KEY_CODE_U                               = GLFW_KEY_U;
	const int GameInput::KEY_CODE_V                               = GLFW_KEY_V;
	const int GameInput::KEY_CODE_W                               = GLFW_KEY_W;
	const int GameInput::KEY_CODE_X                               = GLFW_KEY_X;
	const int GameInput::KEY_CODE_Y                               = GLFW_KEY_Y;
	const int GameInput::KEY_CODE_Z                               = GLFW_KEY_Z;
	const int GameInput::KEY_CODE_LEFT_BRACKET         = GLFW_KEY_LEFT_BRACKET;
	const int GameInput::KEY_CODE_BACKSLASH               = GLFW_KEY_BACKSLASH;
	const int GameInput::KEY_CODE_RIGHT_BRACKET       = GLFW_KEY_RIGHT_BRACKET;
	const int GameInput::KEY_CODE_GRAVE_ACCENT         = GLFW_KEY_GRAVE_ACCENT;
	const int GameInput::KEY_CODE_WORLD_1                   = GLFW_KEY_WORLD_1;
	const int GameInput::KEY_CODE_WORLD_2                   = GLFW_KEY_WORLD_2;
	const int GameInput::KEY_CODE_ESCAPE                     = GLFW_KEY_ESCAPE;
	const int GameInput::KEY_CODE_ENTER                       = GLFW_KEY_ENTER;
	const int GameInput::KEY_CODE_TAB                           = GLFW_KEY_TAB;
	const int GameInput::KEY_CODE_BACKSPACE               = GLFW_KEY_BACKSPACE;
	const int GameInput::KEY_CODE_INSERT                     = GLFW_KEY_INSERT;
	const int GameInput::KEY_CODE_DELETE                     = GLFW_KEY_DELETE;
	const int GameInput::KEY_CODE_RIGHT                       = GLFW_KEY_RIGHT;
	const int GameInput::KEY_CODE_LEFT                         = GLFW_KEY_LEFT;
	const int GameInput::KEY_CODE_DOWN                         = GLFW_KEY_DOWN;
	const int GameInput::KEY_CODE_UP                             = GLFW_KEY_UP;
	const int GameInput::KEY_CODE_PAGE_UP                   = GLFW_KEY_PAGE_UP;
	const int GameInput::KEY_CODE_PAGE_DOWN               = GLFW_KEY_PAGE_DOWN;
	const int GameInput::KEY_CODE_HOME                         = GLFW_KEY_HOME;
	const int GameInput::KEY_CODE_END                           = GLFW_KEY_END;
	const int GameInput::KEY_CODE_CAPS_LOCK               = GLFW_KEY_CAPS_LOCK;
	const int GameInput::KEY_CODE_SCROLL_LOCK           = GLFW_KEY_SCROLL_LOCK;
	const int GameInput::KEY_CODE_NUM_LOCK                 = GLFW_KEY_NUM_LOCK;
	const int GameInput::KEY_CODE_PRINT_SCREEN         = GLFW_KEY_PRINT_SCREEN;
	const int GameInput::KEY_CODE_PAUSE                       = GLFW_KEY_PAUSE;
	const int GameInput::KEY_CODE_F1                             = GLFW_KEY_F1;
	const int GameInput::KEY_CODE_F2                             = GLFW_KEY_F2;
	const int GameInput::KEY_CODE_F3                             = GLFW_KEY_F3;
	const int GameInput::KEY_CODE_F4                             = GLFW_KEY_F4;
	const int GameInput::KEY_CODE_F5                             = GLFW_KEY_F5;
	const int GameInput::KEY_CODE_F6                             = GLFW_KEY_F6;
	const int GameInput::KEY_CODE_F7                             = GLFW_KEY_F7;
	const int GameInput::KEY_CODE_F8                             = GLFW_KEY_F8;
	const int GameInput::KEY_CODE_F9                             = GLFW_KEY_F9;
	const int GameInput::KEY_CODE_F10                           = GLFW_KEY_F10;
	const int GameInput::KEY_CODE_F11                           = GLFW_KEY_F11;
	const int GameInput::KEY_CODE_F12                           = GLFW_KEY_F12;
	const int GameInput::KEY_CODE_F13                           = GLFW_KEY_F13;
	const int GameInput::KEY_CODE_F14                           = GLFW_KEY_F14;
	const int GameInput::KEY_CODE_F15                           = GLFW_KEY_F15;
	const int GameInput::KEY_CODE_F16                           = GLFW_KEY_F16;
	const int GameInput::KEY_CODE_F17                           = GLFW_KEY_F17;
	const int GameInput::KEY_CODE_F18                           = GLFW_KEY_F18;
	const int GameInput::KEY_CODE_F19                           = GLFW_KEY_F19;
	const int GameInput::KEY_CODE_F20                           = GLFW_KEY_F20;
	const int GameInput::KEY_CODE_F21                           = GLFW_KEY_F21;
	const int GameInput::KEY_CODE_F22                           = GLFW_KEY_F22;
	const int GameInput::KEY_CODE_F23                           = GLFW_KEY_F23;
	const int GameInput::KEY_CODE_F24                           = GLFW_KEY_F24;
	const int GameInput::KEY_CODE_F25                           = GLFW_KEY_F25;
	const int GameInput::KEY_CODE_KP_0                         = GLFW_KEY_KP_0;
	const int GameInput::KEY_CODE_KP_1                         = GLFW_KEY_KP_1;
	const int GameInput::KEY_CODE_KP_2                         = GLFW_KEY_KP_2;
	const int GameInput::KEY_CODE_KP_3                         = GLFW_KEY_KP_3;
	const int GameInput::KEY_CODE_KP_4                         = GLFW_KEY_KP_4;
	const int GameInput::KEY_CODE_KP_5                         = GLFW_KEY_KP_5;
	const int GameInput::KEY_CODE_KP_6                         = GLFW_KEY_KP_6;
	const int GameInput::KEY_CODE_KP_7                         = GLFW_KEY_KP_7;
	const int GameInput::KEY_CODE_KP_8                         = GLFW_KEY_KP_8;
	const int GameInput::KEY_CODE_KP_9                         = GLFW_KEY_KP_9;
	const int GameInput::KEY_CODE_KP_DECIMAL             = GLFW_KEY_KP_DECIMAL;
	const int GameInput::KEY_CODE_KP_DIVIDE               = GLFW_KEY_KP_DIVIDE;
	const int GameInput::KEY_CODE_KP_MULTIPLY           = GLFW_KEY_KP_MULTIPLY;
	const int GameInput::KEY_CODE_KP_SUBTRACT           = GLFW_KEY_KP_SUBTRACT;
	const int GameInput::KEY_CODE_KP_ADD                     = GLFW_KEY_KP_ADD;
	const int GameInput::KEY_CODE_KP_ENTER                 = GLFW_KEY_KP_ENTER;
	const int GameInput::KEY_CODE_KP_EQUAL                    = GLFW_KEY_EQUAL;
	const int GameInput::KEY_CODE_LEFT_SHIFT             = GLFW_KEY_LEFT_SHIFT;
	const int GameInput::KEY_CODE_LEFT_CONTROL         = GLFW_KEY_LEFT_CONTROL;
	const int GameInput::KEY_CODE_LEFT_ALT                 = GLFW_KEY_LEFT_ALT;
	const int GameInput::KEY_CODE_LEFT_SUPER             = GLFW_KEY_LEFT_SUPER;
	const int GameInput::KEY_CODE_RIGHT_SHIFT           = GLFW_KEY_RIGHT_SHIFT;
	const int GameInput::KEY_CODE_RIGHT_CONTROL       = GLFW_KEY_RIGHT_CONTROL;
	const int GameInput::KEY_CODE_RIGHT_ALT               = GLFW_KEY_RIGHT_ALT;
	const int GameInput::KEY_CODE_RIGHT_SUPER           = GLFW_KEY_RIGHT_SUPER;
	const int GameInput::KEY_CODE_MENU                         = GLFW_KEY_MENU;

	// GLFW Mouse Button Codes
	const int GameInput::MOUSE_BUTTON_1                  = GLFW_MOUSE_BUTTON_1;
	const int GameInput::MOUSE_BUTTON_2                  = GLFW_MOUSE_BUTTON_2;
	const int GameInput::MOUSE_BUTTON_3                  = GLFW_MOUSE_BUTTON_3;
	const int GameInput::MOUSE_BUTTON_4                  = GLFW_MOUSE_BUTTON_4;
	const int GameInput::MOUSE_BUTTON_5                  = GLFW_MOUSE_BUTTON_5;
	const int GameInput::MOUSE_BUTTON_6                  = GLFW_MOUSE_BUTTON_6;
	const int GameInput::MOUSE_BUTTON_7                  = GLFW_MOUSE_BUTTON_7;
	const int GameInput::MOUSE_BUTTON_8                  = GLFW_MOUSE_BUTTON_8;

	bool GameInput::getButtonDown(const int &button) const {
		if (button < 0 || button > MAX_NUM_BUTTONS) return false; // In range?

		return buttonsDown[button];
	}

	bool GameInput::getButtonReleased(const int &button) const {
		if (button < 0 || button > MAX_NUM_BUTTONS) return false; // In range?

		return buttonsReleased[button];
	}

	GameInput* GameInput::getGameInput() {
		static GameInput *gameInput = new GameInput();
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

	void GameInput::callbackCursorPosition(GLFWWindow *window, double x,
			double y) {
		GameInput::getGameInput()->mousePos.set((float)x, (float)y);
	}

	void GameInput::callbackKey(GLFWWindow *window, int key, int scanCode, 
			int action, int mods) {
		if (key < 0 || key > MAX_NUM_KEYS) return; // In range?

		switch (action) { // Switch the action which was done to the key
		case GLFW_RELEASE: // If just released -> Key is UP
			GameInput::getGameInput()->keysReleased[key] = true;
			GameInput::getGameInput()->keysDown[key] = false;
			break;
		case GLFW_PRESS: // If just pressed -> Key is DOWN
			GameInput::getGameInput()->keysDown[key] = true;
			break;
		}
	}

	void GameInput::callbackMouseButton(GLFWWindow *window, int button,
			int action, int mods) {
		if (button < 0 || button > MAX_NUM_BUTTONS) return; // In range?

		switch (action) { // 
		case GLFW_RELEASE: // If just released -> Button is up
			GameInput::getGameInput()->buttonsReleased[button] = true;
			GameInput::getGameInput()->buttonsDown[button] = false;
			break;
		case GLFW_PRESS: // If just pressed -> Button is down
			GameInput::getGameInput()->buttonsDown[button] = true;
			break;
		}
	}
} }
