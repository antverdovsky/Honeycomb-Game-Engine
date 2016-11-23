#include "..\include\HoneycombTest.h"

#include "..\..\Honeycomb GE\include\HoneycombEngine.h"

#include "..\include\components\InputTransformable.h"

using namespace HoneycombEngine;
using namespace HoneycombTest::Components;

namespace HoneycombTest {
	void TestGame::input() {
		PointLight *pL = GameObject::getRoot()->getChild("Suzanne")->
			getComponentOfType<PointLight>("pointLight");

		/*if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_1))
			pL->setRange(pL->getRange() + 0.5F);
		else if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_2))
			pL->setRange(pL->getRange() - 0.5F);

		if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_3))
			pL->setIntensity(pL->getIntensity() + 0.1F);
		else if (GameInput::getGameInput()->getKeyDown(GameInput::KEY_CODE_4))
			pL->setIntensity(pL->getIntensity() - 0.1F);*/

		GameObject::getRoot()->input();
	}

	void TestGame::render() {
		GameObject::getRoot()->render();
	}

	void TestGame::start() {
		///
		/// Load in all of the Models.
		///
		GameObject *cube = Builder::getBuilder()->newCube();
		GameObject *plane = Builder::getBuilder()->newPlane();
		GameObject *sphere = Builder::getBuilder()->newSphere();
		GameObject *suzanne = Builder::getBuilder()->newSuzanne();

//		suzanne->addComponent(*(new PointLight(BaseLight("pointLight", 1.0F, 
//			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)), 
//			20.0F, 1.0F, 0.22F, 0.20F)));
		suzanne->addComponent(*(new SpotLight(BaseLight("spotLight", 25,
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)),
			50, Utils::degToRad(10), 1.0F, 0.22F, 0.20F)));

		///
		/// Load in all of the Lights and the Camera.
		///
		GameObject *camera = Builder::getBuilder()->newCamera();
		GameObject *ambientLight = Builder::getBuilder()->newAmbientLight();
//		GameObject *directionalLight = Builder::getBuilder()->
//			newDirectionalLight();
//		GameObject *pointLight = Builder::getBuilder()->newPointLight();


		///
		/// Create additional components for the created objects & add.
		///
		InputTransformable *camInputTransformable = new InputTransformable();
		InputTransformable *suzInputTransformable = new InputTransformable(
			GameInput::KEY_CODE_UP, GameInput::KEY_CODE_DOWN,
			GameInput::KEY_CODE_LEFT, GameInput::KEY_CODE_RIGHT,
			GameInput::KEY_CODE_COMMA, GameInput::KEY_CODE_PERIOD,
			GameInput::KEY_CODE_R, GameInput::KEY_CODE_T,
			GameInput::KEY_CODE_F, GameInput::KEY_CODE_G,
			GameInput::KEY_CODE_V, GameInput::KEY_CODE_B,
			5.0F, 5.0F);
		camera->addComponent(*camInputTransformable);
		suzanne->addComponent(*suzInputTransformable);


		///
		/// Transform the objects in the scene.
		///
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


		///
		/// Create a fancy Emerald Material (textured and non-textured).
		///
		Material *emerald = new Material("material", nullptr,
			Vector4f(0.0215F, 0.1745F, 0.0215F, 1.0F),
			Vector4f(0.07568F, 0.61424F, 0.07568F, 1.0F),
			Vector4f(0.633F, 0.727811F, 0.633F, 1.0F),
			0.6F * 128.0F);
//			Vector4f(0.0215F, 0.1745F, 0.0215F, 1.0F),
//			Vector4f(0.07568F, 0.61424F, 0.07568F, 1.0F),
//			Vector4f(0.633F, 0.727811F, 0.633F, 1.0F),
//			0.6F * 128.0F);
		Material *emeraldTex = new Material(*emerald);
//		Texture2D *tex =
//			cube->getComponentOfType<MeshRenderer>("MeshRenderer")->
//			getMaterial()->getAlbedoTexture();
//		emeraldTex->setAlbedoTexture(tex);


		///
		/// Give the Cube, Sphere and Plane the Textured Emerald Material, and
		/// give Suzanne the non-Textured Emerald Material.
		///
		cube->getComponentOfType<MeshRenderer>("MeshRenderer")->
			setMaterial(emeraldTex);
		plane->getComponentOfType<MeshRenderer>("MeshRenderer")->
			setMaterial(emeraldTex);
		sphere->getComponentOfType<MeshRenderer>("MeshRenderer")->
			setMaterial(emeraldTex);
		suzanne->getComponentOfType<MeshRenderer>("MeshRenderer")->
			setMaterial(emerald);

		GameObject::getRoot()->start();
	}

	void TestGame::stop() {
		GameObject::getRoot()->stop();
	}

	void TestGame::update() {
		///
		/// Rotate the Directional Light to emulate sun light in the scene.
		///
//		GameObject *sun = GameObject::getRoot()->getChild("Directional Light");
//		Transform *sunTrans = sun->getComponentOfType<Transform>("Transform");
//		sunTrans->rotate(sunTrans->getLocalRight(), 
//			0.333F * Time::getDeltaTimeSeconds());

		GameObject::getRoot()->update();
	}
}