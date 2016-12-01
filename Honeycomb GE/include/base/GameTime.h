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
		const float& getDeltaTimeMS() const;

		/// Gets the time between the current frame and the last frame in
		/// seconds.
		/// return : The time between the frames (in s).
		const float& getDeltaTimeS() const;

		/// Gets the elapsed game time (since the start of the game) in 
		/// milliseconds.
		/// return : The game time (in ms).
		const float& getElapsedTimeMS() const;

		/// Gets the elapsed game time (since the start of the game) in 
		/// seconds.
		/// return : The game time (in s).
		const float& getElapsedTimeS() const;

		/// Sets the time between the current frame and the last frame in
		/// milliseconds.
		/// The delta time (in ms).
		void setDeltaTimeMS(const float &ms); // todo: privatize...

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
	};
}

#endif