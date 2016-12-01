#include "..\..\include\geometry\Vertex.h"

#include <iostream>

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;

namespace Honeycomb::Geometry {
	Vertex::Vertex() {
		this->normal = Vector3f();
		this->position = Vector3f();
		this->uv = Vector2f();
	}

	Vertex::Vertex(const Vector3f &norm, const Vector3f &pos, 
			const Vector2f &uv) {
		this->normal.set(norm.getX(), norm.getY(), norm.getZ());
		this->position.set(pos.getX(), pos.getY(), pos.getZ());
		this->uv.set(uv.getX(), uv.getY());
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
		// for the texture coordinates and 3 floats for the normal of the
		// vertex (total of 8 floats for each vertex).
		float* floatBuffer = new float[count * 8];

		for (int i = 0; i < count * 8;) {
			int curVertNum = i / 8; // Current vertex number

			Vector3f curPos = verts[curVertNum].getPosition();
			Vector2f curUV = verts[curVertNum].getUV();
			Vector3f curNorm = verts[curVertNum].getNormal();

			// Store each component of the element into the float buffer. Each 
			// time a component is copied over, the current index is increased 
			// so that the next component is copied into the next slot in the 
			// float buffer.
			floatBuffer[i++] = verts[curVertNum].getPosition().getX();
			floatBuffer[i++] = verts[curVertNum].getPosition().getY();
			floatBuffer[i++] = verts[curVertNum].getPosition().getZ();
			floatBuffer[i++] = verts[curVertNum].getUV().getX();
			floatBuffer[i++] = verts[curVertNum].getUV().getY();
			floatBuffer[i++] = verts[curVertNum].getNormal().getX();
			floatBuffer[i++] = verts[curVertNum].getNormal().getY();
			floatBuffer[i++] = verts[curVertNum].getNormal().getZ();
		}

		return floatBuffer; // Return the float buffer
	}
}