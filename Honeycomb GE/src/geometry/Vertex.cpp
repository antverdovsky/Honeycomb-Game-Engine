#include "../../include/geometry/Vertex.h"

#include <iostream>

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;

namespace Honeycomb { namespace Geometry {
	std::vector<float> Vertex::toFloatBuffer(const std::vector<Vertex> 
			&verts) {
		// Create a buffer and set its capacity to the number of elements to be
		// written to the buffer.
		std::vector<float> buffer;
		buffer.reserve(ELEMENTS_PER_ATTRIBUTE_SIZE * verts.size());

		for (int i = 0; i < verts.size(); ++i) {
			// Get the attributes of the vertex
			Vertex vertex = verts[i];
			Vector3f curPos  = vertex.getPosition();
			Vector3f curNorm = vertex.getNormal();
			Vector3f curTan  = vertex.getTangent();
			Vector2f curTC0  = vertex.getTexCoords0();

			// Push { P.x, P.y, P.z, 1.0F } for the Position Vector
			buffer.push_back(curPos.getX());
			buffer.push_back(curPos.getY());
			buffer.push_back(curPos.getZ());
			buffer.push_back(1.0F);

			// Push { N.x, N.y, N.z, 0.0F } for the Normal Vector
			buffer.push_back(curNorm.getX());
			buffer.push_back(curNorm.getY());
			buffer.push_back(curNorm.getZ());
			buffer.push_back(0.0F);

			// Push { T.x, T.y, T.z, 0.0F } for the Tangent Vector
			buffer.push_back(curTan.getX());
			buffer.push_back(curTan.getY());
			buffer.push_back(curTan.getZ());
			buffer.push_back(0.0F);

			// Push { TC0.x, TC0.y, 0.0F, 1.0F } for Texture Coords 0 Vector
			buffer.push_back(curTC0.getX());
			buffer.push_back(curTC0.getY());
			buffer.push_back(0.0F);
			buffer.push_back(1.0F);
		}

		return buffer; // Return the float buffer
	}

	Vertex::Vertex() {
		this->position = Vector3f();
		this->normal = Vector3f();
		this->tangent = Vector3f();
		this->texCoords0 = Vector2f();
	}

	Vertex::Vertex(const Vector3f &pos, const Vector3f &norm, 
			const Vector3f &tan, const Vector2f &tc0) {
		this->position = pos;
		this->normal = norm;
		this->tangent = tan;
		this->texCoords0 = tc0;
	}

	const Vector3f& Vertex::getNormal() const {
		return this->normal;
	}

	const Vector3f& Vertex::getPosition() const {
		return this->position;
	}

	const Vector3f& Vertex::getTangent() const {
		return this->tangent;
	}

	const Vector2f& Vertex::getTexCoords0() const {
		return this->texCoords0;
	}

	void Vertex::setNormal(const Vector3f &norm) {
		this->normal = norm;
	}

	void Vertex::setPosition(const Vector3f &pos) {
		this->position = pos;
	}

	void Vertex::setTangent(const Vector3f &tan) {
		this->tangent = tan;
	}

	void Vertex::setTexCoords0(const Vector2f &uv) {
		this->texCoords0 = uv;
	}
} }
