#include <iostream>
#include <math.h>
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\base\Game.h"
#include "..\..\include\base\GameInput.h"
#include "..\..\include\base\Main.h"
#include "..\..\include\file\FileIO.h"
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
std::string testModelCube =
	"..\\Honeycomb GE\\res\\models\\test1\\testMonkey.obj";

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Mesh::Mesh;
using Honeycomb::Mesh::Vertex;
using Honeycomb::Shader::Shader;

namespace Honeycomb::Base {
	Game::Game() {
		/*
		Vertex data[] = {
			Vertex(Vector3f(-0.5F, 0.5F, 0.0F)),
			Vertex(Vector3f(0.5F, 0.5F, 0.0F)),
			Vertex(Vector3f(0.5F, -0.5F, 0.0F)),
			Vertex(Vector3f(-0.5F, -0.5F, 0.0F))

			//Vertex(Vector3f(0.5, -0.5F, -1.0F)),
			//Vertex(Vector3f(-0.5F, -0.5F, -1.0F)),
			//Vertex(Vector3f(-0.5, 0.5F, -1.0F))
		};

		int indicies[] = {
			0, 1, 2,
			2, 3, 0
		};
		*/

		testMesh = Mesh::Mesh::loadMeshOBJ(testModelCube);
		testShader = new Shader::Shader();

		testShader->addShader(testShaderVertex1, GL_VERTEX_SHADER);
		testShader->addShader(testShaderFrag1, GL_FRAGMENT_SHADER);
		testShader->finalizeProgram();
	}

	Game::~Game() {
		delete testMesh;
		delete testShader;
	}

	void Game::input() {
		Main::input->getGameInput()->clear();
	}

	void Game::render() {
		testShader->bindProgram();
		testMesh->draw();
		testShader->unbindProgram();
	}

	void Game::update() {

	}
}