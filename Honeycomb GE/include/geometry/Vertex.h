#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"

namespace Honeycomb::Geometry {
	class Vertex {
	public:
		/// Creates an empty vertex, with the position, texture coordinates and
		/// normals being set to their default Vector3f/2f values.
		Vertex();

		/// Creates a vertex initialized to the specified position, texture
		/// coordinates and normal.
		/// Vector3f norm : The normal of the vertex.
		/// Vector3f pos : The position of the vertex.
		/// Vector2f uv : The texture coordinates of the vertex.
		Vertex(Honeycomb::Math::Vector3f norm, Honeycomb::Math::Vector3f pos, 
			Honeycomb::Math::Vector2f uv);

		/// Gets the normal of this vertex.
		/// return : The normal vector.
		Honeycomb::Math::Vector3f& getNormal();

		/// Gets the position of this vertex.
		/// return : The position vector.
		Honeycomb::Math::Vector3f& getPosition();

		/// Gets the texture coordinate of this vertex.
		/// return : The texture coordinate vector.
		Honeycomb::Math::Vector2f& getUV();

		/// Converts the array of vertices to a float buffer. The buffer will
		/// store each vertex's position, followed by the texture coordinates
		/// followed by the normal. The array will be returned as a newly 
		/// allocated array and should, therefore, be deleted after being used.
		/// Vertex verts[] : The array of vertices to be converted to a float
		///					 buffer.
		/// int count : The number of vertices passed in.
		/// return : The float buffer.
		static float* toFloatBuffer(Vertex verts[], int count);
		
		// Default Destructor.
		~Vertex();
	private:
		Honeycomb::Math::Vector3f normal; // The normal of the vertex
		Honeycomb::Math::Vector3f position; // The position of the vertex
		Honeycomb::Math::Vector2f uv; // The texture coordinates of the vertex
	};
}

#endif