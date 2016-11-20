#include "..\..\include\geometry\Mesh.h"

#include <iostream>
#include <sstream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\file\FileIO.h"
#include "..\..\include\math\Vector3f.h"
#include "..\..\include\geometry\Vertex.h"

using Honeycomb::Geometry::Vertex;
using Honeycomb::Math::Vector3f;

namespace Honeycomb::Geometry {
	Mesh::Mesh() {
		// Initialize a Vertex Buffer Object and store it
		GLuint vbo = 0;
		glGenBuffers(1, &vbo);

		// Initialize a Index Buffer Object and store it
		GLuint ibo = 0;
		glGenBuffers(1, &ibo);

		// Copy the VBO and IBO pointers into the mesh instance. Set default 
		// mesh size to zero (no vertices or indices yet).
		this->vertexBufferObj = vbo;
		this->vertCount = 0;
		this->vertSize = 0;
		this->indexBufferObj = ibo;
		this->indexCount = 0;
		this->indexSize = 0;
	}

	Mesh::Mesh(Vertex vert[], int vertCount, int indx[], int indxCount) 
			: Mesh() {
		this->addVertexData(vert, vertCount, indx, indxCount);
	}

	Mesh::~Mesh() {
		GLuint ibo = this->indexBufferObj;
		glDeleteBuffers(1, &ibo);
		
		GLuint vbo = this->vertexBufferObj;
		glDeleteBuffers(1, &vbo);
	}

	void Mesh::addVertexData(Vertex vert[], int vertCount, int indx[],
			int indxCount) {
		// Convert the verticies into floats which OpenGL understands
		GLfloat *vertFloats = Vertex::toFloatBuffer(vert, vertCount);

		// Get the count of the verticies and the memory size (in bytes) of the
		// verticies (each vertex has 8 floats (3 for positions, 2 for texture
		// coordinates, 3 for normals)).
		this->vertCount = vertCount;
		this->vertSize = vertCount * 8 * sizeof(GLfloat);

		// Get the count of indices and their memory size
		this->indexCount = indxCount;
		this->indexSize = indxCount * sizeof(int);

		// Bind the buffer to the VBO and send the vertex data to the buffer 
		// [Static Draw indicates that data is constant].
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);
		glBufferData(GL_ARRAY_BUFFER, this->vertSize, &vertFloats[0], 
			GL_STATIC_DRAW);

		// Bind the buffer to the IBO and send the index data to the buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferObj);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexSize, &indx[0], 
			GL_STATIC_DRAW);
		
		delete vertFloats; // Done using the verticies floats
	}

	void Mesh::draw() {
		// Enable attribute arrays for the vertices
		glEnableVertexAttribArray(0); // The position
		glEnableVertexAttribArray(1); // The texture coordinates
		glEnableVertexAttribArray(2); // The normals

		// Bind the buffer to the VBO.
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);

		// The positions are to be stored at 0, with each one containing 3 
		// floats per face, normalization is not needed, size is taken from the
		// variable stored for this mesh, and the data starts at 0.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);

		// Bind the buffer to the IBO.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferObj);

		// Draw the vertex array data as triangles, from the starting vertex to
		// the final one.
		glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 
			(void*)0);

		// Disable the position vertex attribute array
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}