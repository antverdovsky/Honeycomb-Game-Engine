#include <iostream>

#include <GLFW\glfw3.h>

#include "..\..\include\io\Input.h";
#include "..\..\include\math\Vector2f.h";

bool Input::keysDown[MAX_NUM_KEYS];
bool Input::keysReleased[MAX_NUM_KEYS];

Vector2f Input::mousePos(0, 0);
bool Input::buttonsDown[MAX_NUM_BUTTONS];
bool Input::buttonsReleased[MAX_NUM_BUTTONS];

void Input::cursorPositionCallback(GLFWWindow *window, double x, double y) {
#if _DEBUG // If debug -> Print out the new x and y positions.
//	std::cout << "MOUSE X: " << x << " | MOUSE Y: " << y << std::endl;
#endif
	mousePos.set(x, y);
}

bool Input::getButtonDown(int button) {
	if (button < 0 || button > MAX_NUM_BUTTONS) return false; // Verify range

	return buttonsDown[button];
}

bool Input::getButtonReleased(int button) {
	if (button < 0 || button > MAX_NUM_BUTTONS) return false;

	return buttonsReleased[button];
}

bool Input::getKeyDown(int key) {
	if (key < 0 || key > MAX_NUM_KEYS) return false;

	return keysDown[key];
}

bool Input::getKeyReleased(int key) {
	if (key < 0 || key > MAX_NUM_KEYS) return false;

	return keysReleased[key];
}

Vector2f Input::getMousePosition() {
	return mousePos;
}

void Input::clear() {
	// Set the released state of all buttons and keys to false. (The down state
	// is not modified as that is automatically cleared when the use lets go of
	// the button).
	for (int i = 0; i < MAX_NUM_KEYS; i++)
		keysReleased[i] = false;

	for (int i = 0; i < MAX_NUM_BUTTONS; i++)
		buttonsReleased[i] = false;
}

void Input::keyCallback(GLFWWindow * window, int key, int scanCode, int action,
	int mods) {
#if _DEBUG // If debug -> Print out the key pressed & the other specified info
//	 std::cout << "KEY PRESSED: " << key << " | SC: " << scanCode <<
//	 	" | ACTION: " << action << " | MODS: " << mods << std::endl;
#endif

	if (key < 0 || key > MAX_NUM_KEYS) return; // Verify key is in range

	switch (action) { // Switch the action which was done to the key
	case GLFW_RELEASE: // If just released -> Key is UP
		keysReleased[key] = true;
		keysDown[key] = false;
		break;
	case GLFW_PRESS: // If just pressed -> Key is DOWN
		keysDown[key] = true;
		break;
	}
}

void Input::mouseButtonCallback(GLFWWindow *window, int button, int action,
	int mods) {
#if _DEBUG // If debug -> Print out the button pressed
//	std::cout << "BUTTON PRESSED: " << button << " | ACTION: " << action <<
//		" | MODS: " << mods << std::endl;
#endif

	if (button < 0 || button > MAX_NUM_BUTTONS) return; // Verify in range

	switch (action) { // 
	case GLFW_RELEASE: // If just released -> Button is up
		buttonsReleased[button] = true;
		buttonsDown[button] = false;
		break;
	case GLFW_PRESS: // If just pressed -> Button is down
		buttonsDown[button] = true;
		break;
	}
}