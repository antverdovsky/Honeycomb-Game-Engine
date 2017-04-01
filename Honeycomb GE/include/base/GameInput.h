#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include <vector>

#include "../math/Vector2f.h"

struct GLFWWindow;

namespace Honeycomb::Base {
	class GameInput {
	public:
		/// All of the GLFW keyboard keys which are supported
		const static int KEY_CODE_SPACE = GLFW_KEY_SPACE;
		const static int KEY_CODE_APOSTROPHE = GLFW_KEY_APOSTROPHE;
		const static int KEY_CODE_COMMA = GLFW_KEY_COMMA;
		const static int KEY_CODE_MINUS = GLFW_KEY_MINUS;
		const static int KEY_CODE_PERIOD = GLFW_KEY_PERIOD;
		const static int KEY_CODE_SLASH = GLFW_KEY_SLASH;
		const static int KEY_CODE_0 = GLFW_KEY_0;
		const static int KEY_CODE_1 = GLFW_KEY_1;
		const static int KEY_CODE_2 = GLFW_KEY_2;
		const static int KEY_CODE_3 = GLFW_KEY_3;
		const static int KEY_CODE_4 = GLFW_KEY_4;
		const static int KEY_CODE_5 = GLFW_KEY_5;
		const static int KEY_CODE_6 = GLFW_KEY_6;
		const static int KEY_CODE_7 = GLFW_KEY_7;
		const static int KEY_CODE_8 = GLFW_KEY_8;
		const static int KEY_CODE_9 = GLFW_KEY_9;
		const static int KEY_CODE_SEMICOLON = GLFW_KEY_SEMICOLON;
		const static int KEY_CODE_EQUAL = GLFW_KEY_EQUAL;
		const static int KEY_CODE_A = GLFW_KEY_A;
		const static int KEY_CODE_B = GLFW_KEY_B;
		const static int KEY_CODE_C = GLFW_KEY_C;
		const static int KEY_CODE_D = GLFW_KEY_D;
		const static int KEY_CODE_E = GLFW_KEY_E;
		const static int KEY_CODE_F = GLFW_KEY_F;
		const static int KEY_CODE_G = GLFW_KEY_G;
		const static int KEY_CODE_H = GLFW_KEY_H;
		const static int KEY_CODE_I = GLFW_KEY_I;
		const static int KEY_CODE_J = GLFW_KEY_J;
		const static int KEY_CODE_K = GLFW_KEY_K;
		const static int KEY_CODE_L = GLFW_KEY_L;
		const static int KEY_CODE_M = GLFW_KEY_M;
		const static int KEY_CODE_N = GLFW_KEY_N;
		const static int KEY_CODE_O = GLFW_KEY_O;
		const static int KEY_CODE_P = GLFW_KEY_P;
		const static int KEY_CODE_Q = GLFW_KEY_Q;
		const static int KEY_CODE_R = GLFW_KEY_R;
		const static int KEY_CODE_S = GLFW_KEY_S;
		const static int KEY_CODE_T = GLFW_KEY_T;
		const static int KEY_CODE_U = GLFW_KEY_U;
		const static int KEY_CODE_V = GLFW_KEY_V;
		const static int KEY_CODE_W = GLFW_KEY_W;
		const static int KEY_CODE_X = GLFW_KEY_X;
		const static int KEY_CODE_Y = GLFW_KEY_Y;
		const static int KEY_CODE_Z = GLFW_KEY_Z;
		const static int KEY_CODE_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET;
		const static int KEY_CODE_BACKSLASH = GLFW_KEY_BACKSLASH;
		const static int KEY_CODE_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET;
		const static int KEY_CODE_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT;
		const static int KEY_CODE_ESCAPE = GLFW_KEY_ESCAPE;
		const static int KEY_CODE_ENTER = GLFW_KEY_ENTER;
		const static int KEY_CODE_TAB = GLFW_KEY_TAB;
		const static int KEY_CODE_BACKSPACE = GLFW_KEY_BACKSPACE;
		const static int KEY_CODE_INSERT = GLFW_KEY_INSERT;
		const static int KEY_CODE_DELETE = GLFW_KEY_DELETE;
		const static int KEY_CODE_RIGHT = GLFW_KEY_RIGHT;
		const static int KEY_CODE_LEFT = GLFW_KEY_LEFT;
		const static int KEY_CODE_DOWN = GLFW_KEY_DOWN;
		const static int KEY_CODE_UP = GLFW_KEY_UP;
		const static int KEY_CODE_PAGE_UP = GLFW_KEY_PAGE_UP;
		const static int KEY_CODE_PAGE_DOWN = GLFW_KEY_PAGE_DOWN;
		const static int KEY_CODE_HOME = GLFW_KEY_HOME;
		const static int KEY_CODE_END = GLFW_KEY_END;
		const static int KEY_CODE_CAPS_LOCK = GLFW_KEY_CAPS_LOCK;
		const static int KEY_CODE_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK;
		const static int KEY_CODE_NUM_LOCK = GLFW_KEY_NUM_LOCK;
		const static int KEY_CODE_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN;
		const static int KEY_CODE_PAUSE = GLFW_KEY_PAUSE;
		const static int KEY_CODE_F1 = GLFW_KEY_F1;
		const static int KEY_CODE_F2 = GLFW_KEY_F2;
		const static int KEY_CODE_F3 = GLFW_KEY_F3;
		const static int KEY_CODE_F4 = GLFW_KEY_F4;
		const static int KEY_CODE_F5 = GLFW_KEY_F5;
		const static int KEY_CODE_F6 = GLFW_KEY_F6;
		const static int KEY_CODE_F7 = GLFW_KEY_F7;
		const static int KEY_CODE_F8 = GLFW_KEY_F8;
		const static int KEY_CODE_F9 = GLFW_KEY_F9;
		const static int KEY_CODE_F10 = GLFW_KEY_F10;
		const static int KEY_CODE_F11 = GLFW_KEY_F11;
		const static int KEY_CODE_F12 = GLFW_KEY_F12;
		const static int KEY_CODE_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT;
		const static int KEY_CODE_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL;
		const static int KEY_CODE_LEFT_ALT = GLFW_KEY_LEFT_ALT;
		const static int KEY_CODE_LEFT_SUPER = GLFW_KEY_LEFT_SUPER;
		const static int KEY_CODE_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT;
		const static int KEY_CODE_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL;
		const static int KEY_CODE_RIGHT_ALT = GLFW_KEY_RIGHT_ALT;
		const static int KEY_CODE_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER;

