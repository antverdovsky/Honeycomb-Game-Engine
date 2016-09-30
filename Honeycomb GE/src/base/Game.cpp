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
#include "..\..\include\render\Camera.h"
#include "..\..\include\object\Transform.h"
#include "..\..\include\mesh\Vertex.h"
#include "..\..\include\mesh\Mesh.h"
#include "..\..\include\shader\ShaderProgram.h"
#include "..\..\include\base\GameWindow.h"

std::string vertexShader = 
	"..\\Honeycomb GE\\res\\shaders\\vertexShader.vs";
std::string fragShader =
	"..\\Honeycomb GE\\res\\shaders\\fragShader.fs";
std::string testModelCube =
	"..\\Honeycomb GE\\res\\models\\test1\\testCube.obj";

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Mesh::Mesh;
using Honeycomb::Mesh::Vertex;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Object::Transform;
using Honeycomb::Render::Camera;

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
		testCamera = new Camera(100.0F, 0.3F, 90, 600, 800);
		testMesh = Mesh::Mesh::loadMeshOBJ(testModelCube);
		testShader = new ShaderProgram();
		
		testShader->addShader(vertexShader, GL_VERTEX_SHADER);
		testShader->addShader(fragShader, GL_FRAGMENT_SHADER);
		testShader->finalizeShaderProgram();

		testShader->addUniform("transform");
		//testShader->addUniform("projection");
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
		
		Vector3f newPos = Vector3f(//cos(Time::getGameTime() / 1000) / 2,
			//5 * sin(Time::getGameTime() / 1000),
			//5 * sin(Time::getGameTime() / 1000),
			0, 0, -4);
			//0, 0, -20 * abs(sin(Time::getGameTime() / 1000))); //-abs(5 * sin(Time::getGameTime() / 3000)));
		testTransform->setTranslation(newPos);
		

		Vector3f newRot = Vector3f(0, ///sin(Time::getGameTime() / 1000),
			sin(Time::getGameTime() / 5000),
			0); ///sin(Time::getGameTime() / 1000));
		testTransform->rotate(Vector3f(0.001F, 0.001F, 0.001F));

		
		Vector3f newScl = Vector3f(//2 * sin(Time::getGameTime() / 3000), 
			//2 * sin(Time::getGameTime() / 3000), 
			//2 * sin(Time::getGameTime() / 3000));
			1, 1, 1);
		testTransform->setScale(Vector3f(1, 1, 1));
		
		Matrix4f camMat = testCamera->getProjection();
		Matrix4f transMat = testTransform->modelTransformation();
		Matrix4f finalMat = camMat * transMat;

		//testShader->setUniform_mat4("projection",
		//	*testCamera->getProjection());
		testShader->setUniform_mat4("transform", 
			finalMat);
	}
}