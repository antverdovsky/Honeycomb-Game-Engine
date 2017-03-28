#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"

namespace Honeycomb::Geometry {
	class Vertex {
	public:
		/// Creates an empty vertex, with the position, texture coordinates,
		/// normals and tangent being set to their default Vector values.
		Vertex();

		/// Creates a vertex initialized to the specified position, texture
		/// coordinates, normal and tangent.
		/// const Vector3f &norm : The normal of the vertex.
		/// const Vector3f &pos : The position of the vertex.
		/// const Vector2f &uv : The texture coordinates of the vertex.
		/// const Vector3f &tan : The tangent vector of the vertex.
		Vertex(const Honeycomb::Math::Vector3f &norm,
			const Honeycomb::Math::Vector3f &pos, 
			const Honeycomb::Math::Vector2f &uv,
			const Honeycomb::Math::Vector3f &tan);

		/// Gets the tangent of this vertex.
		/// return : The tangent vector.
		const Honeycomb::Math::Vector3f& getTangent() const;

		/// Gets the normal of this vertex.
		/// return : The normal vector.
		const Honeycomb::Math::Vector3f& getNormal() const;

		/// Gets the position of this vertex.
		/// return : The position vector.
		const Honeycomb::Math::Vector3f& getPosition() const;

		/// Gets the texture coordinate of this vertex.
		/// return : The texture coordinate vector.
		const Honeycomb::Math::Vector2f& getUV() const;

		/// Sets the tangent of this vertex.
		/// const Vector3f &tan : The tangent vector.
		void setTangent(const Honeycomb::Math::Vector3f &tan);

		/// Sets the normal of this vertex.
		/// const Vector3f &norm : The normal vector.
		void setNormal(const Honeycomb::Math::Vector3f &norm);

		/// Sets the position of this vertex.
		/// const Vector3f &pos : The position vector.
		void setPosition(const Honeycomb::Math::Vector3f &pos);

		/// Sets the UV texture coordinates of this vertex.
		/// const Vector2f &uv : The UV texture coordinates vector.
		void setUV(const Honeycomb::Math::Vector2f &uv);

		/// Converts the array of vertices to a float buffer. The buffer will
		/// store each vertex's position, followed by the texture coordinates
		/// followed by the normal, followed by the tangent. The array will 
		/// be a dynamically allocated array and should, therefore, be deleted 
		/// after being used.
		/// Vertex verts[] : The array of vertices to be converted to a float
		///					 buffer.
		/// int count : The number of vertices passed in (length of the verts
		///				array).
		/// return : The float buffer.
		static float* toFloatBuffer(Vertex verts[], const int &count);
	private:
		Honeycomb::Math::Vector3f normal;		// Model Normal Vector
		Honeycomb::Math::Vector3f position;		// Model Position
		Honeycomb::Math::Vector2f uv;			// Texture Coordinates
		Honeycomb::Math::Vector3f tangent;		// Model Tangent Vector
	};
}

#endif