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
		// SHADER INCLUDE SYSTEM TESTING...
		ShaderProgram *includeTest = new ShaderProgram();
		includeTest->addShader("..\\Honeycomb GE\\res\\shaders\\includeTest\\main\\main.glsl", 0);
		//


		// Load in all of the Models.
		GameObject *cube = Builder::getBuilder()->newCube();
		GameObject *plane = Builder::getBuilder()->newPlane();
		GameObject *sphere = Builder::getBuilder()->newSphere();
		GameObject *suzanne = Builder::getBuilder()->newSuzanne();
		GameObject *challenger = Builder::getBuilder()->newModel(
			"..\\Test Game\\res\\models\\dodge-challenger.fbx");
		GameObject *aPointLight = Builder::getBuilder()->newPointLight();

		// Initialize the Light Objects & a Camera
		GameObject *ambientLight = Builder::getBuilder()->newAmbientLight();
		ambientLight->getComponent<AmbientLight>()->
			setIntensity(0.22F);
		GameObject *directionalLight = Builder::getBuilder()->
			newDirectionalLight();
		directionalLight->getComponent<DirectionalLight>
			()->setIntensity(2.0F);
		GameObject *camera = Builder::getBuilder()->newCamera();
		aPointLight->getComponent<Transform>()->translate(
			Vector3f(0.0F, 5.0F, 0.0F));
		aPointLight->getComponent<PointLight>()->setIntensity(
			10.0F);
		aPointLight->getComponent<PointLight>()->setColor(
			Vector4f(0.0F, 0.0F, 1.0F, 1.0F));

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
		suzPointLight->setColor(Vector4f(1.0F, 0.0F, 0.0F, 1.0F));
		suzPointLight->setIntensity(10.0F);
		SpotLight *suzSpotLight = new SpotLight();
		suzSpotLight->setColor(Vector4f(0.0F, 0.0F, 1.0F, 1.0F));
		suzSpotLight->setIntensity(10.0F);

		// Add Suzanne's Components to Suzanne
		suzanne->addComponent(*suzPointLight);
		suzanne->addComponent(*suzSpotLight);
		suzanne->addComponent(*suzInputTransformable);
		camera->addComponent(*(new DirectionalLight("DirectionalLight",
			2.0F,
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F))));

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
			Vector3f(0.0F, 2.5F, 0.0F));
		challenger->getChild("Body")->getComponent<Transform>()->setScale(
			Vector3f(2.5F, 2.5F, 2.5F));
		challenger->getChild("Body")->getComponent<Transform>()->setTranslation(
			Vector3f(7.5F, 1.75F, -7.5F));

		// Create a fancy Emerald Material (non-textured).
		Material *emerald = new Material("material", 
			Texture2D::getNonTexture(),
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F),
			Vector4f(0.07568F, 0.61424F, 0.07568F, 1.0F),
			Vector4f(0.633F, 0.727811F, 0.633F, 1.0F),
			0.6F * 128.0F);
		
		// Give Suzanne & the Sphere the Emerald Material
		suzanne->getComponent<MeshRenderer>()->setMaterial(
			*emerald);
		sphere->getComponent<MeshRenderer>()->setMaterial(
			*emerald);

		// Add all objects to the scene
		this->gameScene.addChild(*cube);
		this->gameScene.addChild(*plane);
		this->gameScene.addChild(*sphere);
		this->gameScene.addChild(*suzanne);
		this->gameScene.addChild(*aPointLight);
		this->gameScene.addChild(*ambientLight);
		this->gameScene.addChild(*camera);
		this->gameScene.addChild(*challenger);
		GameScene::setActiveScene(this->gameScene);
		
		// Start the Game Scene
		this->gameScene.start();
	}

	void TestGame::stop() {
		this->gameScene.stop();
	}

	void TestGame::update() {
		/*
		// Rotate the Directional Light to emulate sun light in the scene.
		GameObject *sun = this->gameScene.getChild("Directional Light");
		DirectionalLight *sunLight = sun->getComponentOfType<DirectionalLight>
			("directionalLight");
		Transform *sunTrans = sun->getComponentOfType<Transform>("Transform");
		
		sunTrans->rotate(sunTrans->getLocalRight(), 
			0.333F * GameTime::getGameTime()->getDeltaTimeS());
		*/
	}
}