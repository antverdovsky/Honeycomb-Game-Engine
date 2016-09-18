#pragma once
#ifndef VERTEX_H
#define VERTEX_H

class Vector3f;

class Vertex {
public:
	Vertex(Vector3f pos);

	~Vertex();

	Vector3f* getPosition();
private:
	Vector3f* position;
};

#endif