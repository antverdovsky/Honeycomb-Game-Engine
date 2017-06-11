#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "../../include/math/Vector2f.h"
#include "../../include/math/Vector3f.h"

namespace Honeycomb { namespace Geometry {
	/// <summary>
	/// Class for storing any mesh data for a Vertex.
	/// </summary>
	class Vertex {
		friend class Mesh;
	public:
		/// <summary>
		/// Converts the specified array of vertices to a float buffer which
		/// may be directly passed to an OpenGL mesh buffer. For each vertex,
		/// the position, normal, tangent and index zero texture coordinates
		/// are appended to the float buffer, in that order. For each vector,
		/// if the vector has less than four elements, zeros are appended to 
		/// the remaining components to pad the data.
		/// </summary>
		/// <param name="verts">
		/// The vertices array which is to be converted to a float buffer.
		/// </param>
		/// <returns>
		/// The mesh float buffer constructed from the vertices array.
		/// </returns>
		static std::vector<float> toFloatBuffer(const std::vector<Vertex>
				&verts);

		/// <summary>
		/// Creates a new vertex with the position, normals, tangents and
		/// texture coordinates being set to their default Vector2f and
		/// Vector3f values.
		/// </summary>
		Vertex();

		/// <summary>
		/// Creates a new vertex with the specified position, normals,
		/// tangents and texture coordinates.
		/// </summary>
		/// <param name="pos">
		/// The world space position vector of the vertex.
		/// </param>
		/// <param name="norm">
		/// The normal vector of the vertex.
		/// </param>
		/// <param name="tan">
		/// The tangent vector of the vertex.
		/// </param>
		/// <param name="tc0">
		/// The texture coordinates at index zero of the vertex.
		/// </param>
		Vertex(const Honeycomb::Math::Vector3f &pos,
				const Honeycomb::Math::Vector3f &norm,
				const Honeycomb::Math::Vector3f &tan,
				const Honeycomb::Math::Vector2f &tc0);

		/// <summary>
		/// Gets the normal vector of the vertex.
		/// </summary>
		/// <returns>
		/// The normal vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getNormal() const;
		
		/// <summary>
		/// Gets the position vector of the vertex.
		/// </summary>
		/// <returns>
		/// The position vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getPosition() const;

		/// <summary>
		/// Gets the tangent vector of the vertex.
		/// </summary>
		/// <returns>
		/// The tangent vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getTangent() const;

		/// <summary>
		/// Gets the index zero texture coordinates vector of the vertex.
		/// </summary>
		/// <returns>
		/// The index zero texture coordinates vector.
		/// </returns>
		const Honeycomb::Math::Vector2f& getTexCoords0() const;

		/// <summary>
		/// Sets the normal vector of the vertex.
		/// </summary>
		/// <param name="norm">
		/// The normal vector.
		/// </param>
		void setNormal(const Honeycomb::Math::Vector3f &norm);

		/// <summary>
		/// Sets the position vector of the vertex.
		/// </summary>
		/// <param name="pos">
		/// The position vector.
		/// </param>
		void setPosition(const Honeycomb::Math::Vector3f &pos);
		
		/// <summary>
		/// Sets the tangent vector of the vertex.
		/// </summary>
		/// <param name="norm">
		/// The tangent vector.
		/// </param>
		void setTangent(const Honeycomb::Math::Vector3f &tan);

		/// <summary>
		/// Sets the index zero texture coordinates vector of the vertex.
		/// </summary>
		/// <param name="uv">
		/// The index zero texture coordinates vector.
		/// </param>
		void setTexCoords0(const Honeycomb::Math::Vector2f &uv);
	private:
		const static int ELEMENTS_PER_ATTRIBUTE_COUNT = 4;
		const static int ATTRIBUTES_PER_VERTEX_COUNT = 4;
		const static int ELEMENTS_PER_VERTEX_COUNT =
			ELEMENTS_PER_ATTRIBUTE_COUNT * ATTRIBUTES_PER_VERTEX_COUNT;

		const static int ELEMENT_SIZE = sizeof(float);
		const static int ELEMENTS_PER_ATTRIBUTE_SIZE =
			ELEMENT_SIZE * ELEMENTS_PER_ATTRIBUTE_COUNT;
		const static int ELEMENTS_PER_VERTEX_SIZE =
			ELEMENT_SIZE * ELEMENTS_PER_VERTEX_COUNT;

		                                        // ATTRIBUTE  (LAYOUT LOCATION)
		Honeycomb::Math::Vector3f position;     // Model Position           (0)
		Honeycomb::Math::Vector3f normal;       // Model Normal             (1)
		Honeycomb::Math::Vector3f tangent;      // Model Tangent            (2)

		Honeycomb::Math::Vector2f texCoords0;   // Texture Coordinates 0    (3)
	};
} }

#endif
