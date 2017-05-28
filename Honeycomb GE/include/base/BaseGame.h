#pragma once
#ifndef BASE_GAME_H
#define BASE_GAME_H

namespace Honeycomb { namespace Base {
	class BaseGame {
	public:
		/// <summary>
		/// This method should be overwritten to handle all of the input of the
		/// Game. It is called at the very beginning of each frame, before the
		/// game is updated. At the end of each frame, the input data is 
		/// cleared.
		/// </summary>
		virtual void input();

		/// <summary>
		/// This method handles any rendering which should be done by the game.
		/// Typically, this method need not be overwritten or used, unless the
		/// game utilizes some rendering technique which is not included in the
		/// base engine.
		/// </summary>
		virtual void render();

		/// <summary>
		/// This method is used to start the game. It is called after all of
		/// the internal items used by the base engine are started. This should
		/// be overwritten to load in models, textures, shaders, etc., and to 
		/// setup the game scene.
		/// </summary>
		virtual void start();

		/// <summary>
		/// This method is used to stop the game. It is called before all of
		/// the internal items used by the base engine are ended. This should
		/// be overwritten to remove models, textures, shaders, etc. from 
		/// memory.
		/// </summary>
		virtual void stop();

		/// <summary>
		/// This method handles the updating tasks to be conducted each frame.
		/// This method's first call occurs only after the start method has
		/// been called. This should be used to change the scene at runtime.
		/// This is called after the input method and before the render method.
		/// </summary>
		virtual void update();
	};
} }

#endif