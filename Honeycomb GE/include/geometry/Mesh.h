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
		/// Binds this Mesh's index buffer to OpenGL. Note that this is a
		/// global bind and so any currently bound index buffer will be 
		/// unbinded. If the mesh has not yet been initialized, a
		/// GLItemNotInitialization exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void bindIndices();

		/// <summary>
		/// Binds this Mesh's vertex buffer to OpenGL. Note that this is a
		/// global bind and so any currently bound vertex buffer will be
		/// unbinded. If the mesh has not yet been initialized, a
		/// GLItemNotInitialization exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void bindVertices();

		/// <summary>
		/// Clears the indices data of this Mesh. If the mesh has not yet been 
		/// initialized, a GLItemNotInitialization exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void clearIndices();

		/// <summary>
		/// Clears the vertices data of this Mesh. If the mesh has not yet been
		/// initialized, a GLItemNotInitialization exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void clearVertices();

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
		/// Returns the raw pointer of the index buffer object of this Mesh.
		/// </summary>
		/// <returns>
		/// The index buffer object pointer.
		/// </returns>
		const int& getIndexBufferObject() const;

		/// <summary>
		/// Returns the list of indices of this Mesh.
		/// </summary>
		/// <returns>
		/// The list of the indices of the Mesh.
		/// </returns>
		const std::vector<unsigned int> getIndices() const;

		/// <summary>
		/// Returns the raw pointer of the vertex buffer object of this Mesh.
		/// </summary>
		/// <returns>
		/// The vertex buffer object pointer.
		/// </returns>
		const int& getVertexBufferObject() const;

		/// <summary>
		/// Returns the list of vertices of this Mesh.
		/// </summary>
		/// <returns>
		/// The list of the vertices of the Mesh.
		/// </returns>
		const std::vector<Vertex> getVertices() const;

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
		void setIndexData(const std::vector<unsigned int> &indices);

		/// <summary>
		/// Sets the vertices data for this Mesh.
		/// </summary>
		/// <param name="vertices">
		/// The vector of vertices which define this Mesh.
		/// </param>
		void setVertexData(const std::vector<Vertex> &vertices);
	private:
		int vertexBufferObject;                  // VBO "Pointer"
		std::vector<Vertex> vertices;            // Vertices List

		int indexBufferObject;                   // IBO "Pointer"
		std::vector<unsigned int> indices;       // Indices List
	};
} }

#endif
