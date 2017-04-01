#include "../../include/geometry/Vertex.h"

#include <iostream>

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;

namespace Honeycomb { namespace Geometry {
	Vertex::Vertex() {
		this->normal = Vector3f();
		this->position = Vector3f();
		this->uv = Vector2f();
		this->tangent = Vector3f();
	}

	Vertex::Vertex(const Vector3f &norm, const Vector3f &pos, 
			const Vector2f &uv, const Vector3f &tan) {
		this->normal.set(norm.getX(), norm.getY(), norm.getZ());
		this->position.set(pos.getX(), pos.getY(), pos.getZ());
		this->uv.set(uv.getX(), uv.getY());
		this->tangent.set(tan.getX(), tan.getY(), tan.getZ());
	}

	const Vector3f& Vertex::getTangent() const {
		return this->tangent;
	}

	const Vector3f& Vertex::getNormal() const {
		return this->normal;
	}

	const Vector3f& Vertex::getPosition() const {
		return this->position;
	}

	const Vector2f& Vertex::getUV() const {
		return this->uv;
	}

	void Vertex::setTangent(const Vector3f &tan) {
		this->tangent = tan;
	}

	void Vertex::setNormal(const Vector3f &norm) {
		this->normal = norm;
	}

	void Vertex::setPosition(const Vector3f &pos) {
		this->position = pos;
	}

	void Vertex::setUV(const Vector2f &uv) {
		this->uv = uv;
	}

	float* Vertex::toFloatBuffer(Vertex verts[], const int &count) {
		// The float buffer needs to store 3 floats for the position, 2 floats
		// for the texture coordinates, 3 floats for the normal of the
		// vertex and 3 floats for the tangent. 
		// (total of 3 + 2 + 3 + 3 = 11 floats for each vertex).
		float* floatBuffer = new float[count * 11];

		for (int i = 0; i < count * 11;) {
			int curVertNum = i / 11; // Current vertex number

			Vector3f curPos = verts[curVertNum].getPosition();
			Vector2f curUV = verts[curVertNum].getUV();
			Vector3f curNorm = verts[curVertNum].getNormal();
			Vector3f curTan = verts[curVertNum].getTangent();

			// Store each component of the element into the float buffer. Each 
			// time a component is copied over, the current index is increased 
			// so that the next component is copied into the next slot in the 
			// float buffer.
			floatBuffer[i++] = curPos.getX();
			floatBuffer[i++] = curPos.getY();
			floatBuffer[i++] = curPos.getZ();
			floatBuffer[i++] = curUV.getX();
			floatBuffer[i++] = curUV.getY();
			floatBuffer[i++] = curNorm.getX();
			floatBuffer[i++] = curNorm.getY();
			floatBuffer[i++] = curNorm.getZ();
			floatBuffer[i++] = curTan.getX();
			floatBuffer[i++] = curTan.getY();
			floatBuffer[i++] = curTan.getZ();
		}

		return floatBuffer; // Return the float buffer
	}
} }
