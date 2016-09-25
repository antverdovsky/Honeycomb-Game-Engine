#include <iostream>
#include <math.h>
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\base\Game.h"
#include "..\..\include\base\GameInput.h"
#include "..\..\include\base\GameTime.h"
#include "..\..\include\base\Main.h"
#include "..\..\include\file\FileIO.h"
#include "..\..\include\math\Matrix4f.h"
#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"

#include "..\..\include\mesh\Vertex.h"
#include "..\..\include\mesh\Mesh.h"
#include "..\..\include\shader\ShaderProgram.h"

std::string testShaderVertexUniform = 
	"..\\Honeycomb GE\\res\\shaders\\testShaderUniform\\vertexShader2.vert";
std::string testShaderFragUniform =
	"..\\Honeycomb GE\\res\\shaders\\testShaderUniform\\fragmentShader2.frag";
std::string testModelCube =
	"..\\Honeycomb GE\\res\\models\\test1\\testMonkey.obj";

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Mesh::Mesh;
using Honeycomb::Mesh::Vertex;
using Honeycomb::Shader::ShaderProgram;

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
		testShader = new ShaderProgram();
		
		testShader->addShader(testShaderVertexUniform, GL_VERTEX_SHADER);
		testShader->addShader(testShaderFragUniform, GL_FRAGMENT_SHADER);
		testShader->finalizeShaderProgram();

		testShader->addUniform("uni_scale");
		testShader->bindShaderProgram();
	}

	Game::~Game() {
		delete testMesh;
		delete testShader;
	}

	void Game::input() {
		Main::input->getGameInput()->clear();
	}

	void Game::render() {
		//testShader->bindShaderProgram();
		testMesh->draw();
		//testShader->unbindShaderProgram();
	}

	float uni_scale = 0;
	void Game::update() {
		uni_scale = sin(Time::getGameTime() / 1000);
		std::cout << uni_scale << std::endl;
		testShader->setUniform_f("uni_scale", uni_scale);
	}
}