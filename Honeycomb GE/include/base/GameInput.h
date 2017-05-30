#pragma once
#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include "../math/Vector2f.h"

struct GLFWWindow;

namespace Honeycomb { namespace Base {
	class GameInput {
	public:
		/// All of the GLFW keyboard keys which are supported
		const static int KEY_CODE_SPACE;
		const static int KEY_CODE_APOSTROPHE;
		const static int KEY_CODE_COMMA;
		const static int KEY_CODE_MINUS;
		const static int KEY_CODE_PERIOD;
		const static int KEY_CODE_SLASH;
		const static int KEY_CODE_0;
		const static int KEY_CODE_1;
		const static int KEY_CODE_2;
		const static int KEY_CODE_3;
		const static int KEY_CODE_4;
		const static int KEY_CODE_5;
		const static int KEY_CODE_6;
		const static int KEY_CODE_7;
		const static int KEY_CODE_8;
		const static int KEY_CODE_9;
		const static int KEY_CODE_SEMICOLON;
		const static int KEY_CODE_EQUAL;
		const static int KEY_CODE_A;
		const static int KEY_CODE_B;
		const static int KEY_CODE_C;
		const static int KEY_CODE_D;
		const static int KEY_CODE_E;
		const static int KEY_CODE_F;
		const static int KEY_CODE_G;
		const static int KEY_CODE_H;
		const static int KEY_CODE_I;
		const static int KEY_CODE_J;
		const static int KEY_CODE_K;
		const static int KEY_CODE_L;
		const static int KEY_CODE_M;
		const static int KEY_CODE_N;
		const static int KEY_CODE_O;
		const static int KEY_CODE_P;
		const static int KEY_CODE_Q;
		const static int KEY_CODE_R;
		const static int KEY_CODE_S;
		const static int KEY_CODE_T;
		const static int KEY_CODE_U;
		const static int KEY_CODE_V;
		const static int KEY_CODE_W;
		const static int KEY_CODE_X;
		const static int KEY_CODE_Y;
		const static int KEY_CODE_Z;
		const static int KEY_CODE_LEFT_BRACKET;
		const static int KEY_CODE_BACKSLASH;
		const static int KEY_CODE_RIGHT_BRACKET;
		const static int KEY_CODE_GRAVE_ACCENT;
		const static int KEY_CODE_WORLD_1;
		const static int KEY_CODE_WORLD_2;
		const static int KEY_CODE_ESCAPE;
		const static int KEY_CODE_ENTER;
		const static int KEY_CODE_TAB;
		const static int KEY_CODE_BACKSPACE;
		const static int KEY_CODE_INSERT;
		const static int KEY_CODE_DELETE;
		const static int KEY_CODE_RIGHT;
		const static int KEY_CODE_LEFT;
		const static int KEY_CODE_DOWN;
		const static int KEY_CODE_UP;
		const static int KEY_CODE_PAGE_UP;
		const static int KEY_CODE_PAGE_DOWN;
		const static int KEY_CODE_HOME;
		const static int KEY_CODE_END;
		const static int KEY_CODE_CAPS_LOCK;
		const static int KEY_CODE_SCROLL_LOCK;
		const static int KEY_CODE_NUM_LOCK;
		const static int KEY_CODE_PRINT_SCREEN;
		const static int KEY_CODE_PAUSE;
		const static int KEY_CODE_F1;
		const static int KEY_CODE_F2;
		const static int KEY_CODE_F3;
		const static int KEY_CODE_F4;
		const static int KEY_CODE_F5;
		const static int KEY_CODE_F6;
		const static int KEY_CODE_F7;
		const static int KEY_CODE_F8;
		const static int KEY_CODE_F9;
		const static int KEY_CODE_F10;
		const static int KEY_CODE_F11;
		const static int KEY_CODE_F12;
		const static int KEY_CODE_F13;
		const static int KEY_CODE_F14;
		const static int KEY_CODE_F15;
		const static int KEY_CODE_F16;
		const static int KEY_CODE_F17;
		const static int KEY_CODE_F18;
		const static int KEY_CODE_F19;
		const static int KEY_CODE_F20;
		const static int KEY_CODE_F21;
		const static int KEY_CODE_F22;
		const static int KEY_CODE_F23;
		const static int KEY_CODE_F24;
		const static int KEY_CODE_F25;
		const static int KEY_CODE_KP_0;
		const static int KEY_CODE_KP_1;
		const static int KEY_CODE_KP_2;
		const static int KEY_CODE_KP_3;
		const static int KEY_CODE_KP_4;
		const static int KEY_CODE_KP_5;
		const static int KEY_CODE_KP_6;
		const static int KEY_CODE_KP_7;
		const static int KEY_CODE_KP_8;
		const static int KEY_CODE_KP_9;
		const static int KEY_CODE_KP_DECIMAL;
		const static int KEY_CODE_KP_DIVIDE;
		const static int KEY_CODE_KP_MULTIPLY;
		const static int KEY_CODE_KP_SUBTRACT;
		const static int KEY_CODE_KP_ADD;
		const static int KEY_CODE_KP_ENTER;
		const static int KEY_CODE_KP_EQUAL;
		const static int KEY_CODE_LEFT_SHIFT;
		const static int KEY_CODE_LEFT_CONTROL;
		const static int KEY_CODE_LEFT_ALT;
		const static int KEY_CODE_LEFT_SUPER;
		const static int KEY_CODE_RIGHT_SHIFT;
		const static int KEY_CODE_RIGHT_CONTROL;
		const static int KEY_CODE_RIGHT_ALT;
		const static int KEY_CODE_RIGHT_SUPER;
		const static int KEY_CODE_MENU;


