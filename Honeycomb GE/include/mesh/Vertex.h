#pragma once
#ifndef VERTEX_H
#define VERTEX_H

class Vector3f;

class Vertex {
public:
	/// Creates a vertex with the specified position.
	/// Vector3f pos : The position of the vertex.
	Vertex(Vector3f pos);

	/// Destroys the vertex, and its position vector.
	~Vertex();

	/// Gets the position vector.
	/// return : The position vector.
	Vector3f* getPosition();

	/// Converts an array of verticies to an array of the Vector positions
	/// of each vertex. The array will be returned as a dynamically allocated
	/// array and should, therefore, be deleted after being used.
	/// Vertex vert[] : The verticies to be converted to a float buffer.
	/// int count : The number of verticies which are to be converted.
	/// return : An array of floats which is composed of each vertex's x, y,
	///			 and z components.
	static float* toFloatBuffer(Vertex vert[], int count);
private:
	Vector3f* position; // Stores the position vector.
};

#endif