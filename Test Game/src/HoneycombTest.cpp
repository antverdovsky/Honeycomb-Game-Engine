#include "..\include\HoneycombTest.h"

#include "..\..\Honeycomb GE\include\HoneycombEngine.h"

#include "..\include\components\InputTransformable.h"

#include <iostream>
#include <ctime>

using namespace HoneycombEngine;
using namespace HoneycombTest::Components;

namespace HoneycombTest {
	void TestGame::input() {
		/*
		bool somethingHappened = false;
		PointLight *pL = GameObject::getRoot()->getChild("Suzanne")->
			getComponentOfType<PointLight>("pointLight");
		BaseLight::Attenuation atten = pL->getAttenuation();
		BaseLight::Attenuation atten2 = pL->getAttenuation();
		const BaseLight::Attenuation &attenRef = pL->getAttenuation();

		if (GameInput::getGameInput()->getKeyReleased(GameInput::KEY_CODE_1)) {
			atten.setAttenuationQuadratic(0.5F);
			somethingHappened = true;
		}
		else if (GameInput::getGameInput()->getKeyReleased(GameInput::KEY_CODE_2)) {
			atten.setAttenuationQuadratic(0.22F);
			somethingHappened = true;
		}

		if (GameInput::getGameInput()->getKeyReleased(GameInput::KEY_CODE_3)) {
			atten.setAttenuationLinear(0.5F);
			somethingHappened = true;
		}
		else if (GameInput::getGameInput()->getKeyReleased(GameInput::KEY_CODE_4)) {
			atten.setAttenuationLinear(0.20F);
			somethingHappened = true;
		}
		else if (GameInput::getGameInput()->getKeyReleased(GameInput::KEY_CODE_5)) {
			atten2.setAttenuationLinear(1.0F);
			somethingHappened = true;
		}

		pL->setAttenuation(atten);

		if (somethingHappened) {
			std::cout << "PL->ATTEN LIN: " << pL->getAttenuation().getAttenuationLinear() << std::endl;
			std::cout << "ATTEN LIN: " << atten.getAttenuationLinear() << std::endl;
			std::cout << "ATTEN2 LIN: " << atten2.getAttenuationLinear() << std::endl;
			std::cout << "ATTEN REF LIN: " << attenRef.getAttenuationLinear() << std::endl;
		}
		*/
		GameObject::getRoot()->input();
	}

	void TestGame::render() {
		GameObject::getRoot()->render();
	}

	void TestGame::start() {
		srand(time(NULL));

		for (int i = 0; i <= 200; i++) {
			Model::loadModel("..\\Honeycomb GE\\res\\models\\default\\cube.fbx");
			GameObject *myCube = Builder::getBuilder()->newCube();

			myCube->getComponentOfType<Transform>("Transform")->
				translate(Vector3f(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10));
			Material *newMat = new Material(*myCube->getComponentOfType<MeshRenderer>("MeshRenderer")->
				getMaterial());
			newMat->setDiffuseColor(Vector4f(((float)rand() / (RAND_MAX)),
				((float)rand() / (RAND_MAX)),
				((float)rand() / (RAND_MAX)),
				1.0F));
			myCube->getComponentOfType<MeshRenderer>("MeshRenderer")->setMaterial(newMat);

			
			delete myCube;
		}

		Vector2f vec = Vector2f(0.0F, 1.0F);
		const float &vecXRef = vec.getX();

		std::cout << "VEC.GET_X(): " << vec.getX() << std::endl;
		std::cout << "VEC X REF: " << vecXRef << std::endl;

		vec.setX(9.0F);

		std::cout << "VEC.GET_X(): " << vec.getX() << std::endl;
		std::cout << "VEC X REF: " << vecXRef << std::endl;
		
		Vector2f newVec = vec.add(Vector2f(1.0F, 1.0F));
		
		std::cout << "NEW VEC.GET_X(): " << newVec.getX() << std::endl;

		Matrix4f mat = Matrix4f::identity();
		mat.setAt(0, 0, 10);

		std::cout << mat.getAt(0, 0) << std::endl;
		std::cout << (Matrix4f::identity()).getAt(0, 0) << std::endl;


		///
		/// Load in all of the Models.
		///
		GameObject *cube = Builder::getBuilder()->newCube();
		GameObject *plane = Builder::getBuilder()->newPlane();
		GameObject *sphere = Builder::getBuilder()->newSphere();
		GameObject *suzanne = Builder::getBuilder()->newSuzanne();

		suzanne->addComponent(*(new PointLight(BaseLight("pointLight", 2.5F, 
			Vector4f(0.0F, 0.0F, 1.0F, 1.0F)), 
			10.0F, 1.0F, 0.22F, 0.20F)));
		suzanne->addComponent(*(new SpotLight(BaseLight("spotLight", 5.0F,
			Vector4f(1.0F, 0.0F, 0.0F, 1.0F)),
			50, Utils::degToRad(45), 1.0F, 0.22F, 0.20F)));

		///
		/// Load in all of the Lights and the Camera.
		///
		GameObject *camera = Builder::getBuilder()->newCamera();
		GameObject *ambientLight = Builder::getBuilder()->newAmbientLight();
		GameObject *directionalLight = Builder::getBuilder()->
			newDirectionalLight();
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
		Material *emerald = new Material("material", *(new Texture2D()),
			Vector4f(0.0215F, 0.1745F, 0.0215F, 1.0F),
			Vector4f(0.07568F, 0.61424F, 0.07568F, 1.0F),
			Vector4f(0.633F, 0.727811F, 0.633F, 1.0F),
			0.6F * 128.0F);
		///
		/// Give the Cube, Sphere and Plane the Textured Emerald Material, and
		/// give Suzanne the non-Textured Emerald Material.
		///
		//delete plane->getComponentOfType<MeshRenderer>("MeshRenderer")->getMaterial();
		delete cube->getComponentOfType<MeshRenderer>("MeshRenderer")->getMaterial();
		//delete sphere->getComponentOfType<MeshRenderer>("MeshRenderer")->getMaterial();
		//delete suzanne->getComponentOfType<MeshRenderer>("MeshRenderer")->getMaterial();
		//plane->getComponentOfType<MeshRenderer>("MeshRenderer")->
		//	setMaterial(emerald);
		cube->getComponentOfType<MeshRenderer>("MeshRenderer")->
			setMaterial(emerald);
		//sphere->getComponentOfType<MeshRenderer>("MeshRenderer")->
		//	setMaterial(emerald);
		//suzanne->getComponentOfType<MeshRenderer>("MeshRenderer")->
		//	setMaterial(emerald);

		GameObject::getRoot()->start();
	}

	void TestGame::stop() {
		GameObject::getRoot()->stop();
	}

	void TestGame::update() {
		///
		/// Rotate the Directional Light to emulate sun light in the scene.
		///
		GameObject *sun = GameObject::getRoot()->getChild("Directional Light");
		Transform *sunTrans = sun->getComponentOfType<Transform>("Transform");
		sunTrans->rotate(sunTrans->getLocalRight(), 
			0.333F * GameTime::getGameTime()->getDeltaTimeS());

		GameObject::getRoot()->update();
	}
}