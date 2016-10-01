#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\base\GameInput.h"
#include "..\..\include\base\GameTime.h"
#include "..\..\include\base\GameWindow.h"
#include "..\..\include\base\Game.h"
#include "..\..\include\base\Main.h"

int main(int argc, char** argv) {
	Honeycomb::Base::Main::start(); // Initialize the Game Engine components
	Honeycomb::Base::Main::run(); // Main Game Loop
	Honeycomb::Base::Main::stop(); // Destruct the Game Engine components

	return 0;
}

namespace Honeycomb::Base::Main {
	Game *game;
	bool isGameRunning = false; // Is the game loop running?
	bool drawBackFaces = true; // Draw back faces?

	void initializeOpenGL() {
		glClearColor(0.0F, 0.0F, 0.0F, 0.0F); // Set clear color to black
		
		if (!drawBackFaces) { // Should back faces be drawn?
			glFrontFace(GL_CW); // Every face drawn in clockwise is the front
			glCullFace(GL_BACK); // Do not draw the back face (CCW)
			glEnable(GL_CULL_FACE); // Disable rendering unseen back faces
		}

		glEnable(GL_DEPTH_TEST); // Enable depth perception for drawing order
		glEnable(GL_FRAMEBUFFER_SRGB); // Gamma correction
	}

	void render() {
		GameWindow::getGameWindow()->clear();
		game->render();
		GameWindow::getGameWindow()->refresh();
	}

	void run() {
		// The expected time that we should spend rendering each frame in order
		// to hit the desired FPS count.
		const float msPerFrame = 1.0F / FRAME_CAP * Time::SECOND;

		float lastTime = Time::getGameTime(); // Last time game was rendered
		float deltaTime = 0;

		// The number of frames rendered in some amount of time that we spent
		// rendering them.
		int framesRendered = 0;
		float timeSpentRenderingFrames = 0;

		do {
			// Get the game time at the start of the loop and calculate the 
			// delta time between the last loop iteration and the current. 
			// Reset the last render time to the current loop start time.
			float currentTime = Time::getGameTime();
			deltaTime += currentTime - lastTime;
			lastTime = currentTime;

			// If the time between this iteration and last iteration exceeds
			// the minimum amount of time between frames -> Render & update.
			if (deltaTime >= msPerFrame) {
				render(); // Render the game & the game window.
				update(); // Update the game.

				// Time spent rendering frames is to increase by how long it 
				// took to render this frame.
				timeSpentRenderingFrames += deltaTime;
				framesRendered++;

				// Record the time between frames in the Time namespace and
				// reset the delta time for future iterations of the loop.
				Time::setDeltaTime(deltaTime);
				deltaTime = 0;

				// If we have spent at least one second rendering the frames,
				// we have the current number of frames for the last second.
				// Reset the variables so the FPS can be calculated next frame.
				if (timeSpentRenderingFrames >= Time::SECOND) {
					std::cout << "FPS " << framesRendered << std::endl;
					
					timeSpentRenderingFrames = 0;
					framesRendered = 0;
				}
			}

			// "Is game running" is based on the window close requested event
			isGameRunning = !GameWindow::getGameWindow()->isCloseRequested();
		} while (isGameRunning);
	}

	void start() {
		if (isGameRunning) return; // If already running -> No need to start!

		// Initialize the GLFW, the Window, GLEW and OpenGL.
		glfwInit();
		GameWindow::getGameWindow(); // Initialize the Game Window (first time)
		glewExperimental = true; glewInit();
		initializeOpenGL();

		game = new Game();
	}

	void stop() {
		if (!isGameRunning) return; // If already stopped -> No need to stop!

		glfwTerminate(); // Terminate GLFW
	}

	void update() {
		game->input();
		game->update();
	}
}