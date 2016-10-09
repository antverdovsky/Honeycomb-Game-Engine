#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>

namespace Honeycomb::Mesh { class Vertex; }
namespace Honeycomb::Mesh::Importer { class Model; }

namespace Honeycomb::Mesh {
	class Mesh {
	public:
		/// Initializes an empty mesh.
		Mesh();

		/// Initializes a mesh from the model.
		/// Model m : The model to be used to initialize the Mesh.
		Mesh(Honeycomb::Mesh::Importer::Model m);

		/// Default Destructor.
		~Mesh();

		/// Adds the vertex data for this mesh.
		/// Vertex vert[] : The vertex data.
		/// int vertCount : The number of verticies which are passed in.
		/// int indx[] : The indicies data.
		/// int indxCount : The number of indicies which are passed in.
		void addVertexData(Vertex vert[], int vertCount, int index[], 
				int indexCount);

		/// Draws this Mesh to the screen using the vertex data.
		void draw();
	private:
		int vertexBufferObj; // VBO "Pointer"
		int vertCount; // The count of vertices stored for this mesh
		int vertSize; // The byte size of the vertices stored for this mesh

		int indexBufferObj; // IBO "Pointer" (for VBO indexing)
		int indexCount; // The count of the indicies stored for this mesh
		int indexSize; // The byte size of the indicies stored for this mesh
	};
}

#endif