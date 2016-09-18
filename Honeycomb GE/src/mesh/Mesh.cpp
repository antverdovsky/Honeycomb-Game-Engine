#include "..\..\include\mesh\Mesh.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Mesh::Mesh(Vertex vert[], int count) {
	// Initialize a buffer and store the Vertex Buffer Object in a GLuint.
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);

	// Convert GLuint to a regular integer and copy to the vertex buffer in
	// the Mesh instance. Set default mesh size to zero (no vertices yet).
	this->vertexBufferObj = vbo;
	this->count = count;
	this->size = count * 3;

	// Add the vertex data to this mesh.
	this->addVertexData(vert, count);
}

Mesh::~Mesh() {

}

void Mesh::draw() {
	// Enable special vertex object pointer interpretation
	glEnableVertexAttribArray(0);

	// Bind the buffer to the VBO and draw the data stored there.
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);

	// The vertices to be drawn start at index 0, and go to index 3 (x, y, z),
	// are represented by floats, normalization is not needed, size is taken
	// from the variable stored for this mesh, and the data starts at 0.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the vertex array data as triangles, from the starting vertex to
	// the final one.
	glDrawArrays(GL_TRIANGLES, 0, this->count);

	// Disable special vertex object pointer interpretation
	glDisableVertexAttribArray(0);
}

void Mesh::addVertexData(Vertex vert[], int count) {
	// Bind the buffer to the VBO and send the data to the buffer [Statc Draw
	// indicated that data is constant].
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, this->size, vert, GL_STATIC_DRAW);
}