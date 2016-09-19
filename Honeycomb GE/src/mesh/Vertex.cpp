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

float* Vertex::toFloatBuffer(Vertex vert[], int count) {
	// The float buffer array will store each component (total 3) for each
	// vertex (total count), therefore the float buffer must store 3 * count
	// elements.
	float *floatBuffer = new float[count * 3];

	for (int i = 0; i < count * 3; ) { // Go through the float buffer array
		// Store each component of the element into the float buffer. Each time
		// a component is copied over, the current index is incremented so that
		// the next component is copied into the next slot in the float buffer.
		floatBuffer[i++] = vert[i / 3].getPosition()->getX();
		floatBuffer[i++] = vert[i / 3].getPosition()->getY();
		floatBuffer[i++] = vert[i / 3].getPosition()->getZ();
	}

	return floatBuffer;
}