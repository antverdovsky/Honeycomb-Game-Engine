#pragma once
#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "../base/GLItem.h"
#include "../shader/ShaderProgram.h"

namespace Honeycomb { namespace Geometry {
	/// <summary>
	/// Class responsible for storing the vertex and index data of a Mesh.
	/// </summary>
	class Mesh : public Honeycomb::Base::GLItem {
	public:
		/// <summary>
		/// Creates a new, empty Mesh item.
		/// </summary>
		Mesh();

		/// <summary>
		/// Destroys this Mesh item by destroying the mesh buffer. If the Mesh
		/// has not yet been initialized, a GLItemNotInitialized exception will
		/// be thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void destroy();

		/// <summary>
		/// Draws this Mesh using the specified shader program. If the Mesh
		/// has not yet been initialized, a GLItemNotInitialized exception will
		/// be thrown.
		/// </summary>
		/// <param name="shader">
		/// The shader using which the Mesh should be drawn.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void draw(Honeycomb::Shader::ShaderProgram &shader) const;

		/// <summary>
		/// Initializes this Mesh item by creating the appropriate mesh buffer.
		/// If the Mesh has been initialized, a GLItemAlreadyInitialized
		/// exception will be thrown.
		/// </summary>
		/// <exception cref="GLItemAlreadyInitializedException">
		/// Thrown if the Texture has already been initialized.
		/// </exception>
		void initialize();

		/// <summary>
		/// Sets the indices data for this Mesh.
		/// </summary>
		/// <param name="indices">
		/// The vector of indices which define this Mesh.
		/// </param>
		void setIndexData(const std::vector<int> &indices);

		/// <summary>
		/// Sets the vertices data for this Mesh.
		/// </summary>
		/// <param name="vertices">
		/// The vector of vertices which define this Mesh.
		/// </param>
		void setVertexData(const std::vector<Vertex> &vertices);
	private:
		int vertexBufferObj;  // VBO "Pointer"
		int vertCount;        // The number of vertices
		int vertSize;         // The byte size of the vertices

		int indexBufferObj;   // IBO "Pointer" (for VBO indexing)
		int indexCount;       // The number of indices
		int indexSize;        // The byte size of the indices
	};
} }

#endif
