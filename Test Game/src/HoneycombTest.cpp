#include "..\include\HoneycombTest.h"

#include "..\..\Honeycomb GE\include\HoneycombEngine.h"

#include "..\include\components\InputTransformable.h"
#include "..\..\Honeycomb GE\include\debug\Logger.h"

using namespace HoneycombEngine;
using namespace HoneycombTest::Components;
using Honeycomb::Debug::Logger;

namespace HoneycombTest {
	// print position and local directions of the specified transform :-)
	void _printPosAndLocals(Transform &transf) {
		std::cout << "***TRANSFORM FOR: " << transf.getAttached()->getName() << std::endl;
		std::cout << "LOCAL POSITION: " << transf.getLocalTranslation().getX() << 
			", " << transf.getLocalTranslation().getY() << ", " <<
			transf.getLocalTranslation().getZ() << std::endl;
		std::cout << "(INV_TRANSF_POS) LOCAL POS: " << transf.inverseTransformPoint(transf.getGlobalTranslation()).getX() << ", "
			<< transf.inverseTransformPoint(transf.getGlobalTranslation()).getY() << ", " <<
			transf.inverseTransformPoint(transf.getGlobalTranslation()).getZ() << std::endl << std::endl;

		std::cout << "GLOBAL POSITION: " << transf.getGlobalTranslation().getX() <<
			", " << transf.getGlobalTranslation().getY() << ", " <<
			transf.getGlobalTranslation().getZ() << std::endl;
		std::cout << "(TRANSF_POS) GLOBAL POS: " << transf.transformPoint(Vector3f()).getX() << ", " <<
			transf.transformPoint(Vector3f()).getY() << ", " <<
			transf.transformPoint(Vector3f()).getZ() << std::endl << std::endl;

		std::cout << "LOCAL RIGHT: " << transf.getLocalRight().getX() <<
			", " << transf.getLocalRight().getY() << ", " <<
			transf.getLocalRight().getZ() << std::endl;
		std::cout << "(TRANSF_DIR) LOCAL RIGHT: " << transf.transformDirection(Vector3f::getGlobalRight()).getX() << ", " <<
			transf.transformDirection(Vector3f::getGlobalRight()).getY() << ", " <<
			transf.transformDirection(Vector3f::getGlobalRight()).getZ() << std::endl << std::endl;


		std::cout << "LOCAL UP: " << transf.getLocalUp().getX() <<
			", " << transf.getLocalUp().getY() << ", " <<
			transf.getLocalUp().getZ() << std::endl;
		std::cout << "(TRANSF_DIR) LOCAL UP: " << transf.transformDirection(Vector3f::getGlobalUp()).getX() << ", " << 
			transf.transformDirection(Vector3f::getGlobalUp()).getY() << ", " <<
			transf.transformDirection(Vector3f::getGlobalUp()).getZ() << std::endl << std::endl;
		
		
		std::cout << "LOCAL FORWARD: " << transf.getLocalForward().getX() <<
			", " << transf.getLocalForward().getY() << ", " <<
			transf.getLocalForward().getZ() << std::endl;
		std::cout << "(TRANSF_DIR) LOCAL FORWARD: " << transf.transformDirection(Vector3f::getGlobalForward()).getX() << ", " <<
			transf.transformDirection(Vector3f::getGlobalForward()).getY() << ", " <<
			transf.transformDirection(Vector3f::getGlobalForward()).getZ() << std::endl << std::endl;

		std::cout << "GLOBAL ROTATION: " << transf.getLocalRotation().getW() << ", "
			<< transf.getGlobalRotation().getX() << ", "
			<< transf.getLocalRotation().getY() << ", "
			<< transf.getLocalRotation().getZ() << std::endl;
		std::cout << "LOCAL ROTATION: " << transf.getLocalRotation().getW() << ", "
			<< transf.getLocalRotation().getX() << ", "
			<< transf.getLocalRotation().getY() << ", "
			<< transf.getLocalRotation().getZ() << std::endl << std::endl;

		std::cout << "GLOBAL RIGHT: " << transf.inverseTransformDirection(transf.getLocalRight()).getX() << ", " <<
			transf.inverseTransformDirection(transf.getLocalRight()).getY() << ", " <<
			transf.inverseTransformDirection(transf.getLocalRight()).getZ() << std::endl;
		std::cout << "GLOBAL UP: " << transf.inverseTransformDirection(transf.getLocalUp()).getX() << ", " <<
			transf.inverseTransformDirection(transf.getLocalUp()).getY() << ", " <<
			transf.inverseTransformDirection(transf.getLocalUp()).getZ() << std::endl;
		std::cout << "GLOBAL FORWARD: " << transf.inverseTransformDirection(transf.getLocalForward()).getX() << ", " <<
			transf.inverseTransformDirection(transf.getLocalForward()).getY() << ", " <<
			transf.inverseTransformDirection(transf.getLocalForward()).getZ() << std::endl << std::endl;

		std::cout << "LOCAL SCALE: " << transf.getLocalScale().getX() << ", " <<
			transf.getLocalScale().getY() << ", " <<
			transf.getLocalScale().getZ() << ", " << std::endl << std::endl;

		std::cout << "***\n\n\n";
	}

