#pragma once
#ifndef MESH_H
#define MESH_H

#include <memory>

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
		/// Returns the number of initialized Meshes.
		/// </summary>
		/// <returns>
		/// The number of meshes.
		/// </returns>
		static const int& getInitializedMeshCount();

		/// <summary>
		/// Creates a new, initialized Mesh.
		/// </summary>
		/// <returns>
		/// The shared pointer to the Mesh.
		/// </returns>
		static std::shared_ptr<Mesh> newMeshShared();

		/// <summary>
		/// Creates a new, initialized Mesh.
		/// </summary>
		/// <returns>
		/// The unique pointer to the Mesh.
		/// </returns>
		static std::unique_ptr<Mesh> newMeshUnique();

		/// <summary>
		/// Deinitializes and destroys this Mesh.
		/// </summary>
		~Mesh();

		/// <summary>
		/// Copying of Mesh instances is forbidden.
		/// </summary>
		Mesh(const Mesh &) = delete;

		/// <summary>
		/// Binds this Mesh's index buffer to OpenGL. Note that this is a
		/// global bind and so any currently bound index buffer will be 
		/// unbinded.
		/// 
		/// If the mesh has not yet been initialized, a GLItemNotInitialized
		/// exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void bindIndexBuffer();

		/// <summary>
		/// Binds this Mesh's vertex buffer to OpenGL. Note that this is a
		/// global bind and so any currently bound vertex buffer will be
		/// unbinded.
		/// 
		/// If the mesh has not yet been initialized, a GLItemNotInitialized
		/// exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void bindVertexBuffer();

		/// <summary>
		/// Clears the indices data of this Mesh. 
		/// 
		/// If the mesh has not yet been initialized, a GLItemNotInitialized
		/// exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void clearIndices();

		/// <summary>
		/// Clears the vertices data of this Mesh. 
		/// 
		/// If the mesh has not yet been initialized, a GLItemNotInitialized
		/// exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void clearVertices();

		/// <summary>
		/// Destroys this Mesh item by destroying the mesh buffer. 
		/// 
		/// If the Mesh has not yet been initialized, a GLItemNotInitialized 
		/// exception will be thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void destroy();

		/// <summary>
		/// Returns the raw pointer of the index buffer object of this Mesh.
		/// 
		/// If the mesh has not yet been initialized, this pointer will be
		/// negative.
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
		const std::vector<unsigned int>& getIndices() const;

		/// <summary>
		/// Returns the raw pointer of the vertex buffer object of this Mesh.
		/// </summary>
		/// 
		/// If the mesh has not yet been initialized, this pointer will be
		/// negative.
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
		const std::vector<Vertex>& getVertices() const;

		/// <summary>
		/// Initializes this Mesh item by creating the appropriate mesh buffer.
		/// 
		/// If the Mesh has been initialized, a GLItemAlreadyInitialized
		/// exception will be thrown.
		/// </summary>
		/// <exception cref="GLItemAlreadyInitializedException">
		/// Thrown if the Texture has already been initialized.
		/// </exception>
		void initialize();

		/// <summary>
		/// Draws this Mesh using the specified shader program. 
		/// 
		/// If the Mesh has not yet been initialized, a GLItemNotInitialized 
		/// exception will be thrown.
		/// </summary>
		/// <param name="shader">
		/// The shader using which the Mesh should be drawn.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void render(Honeycomb::Shader::ShaderProgram &shader) const;

		/// <summary>
		/// Sets the indices data for this Mesh.
		/// 
		/// If the Mesh has not yet been initialized, a GLItemNotInitialized 
		/// exception will be thrown.
		/// </summary>
		/// <param name="indices">
		/// The vector of indices which define this Mesh.
		/// </param>
		/// <exception cref="GLItemAlreadyInitializedException">
		/// Thrown if the Texture has already been initialized.
		/// </exception>
		void setIndexData(const std::vector<unsigned int> &indices);

		/// <summary>
		/// Sets the vertices data for this Mesh.
		/// 
		/// If the Mesh has not yet been initialized, a GLItemNotInitialized 
		/// exception will be thrown.
		/// </summary>
		/// <param name="vertices">
		/// The vector of vertices which define this Mesh.
		/// </param>
		/// <exception cref="GLItemAlreadyInitializedException">
		/// Thrown if the Texture has already been initialized.
		/// </exception>
		void setVertexData(const std::vector<Vertex> &vertices);

		/// <summary>
		/// Checks if the specified Mesh is equal to this mesh.
		/// </summary>
		/// <param name="rhs">
		/// The right hand side of the operator.
		/// </param>
		/// <returns>
		/// True if the vertex buffer object and the index buffer object
		/// pointers of this instance and the specified instance are the same.
		/// </returns>
		bool operator==(const Mesh &rhs) const;

		/// <summary>
		/// Checks if the specified Mesh is not equal to this mesh.
		/// </summary>
		/// <param name="rhs">
		/// The right hand side of the operator.
		/// </param>
		/// <returns>
		/// True if the vertex buffer object or the index buffer object
		/// pointers of this instance and the specified instance are not the
		/// same.
		/// </returns>
		bool operator!=(const Mesh &rhs) const;

		/// <summary>
		/// Assignment of the Mesh class is forbidden.
		/// </summary>
		Mesh& operator=(const Mesh &) = delete;
	private:
		// Number of initialized meshes
		static int meshCount;
		
		int vertexBufferObject;                                // VBO "Pointer"
		int indexBufferObject;                                 // IBO "Pointer"
		
		std::vector<Vertex> vertices;                          // Vertices List
		std::vector<unsigned int> indices;                     // Indices List

		/// <summary>
		/// Creates a new, empty Mesh item.
		/// </summary>
		Mesh();
	};
} }

#endif