		/// All of the GLFW mouse buttons which are supported
		const static int MOUSE_BUTTON_1;
		const static int MOUSE_BUTTON_2;
		const static int MOUSE_BUTTON_3;
		const static int MOUSE_BUTTON_4;
		const static int MOUSE_BUTTON_5;
		const static int MOUSE_BUTTON_6;
		const static int MOUSE_BUTTON_7;
		const static int MOUSE_BUTTON_8;

		/// <summary>
		/// Clears the memory of the input arrays. This must be done each frame
		/// otherwise the Input will consider the keys to remain down/up.
		/// </summary>
		void clear();

		/// <summary>
		/// Checks if the specified mouse button is down this frame.
		/// </summary>
		/// <param name="button">
		/// The code of the mouse button to be checked.
		/// </param>
		/// <returns>
		/// True if the button is currently down; False otherwise, or if the
		/// button code is not within the range supported by the engine.
		/// </returns>
		bool getButtonDown(const int &button) const;

		/// <summary>
		/// Checks if the specified mouse button has just been released this
		/// frame.
		/// </summary>
		/// <param name="button">
		/// The code of the mouse button to be checked.
		/// </param>
		/// <returns>
		/// True if the button has just been released this frame; False 
		/// otherwise, or if the button code is not within the range supported 
		/// by the engine.
		/// </returns>
		bool getButtonReleased(const int &button) const;

		/// <summary>
		/// Gets the active game input instance possessed by this singleton.
		/// </summary>
		/// <returns>
		/// The singleton game input instance.
		/// </returns>
		static GameInput* getGameInput();

		/// <summary>
		/// Checks if the specified keyboard key is down this frame.
		/// </summary>
		/// <param name="key">
		/// The code of the keyboard key to be checked.
		/// </param>
		/// <returns>
		/// True if the key is currently down; False otherwise, or if the key 
		/// code is not within the range supported by the engine.
		/// </returns>
		bool getKeyDown(const int &key) const;

		/// <summary>
		/// Checks if the specified keyboard key has just been released this
		/// frame.
		/// </summary>
		/// <param name="key">
		/// The code of the keyboard key to be checked.
		/// </param>
		/// <returns>
		/// True if the button has just been released this frame; False 
		/// otherwise, or if the button code is not within the range supported
		/// by the engine.
		/// </returns>
		bool getKeyReleased(const int &key) const;

		/// <summary>
		/// Gets the mouse position within the game window (in pixels).
		/// </summary>
		/// <returns>
		/// The mouse position 2D vector.
		/// </returns>
		const Honeycomb::Math::Vector2f& getMousePosition() const;
	private:
		// The maximum key codes and mouse codes supported by this game engine
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

		/// <summary>
		/// Constructs a new Game Input instance.
		/// </summary>
		GameInput();

		/// <summary>
		/// Callback function which handles the mouse movement event for the 
		/// game.
		/// </summary>
		/// <param name="window">
		/// Pointer to the active GLFW Window.
		/// </param>
		/// <param name="x">
		/// The new x-position of the mouse.
		/// </param>
		/// <param name="y">
		/// The new y-position of the mouse.
		/// </param>
		static void callbackCursorPosition(GLFWWindow *window, double x,
			double y);

		/// <summary>
		/// Callback function which handles the key press event for the game.
		/// </summary>
		/// <param name="window">
		/// Pointer to the active GLFW Window.
		/// </param>
		/// <param name="key">
		/// The key which was pressed / released.
		/// </param>
		/// <param name="scanCode">
		/// The scan code.
		/// </param>
		/// <param name="action">
		/// The action which was done to the key.
		/// </param>
		/// <param name="mods">
		/// Any additional modifiers for the key event.
		/// </param>
		static void callbackKey(GLFWWindow *window, int key, int scanCode, 
			int action, int mods);

		/// <summary>
		/// Callback function which handles the mnouse button press event for 
		/// the game.
		/// </summary>
		/// <param name="window">
		/// Pointer to the active GLFW Window.
		/// </param>
		/// <param name="button">
		/// The mouse button which was pressed / released.
		/// </param>
		/// <param name="action">
		/// The action which was done to the button.
		/// </param>
		/// <param name="mods">
		/// Any additional modifiers for the mouse event.
		/// </param>
		static void callbackMouseButton(GLFWWindow *window, int button,
			int action, int mods);
	};
} }

#endif