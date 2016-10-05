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
#include "..\..\include\math\Quaternion.h"
#include "..\..\include\render\Camera.h"
#include "..\..\include\object\Transform.h"
#include "..\..\include\mesh\Vertex.h"
#include "..\..\include\mesh\Mesh.h"
#include "..\..\include\shader\ShaderProgram.h"
#include "..\..\include\base\GameWindow.h"
#include "..\..\include\math\MathUtils.h"

std::string vertexShader = 
	"..\\Honeycomb GE\\res\\shaders\\vertexShader.vs";
std::string fragShader =
	"..\\Honeycomb GE\\res\\shaders\\fragShader.fs";
std::string testModelCube =
	"..\\Honeycomb GE\\res\\models\\test1\\testCar.obj";

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Quaternion;
using Honeycomb::Mesh::Mesh;
using Honeycomb::Mesh::Vertex;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Object::Transform;
using Honeycomb::Render::Camera;
using namespace Honeycomb::Math::Utils;

namespace Honeycomb::Base {
	Game::Game() {
		float camW = GameWindow::getGameWindow()->getWindowWidth();
		float camH = GameWindow::getGameWindow()->getWindowHeight();

		testTransform = new Transform(Vector3f(), Quaternion(), Vector3f(1, 1, 1));
		testCamera = new Camera(Camera::CameraType::PERSPECTIVE, 100.0F, 0.3F,
			60.0F, camH, camW, Transform(Vector3f(), Quaternion(), Vector3f(1, 1, 1)));
		testMesh = Mesh::Mesh::loadMeshOBJ(testModelCube);
		testShader = new ShaderProgram();

		testTransform->setTranslation(Vector3f(0, 0, 10));

		testShader->addShader(vertexShader, GL_VERTEX_SHADER);
		testShader->addShader(fragShader, GL_FRAGMENT_SHADER);
		testShader->finalizeShaderProgram();

		testShader->addUniform("camProjection");
		testShader->addUniform("camOrientation");
		testShader->addUniform("camTranslation");
		testShader->addUniform("objTransform");
		testShader->bindShaderProgram();

		testShader->setUniform_mat4("camProjection",
			testCamera->getProjection());

		GameInput::getGameInput()->clear();
	}

	Game::~Game() {
		delete testMesh;
		delete testShader;
	}

	void Game::input() {
		float speed = 0.0025F;
		
		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_Z)) { // rot transform
			this->testTransform->rotate(this->testTransform->getLocalUp(),
				-0.075F);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_X)) {
			this->testTransform->rotate(this->testTransform->getLocalRight(),
				-0.075F);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_C)) {
			this->testTransform->rotate(this->testTransform->getLocalForward(),
				-0.075F);
		}
		
		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_W)) { // move forward
			this->testCamera->getTransform().translate(
				this->testCamera->getTransform().getLocalForward() * speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_S)) { // move back
			this->testCamera->getTransform().translate(
				-this->testCamera->getTransform().getLocalForward() * speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_A)) { // move left
			this->testCamera->getTransform().translate(
				-this->testCamera->getTransform().getLocalRight() * speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_D)) { // move right
			this->testCamera->getTransform().translate(
				this->testCamera->getTransform().getLocalRight() * speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_UP)) { // move up
			this->testCamera->getTransform().translate(
				this->testCamera->getTransform().getLocalUp() * speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_DOWN)) { // move down
			this->testCamera->getTransform().translate(
				-this->testCamera->getTransform().getLocalUp() * speed * Time::deltaTime
			);
		}


		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_J)) { // rotate left
			this->testCamera->getTransform().rotate(
				-this->testCamera->getTransform().getLocalUp(), speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_K)) { // rotate right
			this->testCamera->getTransform().rotate(
				this->testCamera->getTransform().getLocalUp(), speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_U)) { // rotate up
			this->testCamera->getTransform().rotate(
				-this->testCamera->getTransform().getLocalRight(),  speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_I)) { // rotate down
			this->testCamera->getTransform().rotate(
				this->testCamera->getTransform().getLocalRight(), speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_N)) { // tilt left
			this->testCamera->getTransform().rotate(
				-this->testCamera->getTransform().getLocalForward(), speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_M)) { // tilt right
			this->testCamera->getTransform().rotate(
				this->testCamera->getTransform().getLocalForward(), speed * Time::deltaTime
			);
		}

		if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_R)) { // reset cam
			this->testTransform->setRotation(
				Quaternion()
			);

			this->testCamera->getTransform().setTranslation(
				Vector3f()
			);

			this->testCamera->getTransform().setRotation(Quaternion(Vector3f::getGlobalUp(), -PI));
		}

		GameInput::getGameInput()->clear();
	}

	void Game::render() {
		testMesh->draw();
		//testShader->unbindShaderProgram();
	}

	float uni_scale = 0;
	int counter = 0;
	void Game::update() {
		counter++;
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

			Vector3f camPos = testCamera->getTransform().getTranslation();
			std::cout << "CAM POS: " << camPos.getX() << ", " << camPos.getY() << ", " << camPos.getZ() << std::endl;
		}

		testTransform->translate(testTransform->getLocalForward() * 0.005F);

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

		//testTransform->translate(testCamera->getTransform().getLocalUp() * 0.001F);

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
		
		Matrix4f camOrien = testCamera->getTransform().getRotationMatrix();
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
		
		testShader->setUniform_mat4("objTransform", objTransf);
		testShader->setUniform_mat4("camOrientation", camOrien);
		testShader->setUniform_mat4("camTranslation", camTransl);
	}
}