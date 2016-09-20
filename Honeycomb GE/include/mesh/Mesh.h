#pragma once
#ifndef MESH_H
#define MESH_H

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
		/// int count : The number of verticies which are passed in.
		void addVertexData(Vertex vert[], int count);

		/// Draws this Mesh to the screen using the vertex data.
		void draw();
	private:
		int vertexBufferObj; // VBO "Pointer"
		int count; // The count of vertices stored for this mesh
		int size; // The size (in bytes) of the vertices stored for this mesh
	};
}

#endif