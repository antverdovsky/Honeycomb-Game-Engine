#pragma once
#ifndef GAME_TIME_H
#define GAME_TIME_H

namespace Honeycomb { namespace Base {
	class GameTime {
		friend class BaseMain; // Only allow BaseMain to set the delta time
	public:
		const static float SECOND; // Number of milliseconds in a second
		
		/// <summary>
		/// Gets the time between the current frame and the last frame in
		/// milliseconds.
		/// </summary>
		/// <returns>
		/// The time between the frames (in milliseconds).
		/// </returns>
		const float& getDeltaTimeMS() const;

		/// <summary>
		/// Gets the time between the current frame and the last frame in
		/// seconds.
		/// </summary>
		/// <returns>
		/// The time between the frames (in seconds).
		/// </returns>
		float getDeltaTimeS() const;

		/// <summary>
		/// Gets the elapsed game time (since the initialization of the game
		/// engine) in milliseconds.
		/// </summary>
		/// <returns>
		/// The game time (in milliseconds).
		/// </returns>
		float getElapsedTimeMS() const;

		/// <summary>
		/// Gets the elapsed game time (since the initialization of the game
		/// engine) in seconds.
		/// </summary>
		/// <returns>
		/// The game time (in seconds).
		/// </returns>
		float getElapsedTimeS() const;

		/// <summary>
		/// Returns the Game Time instance of this Singleton.
		/// </summary>
		/// <returns>
		/// The Game Time instance.
		/// </returns>
		static GameTime* getGameTime();
	private:
		float deltaTime; // The time between frames (in ms) for the last
                         // two frames rendered.

		/// <summary>
		/// Sets the time between the current frame and the last frame in
		/// milliseconds.
		/// </summary>
		/// <param name="ms">
		/// The delta time (in milliseconds).
		/// </param>
		void setDeltaTimeMS(const float &ms);
	};
} }

#endif