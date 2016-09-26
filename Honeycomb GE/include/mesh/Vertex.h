#pragma once
#ifndef VERTEX_H
#define VERTEX_H

namespace Honeycomb::Math { class Vector3f; }

namespace Honeycomb::Mesh {
	class Vertex {
	public:
		/// Creates a vertex with the specified position.
		/// Vector3f pos : The position of the vertex.
		Vertex(Honeycomb::Math::Vector3f pos);

		/// Copy Constructor.
		/// Vertex &v : The vector to copy into this one.
		Vertex(Vertex &v);

		/// Destroys the vertex, and its position vector.
		~Vertex();

		/// Gets the position vector.
		/// return : The position vector.
		Honeycomb::Math::Vector3f* getPosition();

		/// Converts an array of verticies to an array of the Vector positions
		/// of each vertex. The array will be returned as a dynamically 
		/// allocated array and should, therefore, be deleted after being used.
		/// Vertex vert[] : The verticies to be converted to a float buffer.
		/// int count : The number of verticies which are to be converted.
		/// return : An array of floats which is composed of each vertex's x,
		///			 y and z, in that order.
		static float* verticiesToFloatBuffer(Vertex vert[], int count);
	private:
		Honeycomb::Math::Vector3f *position; // Stores the position vector.
	};
}

#endif