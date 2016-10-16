#pragma once
#ifndef TEST_GAME
#define TEST_GAME

#include <string>

#include "..\..\Honeycomb GE\include\base\BaseGame.h"

namespace Honeycomb::Object { class Transform; }
namespace Honeycomb::Mesh::Importer { class Model; }
namespace Honeycomb::Mesh { class Mesh; }
namespace Honeycomb::Render { class Camera; }
namespace Honeycomb::Shader { class ShaderProgram; }

class TestGame : public Honeycomb::Base::BaseGame {
public:
	TestGame();

	~TestGame();

	void input();

	void render();

	void start();

	void update();

	int apples = 321;

private:
	std::string vertexShader =
		"..\\Honeycomb GE\\res\\shaders\\vertexShader.vs";
	std::string fragShader =
		"..\\Honeycomb GE\\res\\shaders\\fragShader.fs";
	std::string testModelCube =
		"..\\Honeycomb GE\\res\\models\\test1\\testCubeTex.obj";

	Honeycomb::Render::Camera* testCamera;
	Honeycomb::Object::Transform* testTransform;
	Honeycomb::Mesh::Importer::Model* testModel;
	Honeycomb::Mesh::Mesh* testMesh;
	Honeycomb::Shader::ShaderProgram* testShader;
};

#endif