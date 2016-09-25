#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>

namespace Honeycomb::Mesh { class Vertex; }

namespace Honeycomb::Mesh {
	class Mesh {
	public:
		/// Initializes an empty mesh.
		Mesh();

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

		/// Loads in a mesh from the specified file and initializes a new
		/// instance of the mesh class containing the verticies and indicies
		/// of the mesh.
		/// std::string file : The full path to the mesh .OBJ file.
		/// return : The mesh instance.
		static Mesh* loadMeshOBJ(std::string file);
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