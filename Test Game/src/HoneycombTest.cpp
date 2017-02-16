#include "..\include\HoneycombTest.h"

#include "..\..\Honeycomb GE\include\HoneycombEngine.h"

#include "..\include\components\InputTransformable.h"

using namespace HoneycombEngine;
using namespace HoneycombTest::Components;

namespace HoneycombTest {
	void TestGame::input() {

	}

	void TestGame::render() {

	}

	void TestGame::start() {
		// Load in all of the Models.
		GameObject *cube = Builder::getBuilder()->newCube();
		GameObject *plane = Builder::getBuilder()->newPlane();
		GameObject *sphere = Builder::getBuilder()->newSphere();
		GameObject *suzanne = Builder::getBuilder()->newSuzanne();
		GameObject *car = Builder::getBuilder()->newModel(
			"..\\Test Game\\res\\models\\dodge-challenger.fbx");
		
		// Initialize the Light Objects & a Camera
		GameObject *ambientLight = Builder::getBuilder()->newAmbientLight();
		ambientLight->getComponent<AmbientLight>()->
			glFloats.setValue(AmbientLight::INTENSITY_F, 0.25F);
		
		GameObject *directionalLight = Builder::getBuilder()->
			newDirectionalLight();
		directionalLight->getComponent<DirectionalLight>
			()->glFloats.setValue(DirectionalLight::INTENSITY_F, 0.25F);
		directionalLight->getComponent<Transform>()->rotate(Vector3f::getGlobalRight(), -PI / 2);
		
		GameObject *camera = Builder::getBuilder()->newCamera();
		
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

		// Add all objects to the scene
		this->gameScene.addChild(*cube);
		this->gameScene.addChild(*plane);
		this->gameScene.addChild(*sphere);
		this->gameScene.addChild(*suzanne);
		this->gameScene.addChild(*directionalLight);
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

	void TestGame::update() {

	}
}