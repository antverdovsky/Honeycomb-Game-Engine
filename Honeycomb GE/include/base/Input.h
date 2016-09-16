#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <vector>

class GLFWWindow;
class Vector2f;

namespace Input {
	// The maximum key codes and mouse codes supported by this game engine.
	const int MAX_NUM_KEYS = 512;
	const int MAX_NUM_BUTTONS = 5;

	// These logical arrays store a boolean representing whether a specified
	// key is up or down. A key which is considered to be down is any key which
	// is currently being pressed down. A key which is considered to be up is
	// any key which was just released. A pressed key is a key which is being
	// held down continously.
	extern bool keysDown[MAX_NUM_KEYS];
	extern bool keysReleased[MAX_NUM_KEYS];

	// Arrays which store the mouse position and whether each mouse button is
	// down or up. The down/up conditions are the same as for the keys.
	extern Vector2f mousePos;
	extern bool buttonsDown[MAX_NUM_BUTTONS];
	extern bool buttonsReleased[MAX_NUM_BUTTONS];

	/// Clears the memory of the input arrays. This must be done one per frame,
	/// otherwise the Input will consider the keys to remain down/up.
	void clear();

	/// Function which handles the mouse movement event for the game.
	/// GLFWWindow *window : Ref. to the window for which to capture input.
	/// double x : The new x-position of the mouse.
	/// double y : The new y-position of the mouse.
	void cursorPositionCallback(GLFWWindow *window, double x, double y);

	/// Checks if the specified button is down or not.
	/// int button : The button to be checked.
	/// return : True if the button is currently down; False otherwise, or if
	///			 the button is not within the range supported by the engine.
	bool getButtonDown(int button);

	/// Checks if the specified button is down or not.
	/// int button : The button to be checked.
	/// return : True if the button is currently down; False otherwise, or if
	///			 the button is not within the range supported by the engine.
	bool getButtonReleased(int button);

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
	Vector2f getMousePosition();

	/// Function which handles the key press event for the game.
	/// GLFWWindow *window : Ref. to the window for which to capture input.
	/// int key : The key which was pressed / released.
	/// int scanCode : The scan code.
	/// int action : The action which was done to the key.
	/// int mods : Any additional modifiers for the key event.
	void keyCallback(GLFWWindow *window, int key, int scanCode, int action,
		int mods);

	/// Function which handles the mnouse button press event for the game.
	/// GLFWWindow *window : Ref. to the window for which to capture input.
	/// int button : The mouse button which was pressed / released.
	/// int action : The action which was done to the key.
	/// int mods : Any additional modifiers for the mouse event.
	void mouseButtonCallback(GLFWWindow *window, int button, int action, 
		int mods);
}

#endif