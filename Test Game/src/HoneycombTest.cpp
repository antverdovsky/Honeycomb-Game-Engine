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
		GameObject *challenger = Builder::getBuilder()->newModel(
			"..\\Test Game\\res\\models\\dodge-challenger.fbx");
		GameObject *aPointLight = Builder::getBuilder()->newPointLight();

		// Initialize the Light Objects & a Camera
		GameObject *ambientLight = Builder::getBuilder()->newAmbientLight();
		ambientLight->getComponent<AmbientLight>()->
			glFloats.setValue(AmbientLight::INTENSITY_F, 0.1F);
		GameObject *directionalLight = Builder::getBuilder()->
			newDirectionalLight();
		directionalLight->getComponent<DirectionalLight>
			()->glFloats.setValue(DirectionalLight::INTENSITY_F, 1.0F);
		directionalLight->getComponent<Transform>()->rotate(Vector3f::getGlobalRight(), -PI / 2);
		GameObject *camera = Builder::getBuilder()->newCamera();
		aPointLight->getComponent<Transform>()->translate(
			Vector3f(5.0F, 5.0F, 0.0F));
		aPointLight->getComponent<PointLight>()->glVector4fs.setValue(PointLight::COLOR_VEC4,
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
		suzPointLight->glVector4fs.setValue(PointLight::COLOR_VEC4, Vector4f(1.0F, 0.0F, 0.0F, 1.0F));
		SpotLight *suzSpotLight = new SpotLight();
		suzSpotLight->glVector4fs.setValue(PointLight::COLOR_VEC4, Vector4f(1.0F, 0.0F, 0.0F, 1.0F));

		// Add Suzanne's Components to Suzanne
		suzanne->addComponent(*suzPointLight);
		suzanne->addComponent(*suzSpotLight);
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
			Vector3f(0.0F, 2.5F, 0.0F));
		challenger->getChild("Body")->getComponent<Transform>()->setScale(
			Vector3f(2.5F, 2.5F, 2.5F));
		challenger->getChild("Body")->getComponent<Transform>()->setTranslation(
			Vector3f(7.5F, 1.75F, -7.5F));

		// Create a fancy Chrome Material (non-textured).
		Texture2D *blank = new Texture2D();
		blank->initialize();
		blank->setImageData();
		Material *chrome = new Material();
		chrome->glVector4fs.setValue("ambientColor", 
			Vector4f(0.25F, 0.25F, 0.25F, 1.0F));
		chrome->glVector4fs.setValue("diffuseColor",
			Vector4f(0.4F, 0.4F, 0.4F, 1.0F));
		chrome->glVector4fs.setValue("specularColor",
			Vector4f(0.774597F, 0.774597F, 0.774597F, 1.0F));
		chrome->glFloats.setValue("shininess", 0.6F * 128.0F);
		chrome->glSampler2Ds.setValue("albedoTexture", *blank);
		
		// Give Suzanne & the Sphere the Emerald Material
		suzanne->getComponent<MeshRenderer>()->setMaterial(
			*chrome);
		sphere->getComponent<MeshRenderer>()->setMaterial(
			*chrome);

		// Add all objects to the scene
		this->gameScene.addChild(*cube);
		this->gameScene.addChild(*plane);
		this->gameScene.addChild(*sphere);
		this->gameScene.addChild(*suzanne);
		this->gameScene.addChild(*aPointLight);
		this->gameScene.addChild(*directionalLight);
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