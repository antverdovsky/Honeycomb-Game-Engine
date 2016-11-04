#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>

#include "..\..\include\geometry\importer\Model.h"

namespace Honeycomb::Geometry {
	class Mesh {
	public:
		/// Initializes an empty mesh.
		Mesh();

		/// Initializes a mesh from the model.
		/// Model m : The model to be used to initialize the Mesh.
		Mesh(Honeycomb::Geometry::Importer::Model m);

		/// Destroys the mesh and the buffers and data associated with it.
		~Mesh();

		/// Adds the vertex data for this mesh.
		/// Vertex vert[] : The vertex data.
		/// int vertCount : The number of verticies which are passed in.
		/// int index[] : The indices data.
		/// int indxCount : The number of indices.
		void addVertexData(Honeycomb::Geometry::Vertex vert[], int vertCount,
				int index[], int intxCount);

		/// Draws this Mesh to the screen using the vertex data.
		void draw();
	private:
		int vertexBufferObj; // VBO "Pointer"
		int vertCount; // The count of vertices stored for this mesh
		int vertSize; // The byte size of the vertices stored for this mesh

		int indexBufferObj; // IBO "Pointer" (for VBO indexing)
		int indexCount; // The count of the indices stored for this mesh
		int indexSize; // The byte size of the indices stored for this mesh
	};
}

#endif