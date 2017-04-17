#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "../../include/math/Vector2f.h"
#include "../../include/math/Vector3f.h"

namespace Honeycomb { namespace Geometry {
	class Vertex {
	public:
		/// Creates an empty vertex, with the position, texture coordinates,
		/// normals and tangent being set to their default Vector values.
		Vertex();

		/// Creates a vertex initialized to the specified position, normals,
		/// tangent and texture coordinates.
		/// const Vector3f &pos : The position of the vertex.
		/// const Vector3f &norm : The normal of the vertex.
		/// const Vector3f &tan : The tangent vector of the vertex.
		/// const Vector2f &uv : The texture coordinates 0 of the vertex.
		Vertex(const Honeycomb::Math::Vector3f &pos,
			const Honeycomb::Math::Vector3f &norm,
			const Honeycomb::Math::Vector3f &tan,
			const Honeycomb::Math::Vector2f &tc0);

		/// Gets the normal of this vertex.
		/// return : The normal vector.
		const Honeycomb::Math::Vector3f& getNormal() const;
		
		/// Gets the position of this vertex.
		/// return : The position vector.
		const Honeycomb::Math::Vector3f& getPosition() const;

		/// Gets the tangent of this vertex.
		/// return : The tangent vector.
		const Honeycomb::Math::Vector3f& getTangent() const;

		/// Gets the texture coordinates 0 of this vertex.
		/// return : The texture coordinates 0 vector.
		const Honeycomb::Math::Vector2f& getTexCoords0() const;

		/// Sets the normal of this vertex.
		/// const Vector3f &norm : The normal vector.
		void setNormal(const Honeycomb::Math::Vector3f &norm);

		/// Sets the position of this vertex.
		/// const Vector3f &pos : The position vector.
		void setPosition(const Honeycomb::Math::Vector3f &pos);
		
		/// Sets the tangent of this vertex.
		/// const Vector3f &tan : The tangent vector.
		void setTangent(const Honeycomb::Math::Vector3f &tan);

		/// Sets the texture coordinates 0 of this vertex.
		/// const Vector2f &uv : The texture coordinates 0 vector.
		void setTexCoords0(const Honeycomb::Math::Vector2f &uv);

		/// Converts the array of vertices to a float buffer. Foreach vertex,
		/// the following are added to the buffer:
		/// { P.x, P.y, P.z, N.x, N.y, N.z, T.x, T.y, T.z, TC0.x, TC0.y },
		/// where P is the position vector, N is the normals vector, T is the
		/// tangent vector and TC0 is the texture coordinates 0 vector.s
		/// Vertex verts[] : The array of vertices to be converted to a float
		///					 buffer.
		/// int count : The number of vertices passed in (length of the verts
		///				array).
		/// return : The float buffer.
		static std::vector<float> toFloatBuffer(Vertex verts[], 
				const int &count);
	private:
		Honeycomb::Math::Vector3f position;		// Model Position
		Honeycomb::Math::Vector3f normal;		// Model Normal
		Honeycomb::Math::Vector3f tangent;		// Model Tangent

		Honeycomb::Math::Vector2f texCoords0;	// Texture Coordinates 0
	};
} }

#endif
