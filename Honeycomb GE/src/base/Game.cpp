#include <iostream>
#include <math.h>

#include <GLFW\glfw3.h>

#include "..\..\include\base\Game.h"
#include "..\..\include\base\Input.h"
#include "..\..\include\math\Matrix4f.h"
#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"

Game::Game() {
	Vector3f v1(-1, 0, 7);
	Vector3f v2(-9, 2, 3);

	Vector3f v3 = v1 + -v2;
	std::cout << v3.getX() << " , " << v3.getY() << " , " << v3.getZ() << std::endl;
}

Game::~Game() {

}

void Game::input() {
	Input::clear();
}

void Game::render() {

}

void Game::update() {

}