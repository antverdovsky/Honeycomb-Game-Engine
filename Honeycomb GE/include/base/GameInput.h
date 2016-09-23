#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <vector>

namespace Honeycomb::Math { class Vector2f; }
class GLFWWindow;

namespace Honeycomb::Base {
	class GameInput {
	public:
		// Destroys the active Game Input instance.
		~GameInput();

		/// Function which handles the mouse movement event for the game.
		/// GLFWWindow *window : Ref. to the window for which to capture input.
		/// double x : The new x-position of the mouse.
		/// double y : The new y-position of the mouse.
		static void callbackCursorPosition(GLFWWindow *window, double x,
			double y);

		/// Function which handles the key press event for the game.
		/// GLFWWindow *window : Ref. to the window for which to capture input.
		/// int key : The key which was pressed / released.
		/// int scanCode : The scan code.
		/// int action : The action which was done to the key.
		/// int mods : Any additional modifiers for the key event.
		static void callbackKey(GLFWWindow *window, int key, int scanCode,
			int action, int mods);

		/// Function which handles the mnouse button press event for the game.
		/// GLFWWindow *window : Ref. to the window for which to capture input.
		/// int button : The mouse button which was pressed / released.
		/// int action : The action which was done to the key.
		/// int mods : Any additional modifiers for the mouse event.
		static void callbackMouseButton(GLFWWindow *window, int button, 
			int action, int mods);

		/// Clears the memory of the input arrays. This must be done each frame 
		/// otherwise the Input will consider the keys to remain down/up.
		void clear();

		/// Checks if the specified button is down or not.
		/// int button : The button to be checked.
		/// return : True if the button is currently down; False otherwise, or 
		///			 if the button is not within the range supported by the 
		///			 engine.
		bool getButtonDown(int button);

		/// Checks if the specified button is down or not.
		/// int button : The button to be checked.
		/// return : True if the button is currently down; False otherwise, or 
		///			 if the button is not within the range supported by the 
		///			 engine.
		bool getButtonReleased(int button);

		/// Gets the active game input instance possessed by this singleton.
		/// return : The active game input instance.
		static GameInput* getGameInput();

		/// Checks if the specified key is down or not.
		/// int key : The key to be checked.
		/// return : True if the key is currently down; False otherwise, or if
		///			 the key is not within the range supported by the engine.
		bool getKeyDown(int key);

		/// Checks if the specified key is up or not.
		/// int key : The key to be checked.
		/// return : True if the key is currently up; False otherwise, or if
		///			 the key is not within the range supported by the engine.
		bool getKeyReleased(int key);

		/// Gets the mouse position within the game window (in pixels).
		/// return : The mouse position 2D vector.
		Honeycomb::Math::Vector2f* getMousePosition();
	private:
		static GameInput *gameInput; // Instance stored by the singleton

		// The maximum key codes and mouse codes supported by this game engine.
		static const int MAX_NUM_KEYS = 512;
		static const int MAX_NUM_BUTTONS = 5;

		// These logical arrays store a boolean representing whether a 
		// specified key is up or down. A key which is considered to be down is
		// any key which is currently being pressed down. A key which is 
		// considered to be up is any key which was just released. A pressed 
		// key is a key which is being held down continously.
		bool keysDown[MAX_NUM_KEYS];
		bool keysReleased[MAX_NUM_KEYS];

		// Arrays which store the mouse position and whether each mouse button
		// is down or up. The down/up conditions are the same as for the keys.
		Honeycomb::Math::Vector2f *mousePos;
		bool buttonsDown[MAX_NUM_BUTTONS];
		bool buttonsReleased[MAX_NUM_BUTTONS];

		/// Constructs a new Game Input instance.
		GameInput();
	};
}

#endif