	GameObject *parentTest;
	GameObject *car;
	GameObject *camera;
	GameObject *suzanne;
	GameObject *cube;
	enum parentTest_ActiveObj {
		ROOT,
			CONE,
				TORUS,
					SPHERE,

			CYLINDER
	};

	void TestGame::input() {
		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_9)) {
			parentTest->getComponent<InputTransformable>()->getSpace() = Space::LOCAL;
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->getSpace() = Space::LOCAL;
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->getSpace() = Space::LOCAL;
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->getSpace() = Space::LOCAL;
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->getSpace() = Space::LOCAL;
			suzanne->getComponent<InputTransformable>()->getSpace() = Space::LOCAL;

			std::cout << "ALL SET TO LOCAL" << std::endl;
		}
		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_0)) {
			parentTest->getComponent<InputTransformable>()->getSpace() = Space::GLOBAL;
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->getSpace() = Space::GLOBAL;
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->getSpace() = Space::GLOBAL;
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->getSpace() = Space::GLOBAL;
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->getSpace() = Space::GLOBAL;
			suzanne->getComponent<InputTransformable>()->getSpace() = Space::GLOBAL;

			std::cout << "ALL SET TO GLOBAL" << std::endl;
		}

		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_1)) {
			parentTest->getComponent<InputTransformable>()->start();
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->stop();
			suzanne->getComponent<InputTransformable>()->stop();

			Transform *ptr = parentTest->getComponent<Transform>();
			std::cout << "ROOT LOCAL: " << ptr->getLocalTranslation().getX() << ", " <<
				ptr->getLocalTranslation().getY() << ", " <<
				ptr->getLocalTranslation().getZ() << ", " << std::endl;
			std::cout << "ROOT GLOBAL: " << ptr->getGlobalTranslation().getX() << ", " <<
				ptr->getGlobalTranslation().getY() << ", " <<
				ptr->getGlobalTranslation().getZ() << ", " << std::endl;
		}
		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_2)) {
			parentTest->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->start();
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->stop();
			suzanne->getComponent<InputTransformable>()->start();
				
			Transform *ptr = parentTest->getChild("Cone")->getComponent<Transform>();
			std::cout << "CONE LOCAL: " << ptr->getLocalTranslation().getX() << ", " <<
				ptr->getLocalTranslation().getY() << ", " <<
				ptr->getLocalTranslation().getZ() << ", " << std::endl;
			std::cout << "CONE GLOBAL: " << ptr->getGlobalTranslation().getX() << ", " <<
				ptr->getGlobalTranslation().getY() << ", " <<
				ptr->getGlobalTranslation().getZ() << ", " << std::endl;
		}
		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_3)) {
			parentTest->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->start();
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->stop();

			Transform *ptr = parentTest->getChild("Cone")->getChild("Torus")->getComponent<Transform>();
			std::cout << "TORUS LOCAL: " << ptr->getLocalTranslation().getX() << ", " <<
				ptr->getLocalTranslation().getY() << ", " <<
				ptr->getLocalTranslation().getZ() << ", " << std::endl;
			std::cout << "TORUS GLOBAL: " << ptr->getGlobalTranslation().getX() << ", " <<
				ptr->getGlobalTranslation().getY() << ", " <<
				ptr->getGlobalTranslation().getZ() << ", " << std::endl;
		}
		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_4)) {
			parentTest->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->start();
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->stop();

			Transform *ptr = parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<Transform>();
			std::cout << "SPHERE LOCAL: " << ptr->getLocalTranslation().getX() << ", " <<
				ptr->getLocalTranslation().getY() << ", " <<
				ptr->getLocalTranslation().getZ() << ", " << std::endl;
			std::cout << "SPHERE GLOBAL: " << ptr->getGlobalTranslation().getX() << ", " <<
				ptr->getGlobalTranslation().getY() << ", " <<
				ptr->getGlobalTranslation().getZ() << ", " << std::endl;
		}
		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_5)) {
			parentTest->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->start();

			Transform *ptr = parentTest->getChild("Cylinder")->getComponent<Transform>();
			std::cout << "CYLINDER LOCAL: " << ptr->getLocalTranslation().getX() << ", " <<
				ptr->getLocalTranslation().getY() << ", " <<
				ptr->getLocalTranslation().getZ() << ", " << std::endl;
			std::cout << "CYLINDER GLOBAL: " << ptr->getGlobalTranslation().getX() << ", " <<
				ptr->getGlobalTranslation().getY() << ", " <<
				ptr->getGlobalTranslation().getZ() << ", " << std::endl;
		}
		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_6)) {
			parentTest->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->stop();
		}
	}

	void TestGame::render() {

	}

	void TestGame::start() {
		Vector3f a = Vector3f(1, 2, 3);
		float m[4][4] = {
			{ 9, 9, 9, 9 },
			{ 9, 1, -1, 9 },
			{ 9, -1, 1, 9 },
			{ 1, 3, 9, 9 }
		};
		Matrix4f mat = Matrix4f(m);
		Matrix4f inv = mat.getInverse();
		float det = mat.getDeterminant();
		Vector3f prod = mat * a;

		// Load in all of the Models.
		car = Builder::getBuilder()->newModel(
			"..\\Test Game\\res\\models\\dodge-challenger.fbx");
		parentTest = Builder::getBuilder()->newModel(
			"..\\Test Game\\res\\models\\parentTest1.fbx");
		cube = Builder::getBuilder()->newCube();
		GameObject *plane = Builder::getBuilder()->newPlane();
		GameObject *sphere = Builder::getBuilder()->newSphere();
		suzanne = Builder::getBuilder()->newSuzanne();
		
		// Initialize the Light Objects & a Camera
		GameObject *ambientLight = Builder::getBuilder()->newAmbientLight();
		ambientLight->getComponent<AmbientLight>()->
			glFloats.setValue(AmbientLight::INTENSITY_F, 0.25F);
		
		GameObject *directionalLight = Builder::getBuilder()->
			newDirectionalLight();
		directionalLight->getComponent<DirectionalLight>
			()->glFloats.setValue(DirectionalLight::INTENSITY_F, 0.25F);
		directionalLight->getComponent<Transform>()->rotate(Vector3f::getGlobalRight(), -PI / 2);
		
		camera = Builder::getBuilder()->newCamera();
		
		// Initialize the Suzanne Components
		InputTransformable *suzInputTransformable = new InputTransformable(
			GameInput::KEY_CODE_UP, GameInput::KEY_CODE_DOWN,
			GameInput::KEY_CODE_LEFT, GameInput::KEY_CODE_RIGHT,
			GameInput::KEY_CODE_COMMA, GameInput::KEY_CODE_PERIOD,
			GameInput::KEY_CODE_U, GameInput::KEY_CODE_I,
			GameInput::KEY_CODE_J, GameInput::KEY_CODE_K,
			GameInput::KEY_CODE_O, GameInput::KEY_CODE_L,
			GameInput::KEY_CODE_Z, GameInput::KEY_CODE_X, // scale
			GameInput::KEY_CODE_C, GameInput::KEY_CODE_V,
			GameInput::KEY_CODE_B, GameInput::KEY_CODE_N,
			10.0F, 10.0F, 10.0F, Space::LOCAL);
		PointLight *suzPointLight = new PointLight();
		suzPointLight->glVector4fs.setValue(PointLight::COLOR_VEC4, Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
		suzPointLight->glFloats.setValue(PointLight::INTENSITY_F, 3.0F);

		// Add Suzanne's Components to Suzanne
		//suzanne->addComponent(*suzPointLight);
		suzanne->addComponent(*suzInputTransformable);

		// Allow the free movement of the camera
		InputTransformable *camInputTransformable = new InputTransformable();
		camera->addComponent(*camInputTransformable);

		// Transform the objects in the scene.
//		cube->getComponent<Transform>()->setTranslation(
//			Vector3f(0.0F, 0.5F, 0.0F));
//		cube->getComponent<Transform>()->setTranslation(Vector3f::getGlobalRight() * 10.0F);
		plane->getComponent<Transform>()->setScale(
			Vector3f(50.0, 1.0F, 50.0F));
		sphere->getComponent<Transform>()->setScale(
			Vector3f(PI, PI, PI));
		sphere->getComponent<Transform>()->setTranslation(
			Vector3f(PI, PI, PI));
		suzanne->getComponent<Transform>()->setTranslation(
			Vector3f(3.0F, 5.5F, 0.0F));
		car->getChild("Body")->addComponent(*suzInputTransformable->clone());

		cube->addComponent(*suzInputTransformable->clone());

		parentTest->addComponent(*suzInputTransformable->clone());
		parentTest->getChild("Cone")->addComponent(*suzInputTransformable->clone());
		parentTest->getChild("Cone")->getChild("Torus")->addComponent(*suzInputTransformable->clone());
		parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->addComponent(*suzInputTransformable->clone());
		parentTest->getChild("Cylinder")->addComponent(*suzInputTransformable->clone());


		// Add all objects to the scene
		this->gameScene.addChild(*cube);
		this->gameScene.addChild(*plane);
//		this->gameScene.addChild(*sphere);
//		this->gameScene.addChild(*suzanne);
		this->gameScene.addChild(*directionalLight);
//		this->gameScene.addChild(*parentTest);
		this->gameScene.addChild(*ambientLight);
		this->gameScene.addChild(*camera);
//		this->gameScene.addChild(*car);
		GameScene::setActiveScene(this->gameScene);
		suzanne->getComponent<Transform>()->setTranslation(Vector3f(5, 0, 0));

		//cube->addChild(*suzanne);
		suzanne->getComponent<Transform>()->translate(Vector3f::getGlobalUp() * 5.0F);

		// Start the Game Scene
		this->gameScene.start();

//		parentTest->getComponent<Transform>()->rotate(Vector3f::getGlobalUp(), -PI / 2);
//		parentTest->getChild("Cylinder")->getComponent<Transform>()->rotate(Vector3f::getGlobalUp(), PI / 2);

		std::cout << "LOCAL: " << parentTest->getChild("Cylinder")->getComponent<Transform>()->getLocalRotation().getW() << ", "
			<< parentTest->getChild("Cylinder")->getComponent<Transform>()->getLocalRotation().getX() << ", "
			<< parentTest->getChild("Cylinder")->getComponent<Transform>()->getLocalRotation().getY() << ", " 
			<< parentTest->getChild("Cylinder")->getComponent<Transform>()->getLocalRotation().getZ() << std::endl;
		std::cout << "GLOBAL: " << parentTest->getChild("Cylinder")->getComponent<Transform>()->getGlobalRotation().getW() << ", "
			<< parentTest->getChild("Cylinder")->getComponent<Transform>()->getGlobalRotation().getX() << ", "
			<< parentTest->getChild("Cylinder")->getComponent<Transform>()->getGlobalRotation().getY() << ", "
			<< parentTest->getChild("Cylinder")->getComponent<Transform>()->getLocalRotation().getZ() << std::endl;

		int b = 32;
		//cube->getComponent<Transform>()->rotateAround(Vector3f(0, 0, 0), Vector3f::getGlobalUp(), PI);
	}

	void TestGame::stop() {
		this->gameScene.stop();
	}

	int i = 0;
	void TestGame::update() {
 //   	cube->getComponent<Transform>()->rotateAround(suzanne->getComponent<Transform>()->getGlobalTranslation(), suzanne->getComponent<Transform>()->getLocalUp() * 100.0F, 0.02F);
		//cube->getComponent<Transform>()->setTranslation(Vector3f((i % 120) / 100.0F, 0.0F, 0.0F));
//		parentTest->getChild("Cylinder")->getComponent<Transform>()->setTranslation(Vector3f::getGlobalForward() * (i % 120) / 60.0F, Space::LOCAL);
//		parentTest->getChild("Cylinder")->getComponent<Transform>()->setTranslation(Vector3f::getGlobalForward() * (i % 120) / 60.0F, parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->getSpace());
//		cube->getComponent<Transform>()->rotate(Vector3f::getGlobalRight(), 0.01F);
		if (++i % 60 == 0) {
//			system("cls");

//			_printPosAndLocals(*camera->getComponent<Transform>());
//			_printPosAndLocals(*car->getChild("Body")->getComponent<Transform>());
//			_printPosAndLocals(*suzanne->getComponent<Transform>());
//			_printPosAndLocals(*parentTest->getChild("Cone")->getComponent<Transform>());
//			_printPosAndLocals(*cube->getComponent<Transform>());
			int a = 32;
			_printPosAndLocals(*cube->getComponent<Transform>());
		}
		
		//parentTest->getComponent<Transform>()->translate(Vector3f::getGlobalForward() * 0.01F, *suzanne->getComponent<Transform>());
		//parentTest->getChild("Cylinder")->getComponent<Transform>()->translate(Vector3f::getGlobalForward() * 0.01F, Space::GLOBAL);
	}
}