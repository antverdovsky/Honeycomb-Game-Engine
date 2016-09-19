#include <iostream>
#include <math.h>
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\base\Game.h"
#include "..\..\include\io\Input.h"
#include "..\..\include\io\FileIO.h"
#include "..\..\include\math\Matrix4f.h"
#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"

#include "..\..\include\mesh\Vertex.h"
#include "..\..\include\mesh\Mesh.h"
#include "..\..\include\shader\Shader.h"

std::string testShaderVertex1 = 
	"..\\Honeycomb GE\\res\\shaders\\testShader1\\vertexShader1.vert";
std::string testShaderFrag1 =
	"..\\Honeycomb GE\\res\\shaders\\testShader1\\fragmentShader1.frag";

Game::Game() {
	Vertex data[] = {
		Vertex(Vector3f(-0.5F, -0.5F, 0.0F)),
		Vertex(Vector3f(0.0F, 1.0F, 0.0F)),
		Vertex(Vector3f(0.5F, -0.5F, 0.0F))
	};

	testMesh = new Mesh();
	testShader = new Shader();

	testMesh->addVertexData(data, 3);

	testShader->addShader(testShaderVertex1, GL_VERTEX_SHADER);
	testShader->addShader(testShaderFrag1, GL_FRAGMENT_SHADER);
	testShader->finalizeProgram();
}

Game::~Game() {
	delete testMesh;
	delete testShader;
}

void Game::input() {
	Input::clear();
}

void Game::render() {
	testShader->bindProgram();
	testMesh->draw();
	testShader->unbindProgram();
}

void Game::update() {

}