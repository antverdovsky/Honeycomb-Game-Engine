#pragma once
#ifndef TEST_GAME
#define TEST_GAME

#include <string>

#include "..\..\Honeycomb GE\include\base\BaseGame.h"

#include "..\..\Honeycomb GE\include\object\Object.h"
#include "..\..\Honeycomb GE\include\object\Component.h"

namespace Honeycomb::Object { class Transform; }
namespace Honeycomb::Mesh::Importer { class Model; }
namespace Honeycomb::Mesh { class Mesh; }
namespace Honeycomb::Graphics { class Texture2D; }
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
private:
	std::string vertexShaderStr =
		"..\\Honeycomb GE\\res\\shaders\\default\\vertexShader.vs";
	std::string fragShaderStr =
		"..\\Honeycomb GE\\res\\shaders\\default\\fragShader.fs";
	std::string testModelCubeStr =
		"..\\Honeycomb GE\\res\\models\\default\\cube.obj";
	std::string testTextureStr =
		"..\\Honeycomb GE\\res\\textures\\default\\Checkerboard.bmp";

	/*
	Honeycomb::Render::Camera* testCamera;
	Honeycomb::Object::Transform* testTransform;
	Honeycomb::Graphics::Texture2D* testTexture;
	Honeycomb::Mesh::Importer::Model* testModel;
	Honeycomb::Mesh::Mesh* testMesh;
	Honeycomb::Shader::ShaderProgram* testShader;
	*/

	Honeycomb::Object::Object* cameraObject;
	Honeycomb::Object::Object* cubeObject;
};

#endif