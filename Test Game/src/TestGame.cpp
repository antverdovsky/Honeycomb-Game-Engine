#include "..\include\TestGame.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\Honeycomb GE\include\base\BaseGame.h"
#include "..\..\Honeycomb GE\include\base\GameInput.h"
#include "..\..\Honeycomb GE\include\base\GameTime.h"
#include "..\..\Honeycomb GE\include\base\BaseMain.h"
#include "..\..\Honeycomb GE\include\file\FileIO.h"
#include "..\..\Honeycomb GE\include\math\Matrix4f.h"
#include "..\..\Honeycomb GE\include\math\Vector2f.h"
#include "..\..\Honeycomb GE\include\math\Vector3f.h"
#include "..\..\Honeycomb GE\include\math\Quaternion.h"
#include "..\..\Honeycomb GE\include\render\Camera.h"
#include "..\..\Honeycomb GE\include\object\Transform.h"
#include "..\..\Honeycomb GE\include\mesh\Mesh.h"
#include "..\..\Honeycomb GE\include\mesh\Vertex.h"
#include "..\..\Honeycomb GE\include\mesh\importer\Model.h"
#include "..\..\Honeycomb GE\include\mesh\importer\Model_OBJ.h"
#include "..\..\Honeycomb GE\include\shader\ShaderProgram.h"
#include "..\..\Honeycomb GE\include\base\GameWindow.h"
#include "..\..\Honeycomb GE\include\math\MathUtils.h"
#include "..\..\Honeycomb GE\include\graphics\Texture2D.h"

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Mesh::Vertex;
using Honeycomb::Math::Quaternion;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Mesh::Mesh;
using Honeycomb::Mesh::Importer::Model;
using Honeycomb::Mesh::Importer::Model_OBJ;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Object::Transform;
using Honeycomb::Render::Camera;

using namespace Honeycomb::File;
using namespace Honeycomb::Base::Time;
using namespace Honeycomb::Math::Utils;

using Honeycomb::Base::GameInput;
using Honeycomb::Base::GameWindow;

TestGame::TestGame() {

}

TestGame::~TestGame() {
	delete testMesh;
	delete testShader;
}

