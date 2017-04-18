#include "../../include/geometry/Mesh.h"

#include <iostream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../include/file/FileIO.h"
#include "../../include/math/Vector3f.h"
#include "../../include/geometry/Vertex.h"

using Honeycomb::Geometry::Vertex;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb { namespace Geometry {
	bool Mesh::initialize() {
		if (this->isInitialized) return false;

		// Placeholders to store the buffer ID after the glGenBuffers func.
		GLuint ibo = 0;
		GLuint vbo = 0;

		// Generate the IBO and VBO buffers
		glGenBuffers(1, &ibo);
		glGenBuffers(1, &vbo);

		// Initialize the IBO buffer information of this Mesh to default
		this->indexBufferObj = ibo;
		this->indexCount = 0;
		this->indexSize = 0;

		// Initialize the VBO buffer information of this Mesh to default
		this->vertexBufferObj = vbo;
		this->vertCount = 0;
		this->vertSize = 0;

		// Success!
		this->isInitialized = true;
		return true;
	}

	void Mesh::destroy() {
		// Placeholders to store the buffer ID for the glDeleteBuffers func.
		GLuint ibo = this->indexBufferObj;
		GLuint vbo = this->vertexBufferObj;;

		// Delete the IBO and VBO buffers
		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(1, &vbo);
	}
	
	void Mesh::draw(ShaderProgram &shader) const {
		shader.bindShaderProgram();

		// Enable attribute arrays for each attribute of the vertex
		for (int i = 0; i < Vertex::ATTRIBUTES_PER_VERTEX_COUNT; ++i)
			glEnableVertexAttribArray(i);

		// Bind the buffer to the VBO.
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);

		// Set the attribute pointer for each attribute of the vertex. Since
		// all attributes are uniform in the number of elements, the same
		// count and size variables may be used for all attributes. The offset
		// will always be ELEMENTS_PER_ATTRIBUTE_SIZE from the previous attrib.
		for (int i = 0; i < Vertex::ATTRIBUTES_PER_VERTEX_COUNT; ++i)
			glVertexAttribPointer(i, Vertex::ELEMENTS_PER_ATTRIBUTE_COUNT, 
				GL_FLOAT, GL_FALSE, Vertex::ELEMENTS_PER_VERTEX_SIZE,
				(void*)(Vertex::ELEMENTS_PER_ATTRIBUTE_SIZE * i));

		// Bind the buffer to the IBO.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferObj);

		// Draw the vertex array data as triangles, from the starting vertex to
		// the final one.
		glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 
			(void*)0);

		// Disable attribute arrays for each attribute of the vertex
		for (int i = 0; i < Vertex::ATTRIBUTES_PER_VERTEX_COUNT; ++i)
			glDisableVertexAttribArray(i);
	}

	void Mesh::setIndexData(int indices[], const int &iC) {
		// Bind the Buffer & invalidate it, in case there is already some data
		glBindBuffer(GL_ARRAY_BUFFER, this->indexBufferObj);
		glBufferData(GL_ARRAY_BUFFER, this->indexSize, nullptr, 
			GL_STATIC_DRAW);

		// Set the count and size variables. The count represents the length of
		// the index array, where as size represents the raw size, in bytes, of
		// the index array. The total size of the array is equal to the size of
		// one integer multiplied by the amount of integers in the array.
		this->indexCount = iC;
		this->indexSize = iC * sizeof(int);

		// Send the index data to the buffer (Static Draw indicates that the
		// data is constant).
		glBufferData(GL_ARRAY_BUFFER, this->indexSize, &indices[0],
			GL_STATIC_DRAW);
	}

	void Mesh::setVertexData(Vertex vert[], const int &vC) {
		// Bind the Buffer & invalidate it, in case there is already some data
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);
		glBufferData(GL_ARRAY_BUFFER, this->vertSize, nullptr, GL_STATIC_DRAW);

		// Convert the verticies into a float buffer which OpenGL understands
		std::vector<float> vertFloats = Vertex::toFloatBuffer(vert, vC);

		// Set the count and size variables.
		this->vertCount = vC;
		this->vertSize = Vertex::ELEMENTS_PER_VERTEX_SIZE * this->vertCount;

		// Send the vertex data to the buffer (Static Draw indicates that the
		// data is constant).
		glBufferData(GL_ARRAY_BUFFER, this->vertSize, &vertFloats[0], 
			GL_STATIC_DRAW);
	}
} }
