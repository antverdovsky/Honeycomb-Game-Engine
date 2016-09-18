#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\io\Input.h";
#include "..\..\include\base\Game.h";
#include "..\..\include\base\Main.h";
#include "..\..\include\base\Time.h";
#include "..\..\include\base\Window.h";


int main(int argc, char** argv) {
	std::cout << glfwGetVersionString() << std::endl;

	Main::start(); // Initialize the Game Engine components
	Main::run(); // Main Game Loop
	Main::stop(); // Destruct the Game Engine components
}

void Main::initializeGLEW(Window *window) {
	// Set the specified game window as the main game window.
	glfwMakeContextCurrent(window->getWindow());

	// Enable experimental GLEW and initialize it.
	glewExperimental = true;
	glewInit();
}

void Main::initializeGLFW() {
	glfwInit(); // Initialize GLFW

	glfwWindowHint(GLFW_DEPTH_BITS, 24); // Use 24 bits for 3D depths
	glfwWindowHint(GLFW_RED_BITS, 8); // Use 8 bits for RGBA values
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);

	glfwWindowHint(GLFW_SAMPLES, 4); // Enable 4x AA
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Forbid window resizing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR); // OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MINOR); // 3.2
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // New GL
}

void Main::initializeOpenGL() {
	glClearColor(1.0F, 0.0F, 0.0F, 0.0F); // Set clear color to zero

	if (!drawBackFaces) { // Should back faces be drawn?
		glFrontFace(GL_CW); // Every face drawn in clockwise is the front
		glCullFace(GL_BACK); // Set the back face as the face to not be drawn
		glEnable(GL_CULL_FACE); // Disable rendering unseen back faces
	}
	
	glEnable(GL_DEPTH_TEST); // Enable depth perception for drawing order
	glEnable(GL_FRAMEBUFFER_SRGB); // Gamma correction
}

void Main::render() {
	Main::window->render();
	Main::window->update();

	Main::game->render();
}

void Main::run() {
	const float msPerFrame = 1.0F / Main::FRAME_CAP * Time::SECOND;
	float lastTime = Time::getGameTime(); // Last time the game was rendered
	float deltaTime = 0;

	int framesRendered = 0;
	int timeSpentRenderingFrames = 0;

	do {
		// Get the game time at the start of the loop and calculate the delta
		// time between the last loop iteration and the current. Reset the
		// last render time to the current loop start time.
		float currentTime = Time::getGameTime();
		deltaTime += currentTime - lastTime;
		lastTime = currentTime;

		// If the time between this iteration and the last iteration exceeds
		// the minimum amount of time between frames -> Render & update.
		if (deltaTime >= msPerFrame) {
			Main::render(); // Render the game & the game window.
			Main::update(); // Update the game.

			// Time spent rendering frames is to increase by how long it took
			// to render this frame.
			timeSpentRenderingFrames += deltaTime;
			framesRendered++;

			// Record the time between frames in the Time namespace and rest
			// the delta time for future iterations of the loop.
			Time::setDeltaTime(deltaTime);
			deltaTime = 0;

			if (timeSpentRenderingFrames > Time::SECOND) {
#if _DEBUG // If debug mode -> Print out how many frames rendered in 1 sec
//				std::cout << "FPS: " << framesRendered << std::endl;
#endif

				timeSpentRenderingFrames = 0;
				framesRendered = 0;
			}
		}

		// Is game running flag is based on the window close requested event
		Main::isGameRunning = !Main::window->isCloseRequested();
	} while (Main::isGameRunning);
}

void Main::start() {
	if (Main::isGameRunning) return; // If already running -> No need to start!

	// Initialize the GLFW, the Window, GLEW and OpenGL.
	Main::initializeGLFW();
	Main::window = new Window(SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, TITLE);
	Main::initializeGLEW(Main::window);
	Main::initializeOpenGL();
	Main::game = new Game();

	// Initialize Input settings & link to the game window.
	glfwSetInputMode(Main::window->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(Main::window->getWindow(), (GLFWkeyfun)Input::keyCallback);
	glfwSetCursorPosCallback(Main::window->getWindow(), 
		(GLFWcursorposfun)Input::cursorPositionCallback);
	glfwSetMouseButtonCallback(Main::window->getWindow(), 
		(GLFWmousebuttonfun)Input::mouseButtonCallback);
}

void Main::stop() {
	if (!Main::isGameRunning) return; // If already stopped -> No need to stop!

	// Destroy the GLFW window and terminate GLFW library.
	glfwDestroyWindow(Main::window->getWindow());
	glfwTerminate();

	// Destroy Game components.
	delete Main::game;
	delete Main::window;
}

void Main::update() {
	Main::game->input();
	Main::game->update();
}