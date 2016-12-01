#include "..\include\HoneycombTest.h"

#include "..\..\Honeycomb GE\include\HoneycombEngine.h"

#include "..\include\components\InputTransformable.h"

#include <iostream>
#include <ctime>

using namespace HoneycombEngine;
using namespace HoneycombTest::Components;

namespace HoneycombTest {
	void TestGame::input() {
		GameObject::getRoot().input();
	}

	void TestGame::render() {
		GameObject::getRoot().render();
	}

	void TestGame::start() {
		// Load in all of the Models.
		GameObject *cube = Builder::getBuilder()->newCube();
		GameObject *plane = Builder::getBuilder()->newPlane();
		GameObject *sphere = Builder::getBuilder()->newSphere();
		GameObject *suzanne = Builder::getBuilder()->newSuzanne();

		// Initialize the Light Objects & a Camera
		GameObject *ambientLight = Builder::getBuilder()->newAmbientLight();
		ambientLight->getComponentOfType<AmbientLight>("ambientLight")->
			setIntensity(0.05F);
		GameObject *directionalLight = Builder::getBuilder()->
			newDirectionalLight();
		directionalLight->getComponentOfType<DirectionalLight>
			("directionalLight")->setIntensity(0.25F);
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
		suzPointLight->setColor(Vector4f(1.0F, 0.0F, 0.0F, 1.0F));
		suzPointLight->setIntensity(10.0F);
		SpotLight *suzSpotLight = new SpotLight();
		suzSpotLight->setColor(Vector4f(0.0F, 0.0F, 1.0F, 1.0F));
		suzSpotLight->setIntensity(10.0F);

		// Add Suzanne's Components to Suzanne
		suzanne->addComponent(*suzPointLight);
		suzanne->addComponent(*suzSpotLight);
		suzanne->addComponent(*suzInputTransformable);

		// Allow the free movement of the camera
		InputTransformable *camInputTransformable = new InputTransformable();
		camera->addComponent(*camInputTransformable);

		// Transform the objects in the scene.
		cube->getComponentOfType<Transform>("Transform")->setTranslation(
			Vector3f(-2.5F, 1.0F, -2.5F));
		plane->getComponentOfType<Transform>("Transform")->setScale(
			Vector3f(25.0F, 25.0F, 25.0F));
		sphere->getComponentOfType<Transform>("Transform")->setScale(
			Vector3f(PI, PI, PI));
		sphere->getComponentOfType<Transform>("Transform")->setTranslation(
			Vector3f(PI, PI, PI));
		suzanne->getComponentOfType<Transform>("Transform")->setTranslation(
			Vector3f(0.0F, 2.5F, 0.0F));

		// Create a fancy Emerald Material (non-textured).
		Material *emerald = new Material("material", 
			Texture2D::getNonTexture(),
			Vector4f(0.0215F, 0.1745F, 0.0215F, 1.0F),
			Vector4f(0.07568F, 0.61424F, 0.07568F, 1.0F),
			Vector4f(0.633F, 0.727811F, 0.633F, 1.0F),
			0.6F * 128.0F);
		
		// Give Suzanne & the Sphere the Emerald Material
		suzanne->getComponentOfType<MeshRenderer>("MeshRenderer")->setMaterial(
			*emerald);
		sphere->getComponentOfType<MeshRenderer>("MeshRenderer")->setMaterial(
			*emerald);

		GameObject::getRoot().start();
	}

	void TestGame::stop() {
		GameObject::getRoot().stop();
	}

	void TestGame::update() {
		// Rotate the Directional Light to emulate sun light in the scene.
		GameObject *sun = GameObject::getRoot().getChild("Directional Light");
		DirectionalLight *sunLight = sun->getComponentOfType<DirectionalLight>
			("directionalLight");
		Transform *sunTrans = sun->getComponentOfType<Transform>("Transform");
		
		sunTrans->rotate(sunTrans->getLocalRight(), 
			0.333F * GameTime::getGameTime()->getDeltaTimeS());

		GameObject::getRoot().update();
	}
}