#pragma once
#ifndef BASE_GAME_H
#define BASE_GAME_H

namespace Honeycomb::Base {
	class BaseGame {
	public:
		/// Handles the input for the game every frame.
		virtual void input();

		/// Handles the rendering for the game every frame.
		virtual void render();

		/// Starts the game. Note, this should be used for loading in and 
		/// processing resources and for initializing game components only.
		virtual void start();

		/// Stops the game.
		virtual void stop();

		/// Updates the game every frame.
		virtual void update();
	};
}

#endif