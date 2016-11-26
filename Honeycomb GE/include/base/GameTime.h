#pragma once
#ifndef GAME_TIME_H
#define GAME_TIME_H

namespace Honeycomb::Base {
	class GameTime {
	public:
		const static float SECOND; // Number of ms in a sec.
		
		/// Gets the time between the current frame and the last frame in
		/// milliseconds.
		/// return : The time between the frames (in milliseconds).
		float getDeltaTimeMS();

		/// Gets the time between the current frame and the last frame in
		/// seconds.
		/// return : The time between the frames (in s).
		float getDeltaTimeS();

		/// Gets the elapsed game time (since the start of the game) in 
		/// milliseconds.
		/// return : The game time (in ms).
		float getElapsedTimeMS();

		/// Gets the elapsed game time (since the start of the game) in 
		/// seconds.
		/// return : The game time (in s).
		float getElapsedTimeS();

		/// Sets the time between the current frame and the last frame in
		/// milliseconds.
		/// The delta time (in ms).
		void setDeltaTimeMS(float ms);

		/// Returns the Game Time instance of this Singleton.
		/// return : The Game Time instance.
		static GameTime* getGameTime();
	private:
		static GameTime* gameTime; // Singleton Instance

		float deltaTime; // The last known time between frames (in ms).

		/// Constructs a new Game Time component.
		GameTime();
	};
}

#endif