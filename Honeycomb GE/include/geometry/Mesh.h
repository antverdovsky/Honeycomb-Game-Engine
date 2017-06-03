#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>

#include "Vertex.h"
#include "../base/GLItem.h"
#include "../shader/ShaderProgram.h"

namespace Honeycomb { namespace Geometry {
	class Mesh : public Honeycomb::Base::GLItem {
	public:
		/// Initializes this Mesh by creating the appropriate Index and Vertex
		/// buffers for it.
		void initialize();

		/// Destroys this Mesh by destroying the appropriate Index and Vertex
		/// buffers of it.
		void destroy();

		/// Draws this Mesh to the screen using the vertex data.
		/// ShaderProgram &shader : The shader which will draw the mesh.
		void draw(Honeycomb::Shader::ShaderProgram &shader) const;

		/// Sets the Index Data for this Mesh. Do note that the index buffer
		/// will be cleared before any data is modified for this Mesh.
		/// int indices[] : The array of indices to be passed to the IBO.
		/// const int &count : The length of the index array.
		void setIndexData(int indices[], const int &count);

		/// Sets the Vertex Data for this Mesh. Do note that the vertex buffer
		/// will be cleared before any data is modified for this Mesh.
		/// Vertex vert[] : The array of vertices to be passed to the VBO.
		/// const int &count : The length of the vertex array.
		void setVertexData(Honeycomb::Geometry::Vertex vert[], const int 
				&count);
	private:
		int vertexBufferObj; // VBO "Pointer"
		int vertCount; // The count of vertices stored for this mesh
		int vertSize; // The byte size of the vertices stored for this mesh

		int indexBufferObj; // IBO "Pointer" (for VBO indexing)
		int indexCount; // The count of the indices stored for this mesh
		int indexSize; // The byte size of the indices stored for this mesh
	};
} }

#endif
