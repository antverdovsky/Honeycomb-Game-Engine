#include "..\..\include\mesh\Vertex.h"

#include "..\..\include\math\Vector3f.h"


Vertex::Vertex(Vector3f pos) {
	this->position = new Vector3f(pos.getX(), pos.getY(), pos.getZ());
}

Vertex::~Vertex() {
	delete this->position;
}

Vector3f* Vertex::getPosition() {
	return this->position;
}