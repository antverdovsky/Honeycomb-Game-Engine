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
	int Mesh::meshCount = 0;

	const int& Mesh::getInitializedMeshCount() {
		return Mesh::meshCount;
	}

	std::shared_ptr<Mesh> Mesh::newMeshShared() {
		std::shared_ptr<Mesh> ptr = std::shared_ptr<Mesh>(new Mesh());
		ptr->initialize();

		return ptr;
	}

	std::unique_ptr<Mesh> Mesh::newMeshUnique() {
		std::unique_ptr<Mesh> ptr = std::unique_ptr<Mesh>(new Mesh());
		ptr->initialize();

		return ptr;
	}

	Mesh::~Mesh() {
		if (this->isInitialized)
			this->destroy();
	}

	void Mesh::bindIndexBuffer() {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		glBindBuffer(GL_ARRAY_BUFFER, this->indexBufferObject);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::bindVertexBuffer() {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::clearIndices() {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		this->indices.clear();
		glBindBuffer(GL_ARRAY_BUFFER, this->indexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, this->indices.size() * sizeof(int),
			nullptr, GL_STATIC_DRAW);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::clearVertices() {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		this->vertices.clear();
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, 
			this->vertices.size() * Vertex::ELEMENTS_PER_VERTEX_SIZE,
			nullptr, GL_STATIC_DRAW);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::destroy() {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		
		// Placeholders to store the buffer ID for the glDeleteBuffers func.
		GLuint ibo = this->indexBufferObject;
		GLuint vbo = this->vertexBufferObject;;

		// Delete the IBO and VBO buffers
		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(1, &vbo);

		--(Mesh::meshCount);
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	const int& Mesh::getIndexBufferObject() const {
		return this->indexBufferObject;
	}

	const std::vector<unsigned int>& Mesh::getIndices() const {
		return this->indices;
	}

	const int& Mesh::getVertexBufferObject() const {
		return this->vertexBufferObject;
	}

	const std::vector<Vertex>& Mesh::getVertices() const {
		return this->vertices;
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
		this->indexBufferObject = ibo;
		this->vertexBufferObject = vbo;

		++(Mesh::meshCount);
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::render(ShaderProgram &shader) const {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		// Bind the shader program so that it may be used for drawing
		shader.bindShaderProgram();

		// Enable attribute arrays for each attribute of the vertex
		for (int i = 0; i < Vertex::ATTRIBUTES_PER_VERTEX_COUNT; ++i)
			glEnableVertexAttribArray(i);

		// Bind the buffer to the VBO.
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);

		// Set the attribute pointer for each attribute of the vertex. Since
		// all attributes are uniform in the number of elements, the same
		// count and size variables may be used for all attributes. The offset
		// will always be ELEMENTS_PER_ATTRIBUTE_SIZE from the previous attrib.
		for (int i = 0; i < Vertex::ATTRIBUTES_PER_VERTEX_COUNT; ++i)
			glVertexAttribPointer(i, Vertex::ELEMENTS_PER_ATTRIBUTE_COUNT,
				GL_FLOAT, GL_FALSE, Vertex::ELEMENTS_PER_VERTEX_SIZE,
				(void*)(Vertex::ELEMENTS_PER_ATTRIBUTE_SIZE * i));

		// Bind the buffer to the IBO.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferObject);

		// Draw the vertex array data as triangles, from the starting vertex to
		// the final one.
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT,
			(void*)0);

		// Disable attribute arrays for each attribute of the vertex
		for (int i = 0; i < Vertex::ATTRIBUTES_PER_VERTEX_COUNT; ++i)
			glDisableVertexAttribArray(i);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::setIndexData(const std::vector<unsigned int> &indices) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		// Bind the Buffer & invalidate it, in case there is already some data
		this->bindIndexBuffer();
		this->clearIndices();
		this->indices = indices;

		// Send the index data to the buffer (Static Draw indicates that the
		// data is constant).
		glBufferData(GL_ARRAY_BUFFER, this->indices.size() * sizeof(int),
			&this->indices[0], GL_STATIC_DRAW);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Mesh::setVertexData(const std::vector<Vertex> &verts) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		// Bind the Buffer & invalidate it, in case there is already some data
		this->bindVertexBuffer();
		this->clearVertices();
		this->vertices = verts;

		// Convert the verticies into a float buffer which OpenGL understands
		std::vector<float> vertFloats = Vertex::toFloatBuffer(verts);

		// Send the vertex data to the buffer (Static Draw indicates that the
		// data is constant).
		glBufferData(GL_ARRAY_BUFFER,
			this->vertices.size() * Vertex::ELEMENTS_PER_VERTEX_SIZE, 
			&vertFloats[0], GL_STATIC_DRAW);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	bool Mesh::operator==(const Mesh &rhs) const {
		return this->vertexBufferObject == rhs.vertexBufferObject &&
			this->indexBufferObject == rhs.indexBufferObject;
	}

	bool Mesh::operator!=(const Mesh &rhs) const {
		return this->vertexBufferObject != rhs.vertexBufferObject ||
			this->indexBufferObject != rhs.indexBufferObject;
	}

	Mesh::Mesh() {
		this->vertexBufferObject = -1;
		this->indexBufferObject = -1;
	}
} }