bool wireframe = false;
void TestGame::input() {
	float speed = 0.0025F;

	if (GameInput::getGameInput()->getKeyReleased(GLFW_KEY_P)) { // wireframe
		wireframe = !wireframe;
		
		if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_Z)) { // rot transform
		this->testTransform->rotate(this->testTransform->getLocalUp(),
			0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_X)) {
		this->testTransform->rotate(this->testTransform->getLocalRight(),
			-0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_C)) {
		this->testTransform->rotate(this->testTransform->getLocalForward(),
			-0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_Q)) {
		this->testTransform->translate(this->testTransform->getLocalForward()
			* 0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_E)) {
		this->testTransform->translate(this->testTransform->getLocalRight()
			* 0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_W)) { // move forward
		this->testCamera->getTransform().translate(
			this->testCamera->getTransform().getLocalForward() * speed * 
				Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_S)) { // move back
		this->testCamera->getTransform().translate(
			-this->testCamera->getTransform().getLocalForward() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_A)) { // move left
		this->testCamera->getTransform().translate(
			-this->testCamera->getTransform().getLocalRight() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_D)) { // move right
		this->testCamera->getTransform().translate(
			this->testCamera->getTransform().getLocalRight() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_UP)) { // move up
		this->testCamera->getTransform().translate(
			this->testCamera->getTransform().getLocalUp() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_DOWN)) { // move down
		this->testCamera->getTransform().translate(
			-this->testCamera->getTransform().getLocalUp() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}


	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_J)) { // rotate left
		this->testCamera->getTransform().rotate(
			this->testCamera->getTransform().getLocalUp(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_K)) { // rotate right
		this->testCamera->getTransform().rotate(
			-this->testCamera->getTransform().getLocalUp(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_U)) { // rotate up
		this->testCamera->getTransform().rotate(
			this->testCamera->getTransform().getLocalRight(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_I)) { // rotate down
		this->testCamera->getTransform().rotate(
			-this->testCamera->getTransform().getLocalRight(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_N)) { // tilt left
		this->testCamera->getTransform().rotate(
			this->testCamera->getTransform().getLocalForward(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_M)) { // tilt right
		this->testCamera->getTransform().rotate(
			-this->testCamera->getTransform().getLocalForward(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_R)) { // reset cam
		this->testTransform->setRotation(
			Quaternion()
		);

		this->testCamera->getTransform().setTranslation(
			Vector3f()
		);

		this->testCamera->getTransform().setRotation(Quaternion(Vector3f::getGlobalUp(), PI));
	}

	GameInput::getGameInput()->clear();
}

void TestGame::render() {
	testTexture->bind();
	testMesh->draw();
	//testShader->unbindShaderProgram();
} 

void TestGame::start() {
	float camW = GameWindow::getGameWindow()->getWindowWidth();
	float camH = GameWindow::getGameWindow()->getWindowHeight();

	testTransform = new Transform(Vector3f(), Quaternion(), Vector3f(1, 1, 1));
	testCamera = new Camera(Camera::CameraType::PERSPECTIVE, 100.0F, 0.3F,
		60, camH, camW, Transform(Vector3f(),
			Quaternion(Vector3f::getGlobalUp(), PI), Vector3f(1, 1, 1)));
	testModel = Model_OBJ::loadModel(testModelCubeStr);
	testMesh = new Mesh(*testModel);
	testShader = new ShaderProgram();
	testTexture = new Texture2D();

	int testTextureWidth = 0;
	int testTextureHeight = 0;
	unsigned char* testTextureData = readImageToUChar(
		testTextureStr, testTextureWidth, testTextureHeight);
	testTexture->setImageData(testTextureData, GL_RGB, GL_RGB, testTextureWidth,
		testTextureHeight);
	//testTexture->setTextureFiltering(GL_NEAREST, GL_NEAREST);
	testTexture->genMipMap();

	testTransform->setTranslation(Vector3f(0, 0, -10));

	testShader->addShader(vertexShaderStr, GL_VERTEX_SHADER);
	testShader->addShader(fragShaderStr, GL_FRAGMENT_SHADER);
	testShader->finalizeShaderProgram();

	testShader->addUniform("camProjection");
	testShader->addUniform("camOrientation");
	testShader->addUniform("camTranslation");
	testShader->addUniform("objTransform");
	testShader->bindShaderProgram();

	testShader->setUniform_mat4("camProjection",
		testCamera->getProjection());

	delete testModel;
	GameInput::getGameInput()->clear();
}
	
float uni_scale = 0;
int counter = 0;
void TestGame::update() {
	counter++;

	//testTransform->translate(testTransform->getLocalForward() * 0.005F);

	//testTransform->rotate(testTransform->getLocalUp(), -0.025F);

	//testTransform->translate(testTransform->getLocalForward().cross(testTransform->getLocalUp()) * 0.005F);
	//testTransform->translate(testTransform->getLocalForward() * 0.005F);

	//testTransform->rotate(Vector3f(1, 1, 1) * 0.01F);
	//testTransform->translate(testTransform->getLocalForward() * 0.0025F);

	//testTransform->setTranslation(Vector3f(0, 0, 10 * cos(Time::getGameTime() / 1000)));
	/*

	// verify rotations and translations.................................
	testCamera->getTransform().setTranslation(Vector3f(
	10 * sin(Time::getGameTime() / 1000),
	10 * sin(Time::getGameTime() / 1000),
	10 * sin(Time::getGameTime() / 1000)
	));
	*/

	//testTransform->translate(testTransform->getLocalForward() * 0.02F);

	/// all transform movement/rotation works...
	//testTransform->translate(testTransform->getLocalUp() * 0.005F);
	//testTransform->translate(testTransform->getLocalRight() * 0.005F);
	//testTransform->translate(testTransform->getLocalForward() * 0.005F);

	//testTransform->setTranslation(Vector3f(0, 0, 10 * cos(Time::getGameTime() / 200)));

	/// none camera movement works... but rotation does
	//testCamera->getTransform().translate(testCamera->getTransform().getLocalUp() * 0.005F);

	//testCamera->getTransform().translate(testCamera->getTransform().getLocalUp() * 0.005F);
	//testCamera->getTransform().rotate(Vector3f( 0.0F, 0.001F, 0.0F ));

	//testTransform->translate(testTransform->getLocalRight() * 0.001F);
	//testTransform->translate(Vector3f(0.01F, 0.0F, 0.0F));
	//testCamera->getTransform().translate(Vector3f(0.01F, 0.0F, 0.0F));
	// works:  testCamera->getTransform().translate(testCamera->getTransform().getLocalForward() * 0.005F);
	// doesnt: testCamera->getTransform().translate(testCamera->getTransform().getLocalUp() * 0.001F);
	Vector3f newCameraPos = testCamera->getTransform().getTranslation();
	Vector3f newObjectPos = testTransform->getTranslation();

	Matrix4f objTransf = testTransform->getTransformationMatrix();
	Matrix4f camProj = testCamera->getProjection();

	Matrix4f camOrien = testCamera->getTransform().getOrientationMatrix();
	camOrien.setAt(2, 0, -camOrien.getAt(2, 0));
	camOrien.setAt(2, 1, -camOrien.getAt(2, 1));
	camOrien.setAt(2, 2, -camOrien.getAt(2, 2));


	// negative since everything in the world moves opposite of the way
	// the camera would move.
	Matrix4f camTransl = Matrix4f::identity();
	camTransl.setAt(0, 0, 1);
	camTransl.setAt(1, 1, 1);
	camTransl.setAt(2, 2, 1);
	camTransl.setAt(3, 3, 1);
	camTransl.setAt(0, 3, -testCamera->getTransform().getTranslationMatrix().getAt(0, 3)); // x
	camTransl.setAt(1, 3, -testCamera->getTransform().getTranslationMatrix().getAt(1, 3)); // y
	camTransl.setAt(2, 3, -testCamera->getTransform().getTranslationMatrix().getAt(2, 3)); // z

	Matrix4f finalNotWokring = camProj * camOrien * camTransl * objTransf;
	Matrix4f finalWorking = camProj * objTransf;

	if (counter % 60 == 0) {
		Vector3f transF = testTransform->getLocalForward();
		std::cout << "TRS FORW: " << transF.getX() << ", " << transF.getY() << ", " << transF.getZ() << std::endl;

		Vector3f transR = testTransform->getLocalRight();
		std::cout << "TRS RIGHT: " << transR.getX() << ", " << transR.getY() << ", " << transR.getZ() << std::endl;

		Vector3f transU = testTransform->getLocalUp();
		std::cout << "TRS UP: " << transU.getX() << ", " << transU.getY() << ", " << transU.getZ() << std::endl;

		Vector3f camF = testCamera->getTransform().getLocalForward();
		std::cout << "CAM FOR: " << camF.getX() << ", " << camF.getY() << ", " << camF.getZ() << std::endl;

		Vector3f camR = testCamera->getTransform().getLocalRight();
		std::cout << "CAM RIGHT: " << camR.getX() << ", " << camR.getY() << ", " << camR.getZ() << std::endl;

		Vector3f camU = testCamera->getTransform().getLocalUp();
		std::cout << "CAM UP: " << camU.getX() << ", " << camU.getY() << ", " << camU.getZ() << std::endl;

		Quaternion q = testTransform->getRotation();
		std::cout << "TRANS ROT: ";
		std::cout << q.getX() << ", " << q.getY() << ", " << q.getZ() << ", "
			<< q.getW() << std::endl;

		q = testCamera->getTransform().getRotation();
		std::cout << "CAM ROT: ";
		std::cout << q.getX() << ", " << q.getY() << ", " << q.getZ() << ", "
			<< q.getW() << std::endl;

		std::cout << "CAMERA ORIENTATION: " << std::endl;
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				std::cout << camOrien.getAt(r, c) << " | ";
			}

			std::cout << std::endl;
		}

		std::cout << "OBJECT ORIENTATION: " << std::endl;
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				std::cout << testTransform->getRotationMatrix().getAt(r, c) << " | ";
			}

			std::cout << std::endl;
		}
	}

	testShader->setUniform_mat4("objTransform", objTransf);
	testShader->setUniform_mat4("camOrientation", camOrien);
	testShader->setUniform_mat4("camTranslation", camTransl);
}