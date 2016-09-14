#pragma once
#ifndef VECTOR_2F_H
#define VECTOR_2F_H

class Vector2f {
public:
	/// Creates a new two dimensional vector with the specified x and y
	/// components.
	/// int x : The x-component.
	/// int y : The y-component.
	Vector2f(float x, float y);
	
	/// Empty Destructor.
	~Vector2f();

	/// Gets the x and y components of the vector and writes them to the passed
	/// in reference values.
	/// float &x : The reference to where the x-component is to be written to.
	/// float &y : The reference to where the y-component is to be written to.
	void get(float &x, float &y);

	/// Gets the x-component of the vector.
	/// return : The x-component.
	float getX();

	/// Gets the y-component of the vector.
	/// return : The y-component.
	float getY();

	/// Sets the x and y components of the vector.
	/// float x : The new x-component.
	/// float y : The new y-component.
	void set(float x, float y);

	/// Sets the x-component of the vector.
	/// float y : The new x-component.
	void setX(float y);

	/// Sets the y-component of the vector.
	/// float y : The new y-component.
	void setY(float y);
private:
	float x; // The x-component
	float y; // The y-component
};

#endif