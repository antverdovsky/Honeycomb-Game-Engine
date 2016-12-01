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

		/// Handles the loading in of resources and initialization of game
		/// data at the very beginning of the game.
		virtual void start();

		/// Handles the freeing of resources and destruction of game data at
		/// the very end of the game.
		virtual void stop();

		/// Handles the updating for the game every frame.
		virtual void update();
	};
}

#endif