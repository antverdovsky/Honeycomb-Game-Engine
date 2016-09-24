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

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Mesh::Mesh;
using Honeycomb::Mesh::Vertex;
using Honeycomb::Shader::Shader;

namespace Honeycomb::Base {
	Game::Game() {
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

		testMesh = new Mesh::Mesh();
		testShader = new Shader::Shader();

		testMesh->addVertexData(data, 4, indicies, 6);

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