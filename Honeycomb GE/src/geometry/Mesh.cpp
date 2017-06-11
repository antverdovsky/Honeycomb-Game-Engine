#include "../../include/geometry/Mesh.h"

#include <iostream>
#include <sstream>
#include <vector>

#include <GL/glew.h>

#include "../../include/base/GLErrorException.h"
#include "../../include/file/FileIO.h"
#include "../../include/math/Vector3f.h"
#include "../../include/geometry/Vertex.h"

using Honeycomb::Base::GLItemAlreadyInitializedException;
using Honeycomb::Base::GLItemNotInitializedException;
using Honeycomb::Base::GLErrorException;
using Honeycomb::Geometry::Vertex;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb { namespace Geometry {
	Mesh::Mesh() {
		this->vertexBufferObj = -1;
		this->vertCount = 0;
		this->vertSize = 0;
	}

	void Mesh::destroy() {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		
		// Placeholders to store the buffer ID for the glDeleteBuffers func.
		GLuint ibo = this->indexBufferObj;
		GLuint vbo = this->vertexBufferObj;;

		// Delete the IBO and VBO buffers
		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(1, &vbo);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::draw(ShaderProgram &shader) const {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		// Bind the shader program so that it may be used for drawing
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

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::initialize() {
		GLErrorException::clear();
		GLItem::initialize();

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

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::setIndexData(const std::vector<int> &indices) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		// Bind the Buffer & invalidate it, in case there is already some data
		glBindBuffer(GL_ARRAY_BUFFER, this->indexBufferObj);
		glBufferData(GL_ARRAY_BUFFER, this->indexSize, nullptr, 
			GL_STATIC_DRAW);

		// Set the count and size variables. The count represents the length of
		// the index array, where as size represents the raw size, in bytes, of
		// the index array. The total size of the array is equal to the size of
		// one integer multiplied by the amount of integers in the array.
		this->indexCount = indices.size();
		this->indexSize = indices.size() * sizeof(int);

		// Send the index data to the buffer (Static Draw indicates that the
		// data is constant).
		glBufferData(GL_ARRAY_BUFFER, this->indexSize, &indices[0],
			GL_STATIC_DRAW);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::setVertexData(const std::vector<Vertex> &verts) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		// Bind the Buffer & invalidate it, in case there is already some data
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObj);
		glBufferData(GL_ARRAY_BUFFER, this->vertSize, nullptr, GL_STATIC_DRAW);

		// Convert the verticies into a float buffer which OpenGL understands
		std::vector<float> vertFloats = Vertex::toFloatBuffer(verts);

		// Set the count and size variables.
		this->vertCount = verts.size();
		this->vertSize = Vertex::ELEMENTS_PER_VERTEX_SIZE * this->vertCount;

		// Send the vertex data to the buffer (Static Draw indicates that the
		// data is constant).
		glBufferData(GL_ARRAY_BUFFER, this->vertSize, &vertFloats[0], 
			GL_STATIC_DRAW);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}
} }
