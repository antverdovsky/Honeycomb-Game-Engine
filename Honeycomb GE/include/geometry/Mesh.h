#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>

#include "Vertex.h"

namespace Honeycomb::Geometry {
	class Mesh {
	public:
		/// Initializes an empty mesh.
		Mesh();

		/// Initializes a Mesh with the specified vertices and indices data.
		/// Vertex v[] : The vertices data.
		/// const int &vC : The vertex count.
		/// int i[] : The indices data.
		/// const int &iC : The index count.
		Mesh(Honeycomb::Geometry::Vertex v[], const int &vC, 
			int i[], const int &iC);

		/// Destroys the mesh and the buffers and data associated with it.
		~Mesh();

		/// Draws this Mesh to the screen using the vertex data.
		void draw() const;
	private:
		int vertexBufferObj; // VBO "Pointer"
		int vertCount; // The count of vertices stored for this mesh
		int vertSize; // The byte size of the vertices stored for this mesh

		int indexBufferObj; // IBO "Pointer" (for VBO indexing)
		int indexCount; // The count of the indices stored for this mesh
		int indexSize; // The byte size of the indices stored for this mesh

		/// Adds the vertex data for this mesh.
		/// Vertex v[] : The vertices data.
		/// const int &vC : The vertex count.
		/// int i[] : The indices data.
		/// const int &iC : The index count.
		void addVertexData(Honeycomb::Geometry::Vertex vert[], const int &vC,
			int i[], const int &iC);
	};
}

#endif