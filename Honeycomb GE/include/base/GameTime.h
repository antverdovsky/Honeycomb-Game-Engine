#pragma once
#ifndef GAME_TIME_H
#define GAME_TIME_H

namespace Honeycomb::Base {
	class GameTime {
		friend class BaseMain; // Only allow BaseMain to set the delta time

	public:
		const static float SECOND; // Number of ms in a sec.
		
		/// Gets the time between the current frame and the last frame in
		/// milliseconds.
		/// return : The time between the frames (in milliseconds).
		const float& getDeltaTimeMS() const;

		/// Gets the time between the current frame and the last frame in
		/// seconds.
		/// return : The time between the frames (in s).
		float getDeltaTimeS() const;

		/// Gets the elapsed game time (since the start of the game) in 
		/// milliseconds.
		/// return : The game time (in ms).
		float getElapsedTimeMS() const;

		/// Gets the elapsed game time (since the start of the game) in 
		/// seconds.
		/// return : The game time (in s).
		float getElapsedTimeS() const;

		/// Returns the Game Time instance of this Singleton.
		/// return : The Game Time instance.
		static GameTime* getGameTime();
	private:
		static GameTime* gameTime; // Singleton Instance

		float deltaTime; // The time between frames (in ms) for the last
						 // two frames rendered.

		/// Constructs a new Game Time instance.
		GameTime();

		/// Destructs this Game Time instance.
		~GameTime();

		/// Sets the time between the current frame and the last frame in
		/// milliseconds.
		/// const float &ms : The delta time (in ms).
		void setDeltaTimeMS(const float &ms);
	};
}

#endif