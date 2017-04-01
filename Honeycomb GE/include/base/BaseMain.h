#pragma once
#ifndef BASE_MAIN_H
#define BASE_MAIN_H

#include "../../include/base/GameInput.h"
#include "../../include/base/GameTime.h"
#include "../../include/base/GameWindow.h"
#include "../../include/base/BaseGame.h"
#include "../../include/render/RenderingEngine.h"

namespace Honeycomb::Base {
	class BaseMain {
	public:
		/// Returns the singleton instance of the BaseMain structure.
		/// return : The reference to the singleton instance.
		static BaseMain& getBaseMain();

		/// Starts running the specified game using the Honeycomb Game Engine.
		/// BaseGame &game : The reference to the game which will be run.
		void runGame(BaseGame &game);
	private:
		static BaseMain *baseMain; // The singleton instance of Base Main

		BaseGame *game; // Pointer to the game that the engine is running
		Honeycomb::Render::RenderingEngine 
			*renderEngine; // Pointer to the rendering engine

		bool isGameRunning; // Is the main game loop running?

		const bool DRAW_BACK_FACES = false; // Draw back faces?
		const int FRAME_RATE_CAP = 999; // The maximum frames per second to be 
										// drawn (or zero for unlimited).

		/// Clears the game window, renders the game and updates the game 
		/// window (in that particular order).
		void render();

		/// The main game loop. Calls the appropriate render, update, and input
		/// functions each frame, and regulates how many frames exist in a 
		/// given second. After this function is complete, the stop function 
		/// should be called to clean up the game.
		void run();

		/// Starts the game by initializes the GLEW, Window and GLFW components
		/// (in that particular order). After all initializations are complete,
		/// the run function should be called to begin the game loop.
		void start();

		/// Stops the game by destroying the game components and terminating 
		/// the OpenGL libraries.
		void stop();

		/// Updates the game and the game window. The method should only be 
		/// called once per frame.
		void update();
	};
}

#endif