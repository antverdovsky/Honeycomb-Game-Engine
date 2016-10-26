#include "..\include\TestGame.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\Honeycomb GE\include\mesh\MeshRenderer.h"
#include "..\..\Honeycomb GE\include\object\Object.h"
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

}

bool wireframe = false;
void TestGame::input() {
	float speed = 0.0025F;

	std::vector<Honeycomb::Object::Component*> allComponentsCube =
		cubeObject->getComponents();
	Honeycomb::Object::Component* compFound2 = cubeObject->getComponents().at(1);
	Honeycomb::Object::Component* compFound = cubeObject->getComponent("Transform");

	Honeycomb::Object::Transform& cubeObjectTransform =
		dynamic_cast<Honeycomb::Object::Transform&>(*compFound);

	Honeycomb::Render::Camera& cameraObjectCamera =
		dynamic_cast<Honeycomb::Render::Camera&>(*cameraObject->getComponent("Camera"));


	if (GameInput::getGameInput()->getKeyReleased(GLFW_KEY_P)) { // wireframe
		wireframe = !wireframe;
		
		if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_Z)) { // rot transform
		cubeObjectTransform.rotate(cubeObjectTransform.getLocalUp(),
			0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_X)) {
		 cubeObjectTransform.rotate( cubeObjectTransform.getLocalRight(),
			-0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_C)) {
		 cubeObjectTransform.rotate( cubeObjectTransform.getLocalForward(),
			-0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_Q)) {
		 cubeObjectTransform.translate( cubeObjectTransform.getLocalForward()
			* 0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_E)) {
		 cubeObjectTransform.translate( cubeObjectTransform.getLocalRight()
			* 0.075F);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_W)) { // move forward
		cameraObjectCamera.getTransform().translate(
			cameraObjectCamera.getTransform().getLocalForward() * speed * 
				Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_S)) { // move back
		cameraObjectCamera.getTransform().translate(
			-cameraObjectCamera.getTransform().getLocalForward() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_A)) { // move left
		cameraObjectCamera.getTransform().translate(
			-cameraObjectCamera.getTransform().getLocalRight() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_D)) { // move right
		cameraObjectCamera.getTransform().translate(
			cameraObjectCamera.getTransform().getLocalRight() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_UP)) { // move up
		cameraObjectCamera.getTransform().translate(
			cameraObjectCamera.getTransform().getLocalUp() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_DOWN)) { // move down
		cameraObjectCamera.getTransform().translate(
			-cameraObjectCamera.getTransform().getLocalUp() * speed * 
			Honeycomb::Base::Time::deltaTime
		);
	}


	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_J)) { // rotate left
		cameraObjectCamera.getTransform().rotate(
			cameraObjectCamera.getTransform().getLocalUp(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_K)) { // rotate right
		cameraObjectCamera.getTransform().rotate(
			-cameraObjectCamera.getTransform().getLocalUp(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_U)) { // rotate up
		cameraObjectCamera.getTransform().rotate(
			cameraObjectCamera.getTransform().getLocalRight(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_I)) { // rotate down
		cameraObjectCamera.getTransform().rotate(
			-cameraObjectCamera.getTransform().getLocalRight(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_N)) { // tilt left
		cameraObjectCamera.getTransform().rotate(
			cameraObjectCamera.getTransform().getLocalForward(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_M)) { // tilt right
		cameraObjectCamera.getTransform().rotate(
			-cameraObjectCamera.getTransform().getLocalForward(), speed * Honeycomb::Base::Time::deltaTime
		);
	}

	if (GameInput::getGameInput()->getKeyDown(GLFW_KEY_R)) { // reset cam
		 cubeObjectTransform.setRotation(
			Quaternion()
		);

		cameraObjectCamera.getTransform().setTranslation(
			Vector3f()
		);

		cameraObjectCamera.getTransform().setRotation(Quaternion(Vector3f::getGlobalUp(), PI));
	}

	GameInput::getGameInput()->clear();
}

void TestGame::render() {
	Honeycomb::Object::Object::getRoot()->render();
} 

void TestGame::start() {
	///
	/// Now Entering Trigger Free Zone
	/// 
	/*
	std::vector<Honeycomb::Object::Component*> myComponents;
	Honeycomb::Object::Component* myTransformComponent =
		new Honeycomb::Object::Transform();
	Honeycomb::Object::Component* myMeshRenderComponent =
		new Honeycomb::Mesh::MeshRenderer(Mesh(), ShaderProgram(), Texture2D());
	myComponents.push_back(myTransformComponent); // at 0
	myComponents.push_back(myMeshRenderComponent); // at 1
	Honeycomb::Object::Transform& myTransformComponentDowncast =
		dynamic_cast<Honeycomb::Object::Transform&>(*myComponents.at(0));
	Honeycomb::Mesh::MeshRenderer& myMeshRenderComponentDowncast =
		dynamic_cast<Honeycomb::Mesh::MeshRenderer&>(*myComponents.at(1));
	*/
	///
	/// Now Departing Trigger Free Zone
	///

	float camW = GameWindow::getGameWindow()->getWindowWidth();
	float camH = GameWindow::getGameWindow()->getWindowHeight();

	Mesh cubeMesh = Mesh(*Model_OBJ::loadModel(testModelCubeStr)); // todo delete model
	ShaderProgram cubeShader = ShaderProgram();
	
	cubeShader.addShader(vertexShaderStr, GL_VERTEX_SHADER);
	cubeShader.addShader(fragShaderStr, GL_FRAGMENT_SHADER);
	cubeShader.finalizeShaderProgram();

	cubeShader.addUniform("camProjection");
	cubeShader.addUniform("camOrientation");
	cubeShader.addUniform("camTranslation");
	cubeShader.addUniform("objTransform");
	cubeShader.bindShaderProgram();

	//cubeShader.setUniform_mat4("camProjection",
	//	testCamera->getProjection()); // todo
	
	// TODO: Find way to not make the cube texture a pointer, like the shader
	// program.
	Texture2D *cubeTexture = new Texture2D();
	int testTextureWidth = 0;
	int testTextureHeight = 0;
	unsigned char* cubeTextureData = readImageToUChar(
		testTextureStr, testTextureWidth, testTextureHeight);
	cubeTexture->setImageData(cubeTextureData, GL_RGB, GL_RGB, testTextureWidth,
		testTextureHeight);
	cubeTexture->setTextureFiltering(GL_NEAREST, GL_NEAREST);
	cubeTexture->setTextureWrap(GL_REPEAT, GL_REPEAT);
	cubeTexture->genMipMap();
	
	Honeycomb::Object::Component *cubeRenderer =
		new Honeycomb::Mesh::MeshRenderer(cubeMesh, cubeShader, cubeTexture);
	Honeycomb::Object::Component* cubeTransform =
		new Honeycomb::Object::Transform(Vector3f(0.0F, 0.0F, -10.0F), 
			Quaternion(), Vector3f(1.0F, 1.0F, 1.0F));
	Honeycomb::Object::Component* cameraController =
		new Honeycomb::Render::Camera(Camera::CameraType::PERSPECTIVE, 100.0F, 0.3F,
			60, camH, camW, Transform(Vector3f(),
				Quaternion(Vector3f::getGlobalUp(), PI), Vector3f(1, 1, 1)));

	cubeObject = new Honeycomb::Object::Object("Cube");
	cubeObject->getComponents().push_back(cubeRenderer);
	cubeObject->getComponents().push_back(cubeTransform);

	cameraObject = new Honeycomb::Object::Object("Camera");
	cameraObject->getComponents().push_back(cameraController);

	/*
	testTransform = new Transform(Vector3f(), Quaternion(), Vector3f(1, 1, 1));
	testCamera = new Camera(Camera::CameraType::PERSPECTIVE, 100.0F, 0.3F,
		60, camH, camW, Transform(Vector3f(),
			Quaternion(Vector3f::getGlobalUp(), PI), Vector3f(1, 1, 1)));
	testModel = Model_OBJ::loadModel(testModelCubeStr);
	testMesh = new Mesh(*testModel);
	testShader = new ShaderProgram();
	testTexture = new Texture2D();
	*/

//	testTransform->setTranslation(Vector3f(0, 0, -5));

//	delete testModel;
	GameInput::getGameInput()->clear();
}
	
float uni_scale = 0;
int counter = 0;
void TestGame::update() {
	counter++;

	Honeycomb::Object::Object::getRoot()->update();

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
	/*
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

	*/

	Honeycomb::Mesh::MeshRenderer& cubeObjectMeshRenderer = 
		dynamic_cast<Honeycomb::Mesh::MeshRenderer&>(*cubeObject->getComponent("MeshRenderer"));
	Honeycomb::Object::Transform& cubeObjectTransform =
		dynamic_cast<Honeycomb::Object::Transform&>(*cubeObject->getComponent("Transform"));

	Honeycomb::Render::Camera& cameraObjectCamera =
		dynamic_cast<Honeycomb::Render::Camera&>(*cameraObject->getComponent("Camera"));

	cubeObjectMeshRenderer.getShader().setUniform_mat4("objTransform", cubeObjectTransform.getTransformationMatrix());
	cubeObjectMeshRenderer.getShader().setUniform_mat4("camOrientation", cameraObjectCamera.getProjectionOrientation());
	cubeObjectMeshRenderer.getShader().setUniform_mat4("camTranslation", cameraObjectCamera.getProjectionTranslation());
	cubeObjectMeshRenderer.getShader().setUniform_mat4("camProjection", cameraObjectCamera.getProjection());

	if (counter % 60 == 0) {
		Vector3f transF = cubeObjectTransform.getLocalForward();
		std::cout << "TRS FORW: " << transF.getX() << ", " << transF.getY() << ", " << transF.getZ() << std::endl;

		Vector3f transR = cubeObjectTransform.getLocalRight();
		std::cout << "TRS RIGHT: " << transR.getX() << ", " << transR.getY() << ", " << transR.getZ() << std::endl;

		Vector3f transU = cubeObjectTransform.getLocalUp();
		std::cout << "TRS UP: " << transU.getX() << ", " << transU.getY() << ", " << transU.getZ() << std::endl;

		Vector3f camF = cameraObjectCamera.getTransform().getLocalForward();
		std::cout << "CAM FOR: " << camF.getX() << ", " << camF.getY() << ", " << camF.getZ() << std::endl;

		Vector3f camR = cameraObjectCamera.getTransform().getLocalRight();
		std::cout << "CAM RIGHT: " << camR.getX() << ", " << camR.getY() << ", " << camR.getZ() << std::endl;

		Vector3f camU = cameraObjectCamera.getTransform().getLocalUp();
		std::cout << "CAM UP: " << camU.getX() << ", " << camU.getY() << ", " << camU.getZ() << std::endl;

		Quaternion q = cubeObjectTransform.getRotation();
		std::cout << "TRANS ROT: ";
		std::cout << q.getX() << ", " << q.getY() << ", " << q.getZ() << ", "
			<< q.getW() << std::endl;

		q = cameraObjectCamera.getTransform().getRotation();
		std::cout << "CAM ROT: ";
		std::cout << q.getX() << ", " << q.getY() << ", " << q.getZ() << ", "
			<< q.getW() << std::endl;
	}

//	testShader->setUniform_mat4("objTransform", objTransf);
//	testShader->setUniform_mat4("camOrientation", camOrien);
//	testShader->setUniform_mat4("camTranslation", camTransl);
}