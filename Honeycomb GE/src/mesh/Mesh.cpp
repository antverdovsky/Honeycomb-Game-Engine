#include "..\..\include\mesh\Mesh.h"

#include <iostream>
#include <sstream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\file\FileIO.h"
#include "..\..\include\math\Vector3f.h"
#include "..\..\include\mesh\Vertex.h"
#include "..\..\include\mesh\importer\Model.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Mesh::Vertex;
using Honeycomb::Mesh::Importer::Model;

namespace Honeycomb::Mesh {
	Mesh::Mesh() {
		// Initialize a Vertex Buffer Object and store it
		GLuint vbo = 0;
		glGenBuffers(1, &vbo);

		// Initialize a Index Buffer Object and store it
		GLuint ibo = 0;
		glGenBuffers(1, &ibo);

		// Copy the VBO and IBO pointers into the mesh instance. Set default 
		// mesh size to zero (no vertices or indicies yet).
		this->vertexBufferObj = vbo;
		this->vertCount = 0;
		this->vertSize = 0;
		this->indexBufferObj = ibo;
		this->indexCount = 0;
		this->indexSize = 0;
	}

	Mesh::Mesh(Model m) : Mesh() {
		this->addVertexData(&m.getVerticies()[0], m.getVerticies().size(),
			&m.getIndicies()[0], m.getIndicies().size());
	}

	Mesh::~Mesh() {

	}

	void Mesh::addVertexData(Vertex vert[], int vertCount, int index[],
			int indexCount) {
		// Convert the verticies into floats which OpenGL understands
		GLfloat *vertFloats = Vertex::verticiesToFloatBuffer(vert, vertCount);

		// Get the count of the verticies and the memory size (in bytes) of the
		// verticies (each vertex has 3 floats (x, y, z)).
		this->vertCount = vertCount;
		this->vertSize = vertCount * 3 * sizeof(GLfloat);

		// Get the count of indicies and their memory size
		this->indexCount = indexCount;
		this->indexSize = indexCount * sizeof(int);

		// Bind the buffer to the VBO and send the vertex data to the buffer 
		// [Static Draw indicates that data is constant].
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);
		glBufferData(GL_ARRAY_BUFFER, this->vertSize, &vertFloats[0], 
			GL_STATIC_DRAW);

		// Bind the buffer to the IBO and send the index data to the buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferObj);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexSize, &index[0], 
			GL_STATIC_DRAW);
		
		delete vertFloats; // Done using the verticies floats
	}

	void Mesh::draw() {
		// Enable the position vertex attribute array
		glEnableVertexAttribArray(0);

		// Bind the buffer to the VBO.
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);

		// The positions are to be stored at 0, with each one containing 3 
		// floats per face, normalization is not needed, size is taken from the
		// variable stored for this mesh, and the data starts at 0.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Bind the buffer to the IBO.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferObj);

		// Draw the vertex array data as triangles, from the starting vertex to
		// the final one.
		glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 
			(void*)0);

		// Disable the position vertex attribute array
		glDisableVertexAttribArray(0);
	}
}