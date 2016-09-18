#include <iostream>
#include <math.h>

#include <GLFW\glfw3.h>

#include "..\..\include\base\Game.h"
#include "..\..\include\io\Input.h"
#include "..\..\include\math\Matrix4f.h"
#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"

#include "..\..\include\mesh\Vertex.h"
#include "..\..\include\mesh\Mesh.h"

Game::Game() {
	Vertex data[] = {
		Vertex(Vector3f(-1, -1, 1)),
		Vertex(Vector3f(1, -1, 1)),
		Vertex(Vector3f(0, 1, 1))
	};

	m = new Mesh(data, 3);
}

Game::~Game() {

}

void Game::input() {
	Input::clear();
}

void Game::render() {
	m->draw();
}

void Game::update() {
	
}