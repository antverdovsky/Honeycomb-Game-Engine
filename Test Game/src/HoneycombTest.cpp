#include "..\include\HoneycombTest.h"

#include "..\..\Honeycomb GE\include\HoneycombEngine.h"
#include "..\..\Honeycomb GE\include\render\Renderer.h"
#include "..\..\Honeycomb GE\include\render\deferred\DeferredRenderer.h"
#include "..\include\components\InputTransformable.h"
#include "..\..\Honeycomb GE\include\debug\Logger.h"

using namespace HoneycombEngine;
using namespace HoneycombTest::Components;
using Honeycomb::Debug::Logger;
using Honeycomb::Render::Renderer;
using Honeycomb::Render::Deferred::DeferredRenderer;

namespace HoneycombTest {
	void TestGame::input() {

	}

	void TestGame::render() {

	}

	void TestGame::start() {
		// Build the Skybox and send to the Renderer
		std::string skyboxDir =
			"..\\Honeycomb GE\\res\\textures\\default\\aurora_skybox\\";
		std::string skyboxTex[6] = {
			skyboxDir + "right.bmp",
			skyboxDir + "left.bmp",
			skyboxDir + "top.bmp",
			skyboxDir + "bottom.bmp",
			skyboxDir + "back.bmp",
			skyboxDir + "front.bmp"
		};
		Cubemap skybox;
		skybox.initialize();
		skybox.setFaces(skyboxTex);
		Renderer::getRenderer()->setSkybox(skybox);

		// Create the Post Processing Shaders and add to the Renderer
		this->inversionShader.initialize();
		this->inversionShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"post-processing\\postProcessingVS.glsl", 0x8B31);
		this->inversionShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"post-processing\\inversionFS.glsl", 0x8B30);
		this->inversionShader.finalizeShaderProgram();

		this->sharpShader.initialize();
		this->sharpShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"post-processing\\postProcessingVS.glsl", 0x8B31);
		this->sharpShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"post-processing\\sharpFS.glsl", 0x8B30);
		this->sharpShader.finalizeShaderProgram();

		Renderer::getRenderer()->getPostShaders().push_back(this->sharpShader);
		Renderer::getRenderer()->setDoPostProcess(false);

		// Import all of the mesh game objects and construct them
		this->car = Builder::getBuilder()->
			newModel("..\\Test Game\\res\\models\\car.fbx");
		this->cube = Builder::getBuilder()->newCube();
		this->plane = Builder::getBuilder()->newPlane();
		this->sphere = Builder::getBuilder()->newSphere();
		this->suzanne = Builder::getBuilder()->newSuzanne();

		// Give the Plane a special material with a colorful texture
		Material *colorMaterial = new Material(
			this->plane->getComponent<MeshRenderer>()->getMaterial());
		Texture2D *colorTexture = new Texture2D();
		colorTexture->initialize();
		colorTexture->
			setImageData("..\\Test Game\\res\\textures\\colors.bmp");
		colorMaterial->glSampler2Ds.setValue("albedoTexture", *colorTexture);
		this->plane->getComponent<MeshRenderer>()->
			setMaterial(*colorMaterial);

		// Give Suzanne an Input Transformable Component
		InputTransformable *suzInputTranfs = new InputTransformable(
			GameInput::KEY_CODE_UP, GameInput::KEY_CODE_DOWN,
			GameInput::KEY_CODE_LEFT, GameInput::KEY_CODE_RIGHT,
			GameInput::KEY_CODE_COMMA, GameInput::KEY_CODE_PERIOD,
			GameInput::KEY_CODE_I, GameInput::KEY_CODE_K,
			GameInput::KEY_CODE_J, GameInput::KEY_CODE_L,
			GameInput::KEY_CODE_U, GameInput::KEY_CODE_O,
			GameInput::KEY_CODE_Z, GameInput::KEY_CODE_X,
			GameInput::KEY_CODE_C, GameInput::KEY_CODE_V,
			GameInput::KEY_CODE_B, GameInput::KEY_CODE_N,
			3.5F, 3.5F, 3.5F, Space::GLOBAL);
		this->suzanne->addComponent(*suzInputTranfs);

		// Construct a default Ambient and Directional Light; decrease the
		// intensity of the lights so they don't overwhelm the scene
		this->ambient = Builder::getBuilder()->newAmbientLight();
		this->directional = Builder::getBuilder()->newDirectionalLight();
		this->ambient->getComponent<AmbientLight>()->setIntensity(0.22F);
		this->directional->getComponent<DirectionalLight>()->
			setIntensity(0.33F);

		// Construct a default Camera and give it a default Input Transformable
		// component and a moderately strong Directional Light.
		this->camera = Builder::getBuilder()->newCamera();
		InputTransformable *camTransf = new InputTransformable();
		DirectionalLight *dirLight = new DirectionalLight();
		dirLight->setIntensity(0.66F);
		this->camera->addComponent(*camTransf);
		this->camera->addComponent(*dirLight);
		
		// Scale and position the Game Objects
		this->plane->getComponent<Transform>()->setScale(
			Vector3f(25.0F, 1.0F, 25.0F));
		this->cube->getComponent<Transform>()->setTranslation(
			Vector3f(-2.5F, 1.0F, -5.0F));
		this->sphere->getComponent<Transform>()->setScale(
			Vector3f(PI, PI, PI));
		this->sphere->getComponent<Transform>()->setTranslation(
			Vector3f(3.0F, PI, -7.5F));
		this->car->getComponent<Transform>()->setTranslation(
			Vector3f(-3.0F, 1.36F, 10.0F));
		this->car->getComponent<Transform>()->setScale(
			Vector3f(2.0F, 2.0F, 2.0F));

		// Construct a left and right spotlight for the front of the car and
		// add to the car (similar to headlights).
		GameObject *carHeadlightL = Builder::getBuilder()->newSpotLight();
		GameObject *carHeadlightR = Builder::getBuilder()->newSpotLight();
		this->car->addChild(*carHeadlightL);
		this->car->addChild(*carHeadlightR);
		carHeadlightL->getComponent<SpotLight>()->setAttenuation(
			Attenuation(1.0F, 0.0F, 0.05F));
		carHeadlightL->getComponent<SpotLight>()->getRange() = 20.0F;
		carHeadlightL->getComponent<SpotLight>()->getAngle() = PI / 2.0F;
		carHeadlightL->getComponent<SpotLight>()->setIntensity(4.0F);
		carHeadlightL->getComponent<Transform>()->setTranslation(
			Vector3f(-4.391F, 0.309F, 5.821F));
		carHeadlightR->getComponent<SpotLight>()->setAttenuation(
			Attenuation(1.0F, 0.0F, 0.05F));
		carHeadlightR->getComponent<SpotLight>()->getRange() = 20.0F;
		carHeadlightR->getComponent<SpotLight>()->getAngle() = PI / 2.0F;
		carHeadlightR->getComponent<SpotLight>()->setIntensity(4.0F);
		carHeadlightR->getComponent<Transform>()->setTranslation(
			Vector3f( -1.391F, 0.309F, 5.821F));

		// Add all of the initialized objects to the Game Scene hierarchy
		this->gameScene.addChild(*this->car);
		this->gameScene.addChild(*this->cube);
		this->gameScene.addChild(*this->plane);
		this->gameScene.addChild(*this->sphere);
		this->gameScene.addChild(*this->suzanne);
		this->gameScene.addChild(*this->ambient);
		this->gameScene.addChild(*this->directional);
		this->gameScene.addChild(*this->camera);
		
		// Start the Game Scene and set it as the active scene
		this->gameScene.start();
		GameScene::setActiveScene(this->gameScene);
	}

	void TestGame::stop() {
		this->gameScene.stop();
	}

	void TestGame::update() {

	}
}