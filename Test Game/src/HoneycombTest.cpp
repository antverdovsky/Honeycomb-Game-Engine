#include "../include/HoneycombTest.h"

#include "../../Honeycomb GE/include/HoneycombEngine.h"
#include "../../Honeycomb GE/include/render/Renderer.h"
#include "../../Honeycomb GE/include/render/deferred/DeferredRenderer.h"
#include "../include/components/InputTransformable.h"
#include "../../Honeycomb GE/include/debug/Logger.h"

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
//		DeferredRenderer::getDeferredRenderer()->setFinalTexture(DeferredRenderer::NORMAL);
//		DeferredRenderer::getDeferredRenderer()->setColorSpace(DeferredRenderer::LINEAR);

		// Build the Skybox and send to the Renderer
		std::string skyboxDir =
			"../Honeycomb GE/res/textures/default/aurora_skybox/";
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
		this->inversionShader.addShader("../Honeycomb GE/res/shaders/"
			"post-processing/postProcessingVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->inversionShader.addShader("../Honeycomb GE/res/shaders/"
			"post-processing/inversionFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->inversionShader.finalizeShaderProgram();

		this->sharpShader.initialize();
		this->sharpShader.addShader("../Honeycomb GE/res/shaders/"
			"post-processing/postProcessingVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->sharpShader.addShader("../Honeycomb GE/res/shaders/"
			"post-processing/sharpFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->sharpShader.finalizeShaderProgram();

		Renderer::getRenderer()->getPostShaders().push_back(this->sharpShader);
		Renderer::getRenderer()->setDoPostProcess(false);
		
		// Import all of the mesh game objects and construct them
		this->car = Builder::getBuilder()->
			newModel("../Test Game/res/models/car.fbx");
		this->cube = Builder::getBuilder()->
			newModel("../Test Game/res/models/brick-cube/cube.fbx");
		this->cube2 = Builder::getBuilder()->
			newModel("../Test Game/res/models/brick-cube2/cube.fbx");
		this->plane = Builder::getBuilder()->newPlane();
		this->sphere = Builder::getBuilder()->newSphere();
		this->suzanne = Builder::getBuilder()->newSuzanne();
		this->earth = Builder::getBuilder()->newModel(
			"../Test Game/res/models/planet-earth/earth.fbx");

		// Give the plane a textured material
		Material *colorMaterial = new Material(
			this->plane->getComponent<MeshRenderer>()->getMaterial());
		Texture2D *colorTexture = new Texture2D();
		colorTexture->initialize();
		colorTexture->
			setImageData("../Test Game/res/textures/colors.bmp");
		colorMaterial->glSampler2Ds.setValue("diffuseTexture.sampler", 
			*colorTexture);
		colorMaterial->glFloats.setValue("shininess", 128.0F);
		colorMaterial->glVector2fs.setValue("diffuseTexture.tiling",
			Vector2f(10.0F, 10.0F));
		this->plane->getComponent<MeshRenderer>()->
			setMaterial(*colorMaterial);

		// Add a displacement map to the second cube. (NOTE: Blender won't
		// export the displacement map for some reason... possible bug?)
		Material *cube2Material = new Material(
			this->cube2->getChild("Cube")->getComponent<MeshRenderer>()->getMaterial());
		Texture2D *displacementTexture = new Texture2D();
		displacementTexture->initialize();
		displacementTexture->setImageData("../Test Game/res/textures/brick-cube2/displacement.bmp");
		cube2Material->glSampler2Ds.setValue("displacementTexture.sampler", *displacementTexture);
		this->cube2->getChild("Cube")->getComponent<MeshRenderer>()->setMaterial(*cube2Material);

		// Give the sphere and suzanne a special reflective material (skybox)
		Material *reflectiveMaterial = new Material(
			this->sphere->getComponent<MeshRenderer>()->getMaterial());
		reflectiveMaterial->glFloats.setValue("refractiveIndex", 1.55F);
		reflectiveMaterial->glFloats.setValue("reflectionStrength", 1.0F);
		reflectiveMaterial->glVector3fs.setValue("specularColor", 
			Vector3f(1.0F, 1.0F, 1.0F));
		reflectiveMaterial->glFloats.setValue("shininess", 64.0F);
		this->suzanne->getComponent<MeshRenderer>()->setMaterial(
			*reflectiveMaterial);
		this->sphere->getComponent<MeshRenderer>()->setMaterial(
			*reflectiveMaterial);
		this->car->getChild("Body")->getComponent<MeshRenderer>()->setMaterial(
			*reflectiveMaterial);

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

		// Give Suzanne a Spot Light and a Point Light
		GameObject *suzSpLight = Builder::getBuilder()->newSpotLight();
		GameObject *suzPtLight = Builder::getBuilder()->newPointLight();
		suzSpLight->getComponent<SpotLight>()->setColor(
			Vector3f(0.0F, 0.0F, 1.0F));
		suzSpLight->getComponent<SpotLight>()->setIntensity(5.0F);
		suzSpLight->getComponent<SpotLight>()->getRange() = 30.0F;
		suzSpLight->getComponent<SpotLight>()->getAngle() = PI / 2.0F;
		suzPtLight->getComponent<PointLight>()->setColor(
			Vector3f(1.0F, 0.0F, 0.0F));
		suzPtLight->getComponent<PointLight>()->setIntensity(2.5F);
		suzPtLight->getComponent<PointLight>()->setRange(10.0F);
		suzanne->addChild(*suzSpLight);
		suzanne->addChild(*suzPtLight);

		// Construct a default Ambient and Directional Light; decrease the
		// intensity of the lights so they don't overwhelm the scene
		this->ambient = Builder::getBuilder()->newAmbientLight();
		this->directional = Builder::getBuilder()->newDirectionalLight();
		this->ambient->getComponent<AmbientLight>()->setIntensity(0.10F);
		this->directional->getComponent<DirectionalLight>()->
			setIntensity(0.10F);

		// Construct a default Camera and give it a default Input Transformable
		this->camera = Builder::getBuilder()->newCamera();
		InputTransformable *camTransf = new InputTransformable();
		this->camera->addComponent(*camTransf);
		
		// Scale and position the Game Objects
		this->plane->getComponent<Transform>()->setScale(
			Vector3f(25.0F, 1.0F, 25.0F));
		this->cube->getComponent<Transform>()->setTranslation(
			Vector3f(-2.5F, 1.0F, -5.0F));
		this->cube2->getComponent<Transform>()->setTranslation(
			Vector3f(0.0F, 1.0F, -3.5F));
		this->sphere->getComponent<Transform>()->setScale(
			Vector3f(PI, PI, PI));
		this->sphere->getComponent<Transform>()->setTranslation(
			Vector3f(3.0F, 0.0F, -7.5F));
		this->car->getComponent<Transform>()->setTranslation(
			Vector3f(-3.0F, 1.36F, 10.0F));
		this->car->getComponent<Transform>()->setScale(
			Vector3f(2.0F, 2.0F, 2.0F));
		this->suzanne->getComponent<Transform>()->setTranslation(
			Vector3f(2.0F, 2.5F, 3.0F));
		this->directional->getComponent<Transform>()->rotate(
			Vector3f::getGlobalRight(), -PI / 4);
		this->earth->getComponent<Transform>()->setScale(
			Vector3f(5.0F, 5.0F, 5.0F));
		this->earth->getComponent<Transform>()->setTranslation(
			Vector3f(7.5F, 5.0F, 5.0F));

		this->cube->addComponent(*suzInputTranfs->clone());
		this->cube2->addComponent(*suzInputTranfs->clone());

		// Construct a left and right spotlight for the front of the car and
		// add to the car (similar to headlights).
		GameObject *carHeadlightL = Builder::getBuilder()->newSpotLight();
		GameObject *carHeadlightR = Builder::getBuilder()->newSpotLight();
		this->car->addChild(*carHeadlightL);
		this->car->addChild(*carHeadlightR);
		carHeadlightL->getComponent<SpotLight>()->setAttenuation(
			Attenuation(1.0F, 0.0F, 0.05F));
		carHeadlightL->getComponent<SpotLight>()->getRange() = 30.0F;
		carHeadlightL->getComponent<SpotLight>()->getAngle() = PI / 2.0F;
		carHeadlightL->getComponent<SpotLight>()->setIntensity(4.0F);
		carHeadlightL->getComponent<Transform>()->setTranslation(
			Vector3f(-4.391F, 0.309F, 5.821F));
		carHeadlightR->getComponent<SpotLight>()->setAttenuation(
			Attenuation(1.0F, 0.0F, 0.05F));
		carHeadlightR->getComponent<SpotLight>()->getRange() = 30.0F;
		carHeadlightR->getComponent<SpotLight>()->getAngle() = PI / 2.0F;
		carHeadlightR->getComponent<SpotLight>()->setIntensity(4.0F);
		carHeadlightR->getComponent<Transform>()->setTranslation(
			Vector3f( -1.391F, 0.309F, 5.821F));

		// Add all of the initialized objects to the Game Scene hierarchy
		this->gameScene.addChild(*this->car);
		this->gameScene.addChild(*this->cube);
		this->gameScene.addChild(*this->cube2);
		this->gameScene.addChild(*this->plane);
		this->gameScene.addChild(*this->sphere);
		this->gameScene.addChild(*this->earth);
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