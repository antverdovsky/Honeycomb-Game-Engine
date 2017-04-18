#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "../../include/math/Vector2f.h"
#include "../../include/math/Vector3f.h"

namespace Honeycomb { namespace Geometry {
	class Vertex {
	public:
		const static int ELEMENTS_PER_ATTRIBUTE_COUNT = 4;
		const static int ATTRIBUTES_PER_VERTEX_COUNT  = 4;
		const static int ELEMENTS_PER_VERTEX_COUNT    = 
			ELEMENTS_PER_ATTRIBUTE_COUNT * ATTRIBUTES_PER_VERTEX_COUNT;

		const static int ELEMENT_SIZE				  = sizeof(float);
		const static int ELEMENTS_PER_ATTRIBUTE_SIZE  = 
			ELEMENT_SIZE * ELEMENTS_PER_ATTRIBUTE_COUNT;
		const static int ELEMENTS_PER_VERTEX_SIZE	  =
			ELEMENT_SIZE * ELEMENTS_PER_VERTEX_COUNT;

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

		/// Converts the array of vertices to a float buffer. For each vertex,
		/// the attributes of the vertex are padded to four elements and then
		/// added to the buffer in the order of position, normal, tangent,
		/// texture coordinates.
		/// Vertex verts[] : The array of vertices to be converted to a float
		///					 buffer.
		/// int count : The number of vertices passed in (length of the verts
		///				array).
		/// return : The float buffer.
		static std::vector<float> toFloatBuffer(Vertex verts[], 
				const int &count);
	private:
												// ATTRIBUTE  (LAYOUT LOCATION)
		Honeycomb::Math::Vector3f position;		// Model Position			(0)
		Honeycomb::Math::Vector3f normal;		// Model Normal				(1)
		Honeycomb::Math::Vector3f tangent;		// Model Tangent			(2)

		Honeycomb::Math::Vector2f texCoords0;	// Texture Coordinates 0	(3)
	};
} }

#endif
