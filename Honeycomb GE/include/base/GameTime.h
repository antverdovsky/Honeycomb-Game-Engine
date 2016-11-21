#pragma once
#ifndef TIME_H
#define TIME_H

namespace Honeycomb::Base::Time {
	const float SECOND = 1000.0F; // Number of ms (this Time unit) in a sec.

	extern float deltaTime; // The last known time between frames.

	/// Gets the time between the current frame and the last frame in
	/// milliseconds.
	/// return : The time between the frames (in ms).
	float getDeltaTime();

	/// Gets the time between the current frame and the last frame in
	/// seconds.
	/// return : The time between the frames (in s).
	float getDeltaTimeSeconds();

	/// Gets the current game time (since the start of the game) in 
	/// milliseconds.
	/// return : The game time (in ms).
	float getGameTime();

	/// Gets the current game time (since the start of the game) in 
	/// seconds.
	/// return : The game time (in s).
	float getGameTimeSeconds();

	/// Sets the time between the current frame and the last frame in
	/// milliseconds.
	/// float dT : The time difference (in ms) between the frames.
	void setDeltaTime(float dT);
}

#endif