		/// All of the GLFW mouse buttons which are supported
		const static int MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1;
		const static int MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2;
		const static int MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3;
		const static int MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4;
		const static int MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5;

		/// Clears the memory of the input arrays. This must be done each frame 
		/// otherwise the Input will consider the keys to remain down/up.
		void clear();

		/// Checks if the specified mouse button is down.
		/// const int &button : The code of the mouse button to be checked.
		/// return : True if the button is currently down; False otherwise, or 
		///			 if the button code is not within the range supported by 
		///			 the engine.
		bool getButtonDown(const int &button) const;

		/// Checks if the specified mouse button has just been released.
		/// const int &button : The code of the mouse button to be checked.
		/// return : True if the button has just been released this frame;
		///			 False otherwise, or if the button code is not within the 
		///			 range supported by the engine.
		bool getButtonReleased(const int &button) const;

		/// Gets the active game input instance possessed by this singleton.
		/// return : The singleton game input instance.
		static GameInput* getGameInput();

		/// Checks if the specified keyboard key is down.
		/// const int &key : The code of the key to be checked.
		/// return : True if the key is currently down; False otherwise, or 
		///			 if the key code is not within the range supported by the 
		///			 engine.
		bool getKeyDown(const int &key) const;

		/// Checks if the specified keyboard key has just been released.
		/// const int &key : The code of the key to be checked.
		/// return : True if the button has just been released this frame;
		///			 False otherwise, or if the button code is not within the 
		///			 range supported by the engine.
		bool getKeyReleased(const int &key) const;

		/// Gets the mouse position within the game window (in pixels).
		/// return : The mouse position 2D vector.
		const Honeycomb::Math::Vector2f& getMousePosition() const;
	private:
		static GameInput *gameInput; // Instance stored by the singleton

		// The maximum key codes and mouse codes supported by this game engine.
		static const int MAX_NUM_KEYS = 512;
		static const int MAX_NUM_BUTTONS = 5;

		// These logical arrays store a boolean representing whether a 
		// specified key is up or down. A key which is considered to be down is
		// any key which is currently being pressed down. A key which is 
		// considered to be up is any key which was just released.
		bool keysDown[MAX_NUM_KEYS];
		bool keysReleased[MAX_NUM_KEYS];

		// Arrays which store the mouse position and whether each mouse button
		// is down or up. The down/up conditions are the same as for the keys.
		Honeycomb::Math::Vector2f mousePos;
		bool buttonsDown[MAX_NUM_BUTTONS];
		bool buttonsReleased[MAX_NUM_BUTTONS];

		/// Constructs a new Game Input instance.
		GameInput();

		/// Destroys the Game Input instance.
		~GameInput();

		/// Function which handles the mouse movement event for the game.
		/// GLFWWindow *window : Ref. to the window for which to capture input.
		/// double x : The new x-position of the mouse.
		/// double y : The new y-position of the mouse.
		static void callbackCursorPosition(GLFWWindow *window, double x,
			double y);

		/// Function which handles the key press event for the game.
		/// GLFWWindow *window : The window which captured the input.
		/// int key : The key which was pressed / released.
		/// int scanCode : The scan code.
		/// int action : The action which was done to the key.
		/// int mods : Any additional modifiers for the key event.
		static void callbackKey(GLFWWindow *window, int key, int scanCode, 
			int action, int mods);

		/// Function which handles the mnouse button press event for the game.
		/// GLFWWindow *window : The window which captured the input.
		/// int button : The mouse button which was pressed / released.
		/// int action : The action which was done to the button.
		/// int mods : Any additional modifiers for the mouse event.
		static void callbackMouseButton(GLFWWindow *window, int button,
			int action, int mods);
	};
}

#endif