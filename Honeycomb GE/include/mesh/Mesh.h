#pragma once
#ifndef MESH_H
#define MESH_H

class Vertex;

class Mesh {
public:
	/// Initializes a Mesh instance using the specified verticies.
	/// Vertex vert[] : The verticices to be added to the Mesh.
	/// int count : The number of verticies which are passed in.
	Mesh(Vertex vert[], int count);

	/// Default Destructor.
	~Mesh();

	/// Draws this Mesh to the screen using the vertex data.
	void draw();
private:
	int vertexBufferObj; // VBO "Pointer"
	int count; // The count of vertices stored for this mesh
	int size; // The size (in bytes) of the vertices stored for this mesh

	/// Sets the vertex data for this mesh.
	/// Vertex vert[] : The vertex data.
	/// int count : The number of verticies which are passed in.
	void setVertexData(Vertex vert[], int count);
};

#endif