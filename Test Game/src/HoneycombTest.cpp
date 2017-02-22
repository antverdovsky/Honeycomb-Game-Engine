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
		std::cout << "POSITION: " << transf.getLocalTranslation().getX() << 
			", " << transf.getLocalTranslation().getY() << ", " <<
			transf.getLocalTranslation().getZ() << std::endl;
		std::cout << "RIGHT: " << transf.getLocalRight().getX() <<
			", " << transf.getLocalRight().getY() << ", " <<
			transf.getLocalRight().getZ() << std::endl;
		std::cout << "UP: " << transf.getLocalUp().getX() <<
			", " << transf.getLocalUp().getY() << ", " <<
			transf.getLocalUp().getZ() << std::endl;
		std::cout << "FORWARD: " << transf.getLocalForward().getX() <<
			", " << transf.getLocalForward().getY() << ", " <<
			transf.getLocalForward().getZ() << std::endl;
		std::cout << "***\n\n\n";
	}

	GameObject *parentTest;
	enum parentTest_ActiveObj {
		ROOT,
			CONE,
				TORUS,
					SPHERE,

			CYLINDER
	};

	void TestGame::input() {
		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_1)) {
			parentTest->getComponent<InputTransformable>()->start();
			parentTest->getChild("Cone")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->getComponent<InputTransformable>()->stop();
			parentTest->getChild("Cylinder")->getComponent<InputTransformable>()->stop();

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

	GameObject *car;
	GameObject *camera;
	GameObject *suzanne;
	void TestGame::start() {
		Vector3f a = Vector3f(1, 2, 3);
		float m[4][4] = {
			{ 1, 2, 3, 4 },
			{ 1, 2, 3, 4 },
			{ 1, 2, 3, 4 },
			{ 1, 2, 3, 4 }
		};
		Matrix4f mat = Matrix4f(m);
		Vector3f prod = mat * a;

		// Load in all of the Models.
		car = Builder::getBuilder()->newModel(
			"..\\Test Game\\res\\models\\dodge-challenger.fbx");
		parentTest = Builder::getBuilder()->newModel(
			"..\\Test Game\\res\\models\\parentTest1.fbx");
		GameObject *cube = Builder::getBuilder()->newCube();
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
			GameInput::KEY_CODE_R, GameInput::KEY_CODE_T,
			GameInput::KEY_CODE_F, GameInput::KEY_CODE_G,
			GameInput::KEY_CODE_V, GameInput::KEY_CODE_B,
			5.0F, 5.0F);
		PointLight *suzPointLight = new PointLight();
		suzPointLight->glVector4fs.setValue(PointLight::COLOR_VEC4, Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
		suzPointLight->glFloats.setValue(PointLight::INTENSITY_F, 3.0F);

		// Add Suzanne's Components to Suzanne
		suzanne->addComponent(*suzPointLight);
		suzanne->addComponent(*suzInputTransformable);

		// Allow the free movement of the camera
		InputTransformable *camInputTransformable = new InputTransformable();
		camera->addComponent(*camInputTransformable);

		// Transform the objects in the scene.
		cube->getComponent<Transform>()->setTranslation(
			Vector3f(-2.5F, 1.0F, -2.5F));
		plane->getComponent<Transform>()->setScale(
			Vector3f(50.0, 1.0F, 50.0F));
		sphere->getComponent<Transform>()->setScale(
			Vector3f(PI, PI, PI));
		sphere->getComponent<Transform>()->setTranslation(
			Vector3f(PI, PI, PI));
		suzanne->getComponent<Transform>()->setTranslation(
			Vector3f(3.0F, 5.5F, 0.0F));
		car->getChild("Body")->addComponent(*suzInputTransformable->clone());


		parentTest->addComponent(*suzInputTransformable->clone());
		parentTest->getChild("Cone")->addComponent(*suzInputTransformable->clone());
		parentTest->getChild("Cone")->getChild("Torus")->addComponent(*suzInputTransformable->clone());
		parentTest->getChild("Cone")->getChild("Torus")->getChild("Sphere")->addComponent(*suzInputTransformable->clone());
		parentTest->getChild("Cylinder")->addComponent(*suzInputTransformable->clone());


		// Add all objects to the scene
//		this->gameScene.addChild(*cube);
		this->gameScene.addChild(*plane);
//		this->gameScene.addChild(*sphere);
		this->gameScene.addChild(*suzanne);
		this->gameScene.addChild(*directionalLight);
		this->gameScene.addChild(*parentTest);
		this->gameScene.addChild(*ambientLight);
		this->gameScene.addChild(*camera);
		this->gameScene.addChild(*car);
		GameScene::setActiveScene(this->gameScene);

		// Start the Game Scene
		this->gameScene.start();
	}

	void TestGame::stop() {
		this->gameScene.stop();
	}

	int i = 0;
	void TestGame::update() {
		if (++i % 120 == 0) {
			system("cls");

			_printPosAndLocals(*camera->getComponent<Transform>());
			_printPosAndLocals(*car->getChild("Body")->getComponent<Transform>());
			_printPosAndLocals(*suzanne->getComponent<Transform>());
		}
	}
}