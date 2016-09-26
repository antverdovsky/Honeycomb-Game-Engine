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

#include "..\..\include\object\Transform.h"
#include "..\..\include\mesh\Vertex.h"
#include "..\..\include\mesh\Mesh.h"
#include "..\..\include\shader\ShaderProgram.h"

std::string testShaderVertexTransform = 
	"..\\Honeycomb GE\\res\\shaders\\testShader3_Transform\\vertexShader3.vert";
std::string testShaderFragTransform =
	"..\\Honeycomb GE\\res\\shaders\\testShader3_Transform\\fragmentShader3.frag";
std::string testModelCube =
	"..\\Honeycomb GE\\res\\models\\test1\\testMonkey.obj";

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Mesh::Mesh;
using Honeycomb::Mesh::Vertex;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Object::Transform;

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

		testTransform = new Transform();
		testMesh = Mesh::Mesh::loadMeshOBJ(testModelCube);
		testShader = new ShaderProgram();
		
		testShader->addShader(testShaderVertexTransform, GL_VERTEX_SHADER);
		testShader->addShader(testShaderFragTransform, GL_FRAGMENT_SHADER);
		testShader->finalizeShaderProgram();

		testShader->addUniform("transform");
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
		testMesh->draw();
		//testShader->unbindShaderProgram();
	}

	float uni_scale = 0;
	void Game::update() {
		Vector3f newPos = Vector3f(cos(Time::getGameTime() / 1000),
			sin(Time::getGameTime() / 1000), 0);
		testTransform->setTranslation(newPos);

		Vector3f newRot = Vector3f(0, sin(Time::getGameTime() / 1000), 0);
		testTransform->setRotation(newRot * 2 * 3.14159);

		Vector3f newScl = Vector3f(abs(sin(Time::getGameTime() / 1000)),
			abs(sin(Time::getGameTime() / 1000)), 
			abs(sin(Time::getGameTime() / 1000)));
		testTransform->setScale(newScl);
		
		testShader->setUniform_mat4("transform", 
			testTransform->cumulateTransformations());
	}
}