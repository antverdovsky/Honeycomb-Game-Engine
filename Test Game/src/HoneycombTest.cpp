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

	GameObject *cone;
	GameObject *suzanne;
	void TestGame::start() {
		// Load in all of the Models.
		GameObject *cube = Builder::getBuilder()->newCube();
		GameObject *plane = Builder::getBuilder()->newPlane();
		GameObject *sphere = Builder::getBuilder()->newSphere();
		suzanne = Builder::getBuilder()->newSuzanne();
		GameObject *icosphere = Builder::getBuilder()->newIcosphere();
		cone = Builder::getBuilder()->newCone();
		GameObject *challenger = Builder::getBuilder()->newModel(
			"..\\Test Game\\res\\models\\dodge-challenger.fbx");
		GameObject *aPointLight = Builder::getBuilder()->newPointLight();

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
		suzPointLight->glVector4fs.setValue(PointLight::COLOR_VEC4, Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
		suzPointLight->glFloats.setValue(PointLight::INTENSITY_F, 7.0F);
		SpotLight *suzSpotLight = new SpotLight();

		suzSpotLight->glVector4fs.setValue(PointLight::COLOR_VEC4, Vector4f(1.0F, 0.0F, 0.0F, 1.0F));
		suzSpotLight->glFloats.setValue(SpotLight::INTENSITY_F, 25.0F);
		suzSpotLight->glFloats.setValue(SpotLight::ANGLE_F, PI);

		// Add Suzanne's Components to Suzanne
//		suzanne->addComponent(*suzPointLight);
		cone->addComponent(*suzInputTransformable->clone());
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
			Vector3f(3.0F, 5.5F, 0.0F));
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
			Vector4f(0.774597F, 0.774597F, 0.774597F, 0.6F * 128.0F));
		chrome->glSampler2Ds.setValue("albedoTexture", *blank);

		// Give Suzanne & the Sphere the Emerald Material
		suzanne->getComponent<MeshRenderer>()->setMaterial(
			*chrome);
		sphere->getComponent<MeshRenderer>()->setMaterial(
			*chrome);

		/*
		srand(time(NULL));
		for (int i = -8; i <= 8; i += 4) {
			for (int j = -8; j <= 8; j += 4) {
				GameObject *light = Builder::getBuilder()->newSpotLight();

				light->getComponent<Transform>()->setTranslation(Vector3f(
					i * 5.0F, 5.0F, j * 5.0F));
//				light->getComponent<Transform>()->rotate(
//					Vector3f::getGlobalRight(), -PI / 2);
				light->getComponent<SpotLight>()->glVector4fs.setValue(
					PointLight::COLOR_VEC4, Vector4f(
						((double)rand() / (RAND_MAX)) + 1,
						((double)rand() / (RAND_MAX)) + 1,
						((double)rand() / (RAND_MAX)) + 1,
						((double)rand() / (RAND_MAX)) + 1)
				);

				light->getComponent<Transform>()->rotate(Vector3f::getGlobalRight(), PI);
				light->getComponent<SpotLight>()->glFloats.setValue(
					SpotLight::INTENSITY_F, 10.0F);
				light->getComponent<SpotLight>()->glFloats.setValue(
					SpotLight::ANGLE_F, PI);
				light->addComponent(*suzInputTransformable->clone());

				this->gameScene.addChild(*light);
			}
		}
		*/

		// Add all objects to the scene
		this->gameScene.addChild(*cube);
		this->gameScene.addChild(*cone);
		this->gameScene.addChild(*plane);
		this->gameScene.addChild(*sphere);
		this->gameScene.addChild(*suzanne);
		this->gameScene.addChild(*aPointLight);
		this->gameScene.addChild(*icosphere);
		//		this->gameScene.addChild(*directionalLight);
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
		cone->getComponent<Transform>()->setRotation(suzanne->getComponent<
			Transform>()->getRotation());
	}
}