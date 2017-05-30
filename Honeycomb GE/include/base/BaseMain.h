#pragma once
#ifndef BASE_MAIN_H
#define BASE_MAIN_H

namespace Honeycomb { namespace Base { class BaseGame; } }
namespace Honeycomb { namespace Render { class RenderingEngine; } }

namespace Honeycomb { namespace Base {
	class BaseMain {
	public:
		/// <summary>
		/// Returns the singleton instance of the BaseMain structure.
		/// </summary>
		/// <returns>
		/// The reference to the singleton instance.
		/// </returns>
		static BaseMain& getBaseMain();

		/// <summary>
		/// Runs the specified game using the Honeycomb Game Engine.
		/// </summary>
		/// <param name="game">
		/// The game to be run using the game engine.
		/// </param>
		void runGame(BaseGame &game);
	private:
		BaseGame *game;
		Honeycomb::Render::RenderingEngine *renderingEngine;

		bool isGameRunning;                 // Is the main game loop running?
		const bool DRAW_BACK_FACES = false; // Draw back faces?

		const int FRAME_RATE_CAP = 999;     // The maximum frames per second to
                                            // be drawn (or zero for unlimited)

		/// <summary>
		/// Conducts a single render pass for the game which is being run. The
		/// game window is cleared and the game being run is rendered to the
		/// window.
		/// </summary>
		void render();

		/// <summary>
		/// The main game loop. Calls the appropriate render, update, and input
		/// functions each frame, and regulates how many frames exist in a 
		/// given second. After this function is complete, the stop function 
		/// is called to clean up the game.
		/// </summary>
		void run();

		/// <summary>
		/// Starts the game by initializing the GLEW, Window and GLFW 
		/// components (in that particular order). After all initializations 
		/// are complete, the run function will be called to begin the game 
		/// loop.
		/// </summary>
		void start();

		/// <summary>
		/// Stops the game by destroying the game components and terminating 
		/// the OpenGL libraries.
		/// </summary>
		void stop();

		/// <summary>
		/// Updates the game and the game window. The method is only called 
		/// once per frame.
		/// </summary>
		void update();
	};
} }

#endif