#include "..\..\include\mesh\Mesh.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\mesh\Vertex.h"

using Honeycomb::Mesh::Vertex;

namespace Honeycomb::Mesh {
	Mesh::Mesh() {
		// Initialize a buffer and store the Vertex Buffer Object in a GLuint.
		GLuint vbo = 0;
		glGenBuffers(1, &vbo);

		// Convert GLuint to a regular integer and copy to the vertex buffer in
		// the Mesh instance. Set default mesh size to zero (no vertices yet).
		this->vertexBufferObj = vbo;
		this->count = 0;
		this->size = 0;
	}

	Mesh::~Mesh() {

	}

	void Mesh::addVertexData(Vertex vert[], int count) {
		// Convert the verticies into floats which OpenGL understands
		GLfloat *vertFloats = Vertex::toFloatBuffer(vert, count);

		// Get the count of the verticies and the memory size (in bytes) of the
		// verticies (each vertex has 3 floats (x, y, z)).
		this->count = count;
		this->size = count * 3 * sizeof(GLfloat);

		// Bind the buffer to the VBO and send the data to the buffer [Statc Draw
		// indicated that data is constant].
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);
		glBufferData(GL_ARRAY_BUFFER, this->size, vertFloats, GL_STATIC_DRAW);

		delete vertFloats; // Done using the verticies floats
	}

	void Mesh::draw() {
		// Enable the position vertex attribute array
		glEnableVertexAttribArray(0);

		// Bind the buffer to the VBO and draw the data stored there.
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);

		// The positions are to be stored at 0, with each one containing 3 floats,
		// normalization is not needed, size is taken from the variable stored for
		// this mesh, and the data starts at 0.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the vertex array data as triangles, from the starting vertex to
		// the final one.
		glDrawArrays(GL_TRIANGLES, 0, this->count);

		// Disable the position vertex attribute array
		glDisableVertexAttribArray(0);
	}
}