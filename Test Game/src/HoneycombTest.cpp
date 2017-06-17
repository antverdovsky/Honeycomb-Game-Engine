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
		// Build the Skybox and send to the Renderer
		std::string skyboxDir =
			"../Honeycomb GE/res/textures/default/aurora_skybox/";
		CubemapTextureTarget targets[6] = {
			CubemapTextureTarget::RIGHT,
			CubemapTextureTarget::LEFT,
			CubemapTextureTarget::TOP,
			CubemapTextureTarget::BOTTOM,
			CubemapTextureTarget::BACK,
			CubemapTextureTarget::FRONT
		};
		ImageIO skyboxTex[6] = {
			ImageIO(skyboxDir + "right.bmp"),
			ImageIO(skyboxDir + "left.bmp"),
			ImageIO(skyboxDir + "top.bmp"),
			ImageIO(skyboxDir + "bottom.bmp"),
			ImageIO(skyboxDir + "back.bmp"),
			ImageIO(skyboxDir + "front.bmp")
		};
		Cubemap skybox;
		skybox.initialize();
		skybox.setFacesDataIO(6, targets, skyboxTex);
		Renderer::getRenderer()->setSkybox(skybox);

		// Import all of the mesh game objects and construct them
		this->car = GameObjectFactory::getFactory().
			newModel("../Test Game/res/models/car.fbx");
		this->cube = GameObjectFactory::getFactory().
			newModel("../Test Game/res/models/brick-cube/cube.fbx");
		this->plane = GameObjectFactory::getFactory().newPlane();
	
		// Give the plane a textured material
		Material *colorMaterial = new Material(
			this->plane->getComponent<MeshRenderer>().getMaterial());
		Texture2D *colorTexture = new Texture2D();
		colorTexture->initialize();
		colorTexture-> // vvvvvv this is a leak here but whatever for now...
			setImageDataIO(ImageIO("../Test Game/res/textures/colors.bmp"));
		colorTexture->setAnisotropicFiltering(8);
		colorMaterial->glSampler2Ds.setValue("albedoTexture.sampler", 
			*colorTexture);
		colorMaterial->glFloats.setValue("shininess", 128.0F);
		colorMaterial->glVector2fs.setValue("globalTiling",
			Vector2f(10.0F, 10.0F));
		colorMaterial->glVector3fs.setValue("diffuseColor", Vector3f(1, 1, 0));
		this->plane->getComponent<MeshRenderer>().
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
		this->car->addComponent(*suzInputTranfs);

		// Construct a default Ambient and Directional Light; decrease the
		// intensity of the lights so they don't overwhelm the scene
		this->ambient = GameObjectFactory::getFactory().newAmbientLight();
		this->directional = GameObjectFactory::getFactory().newDirectionalLight();
		this->ambient->getComponent<AmbientLight>().setIntensity(0.01F);
		this->directional->getComponent<DirectionalLight>().
			setIntensity(0.05F);
		this->directional->getComponent<DirectionalLight>().
			getShadow().setShadowType(ShadowType::SHADOW_VARIANCE_AA);
		this->directional->getComponent<DirectionalLight>().
			getShadow().setIntensity(1.0F);
		this->directional->addComponent(*suzInputTranfs->clone());

		// Construct a default Camera and give it a default Input Transformable
		this->camera = GameObjectFactory::getFactory().newCamera();
		InputTransformable *camTransf = new InputTransformable();
		this->camera->addComponent(*camTransf);
		
		// Scale and position the Game Objects
		this->plane->getComponent<Transform>().setScale(
			Vector3f(15.0F, 1.0F, 25.0F));
		this->cube->getComponent<Transform>().setTranslation(
			Vector3f(-2.5F, 1.0F, -5.0F));
		this->car->getComponent<Transform>().setTranslation(
			Vector3f(-3.0F, 1.36F, 8.0F));
		this->car->getComponent<Transform>().setScale(
			Vector3f(2.0F, 2.0F, 2.0F));
		this->directional->getComponent<Transform>().rotate(
			Vector3f::getGlobalRight(), -PI / 4);

		this->cube->addComponent(*suzInputTranfs->clone());

		// Construct a left and right spotlight for the front of the car and
		// add to the car (similar to headlights).
		auto carHeadlightL = GameObjectFactory::getFactory().newSpotLight();
		auto carHeadlightR = GameObjectFactory::getFactory().newSpotLight();
//		this->car->addChild(*carHeadlightL);
//		this->car->addChild(*carHeadlightR);
		carHeadlightL->getComponent<SpotLight>().setAttenuation(
			Attenuation(1.0F, 0.0F, 0.05F));
		carHeadlightL->getComponent<SpotLight>().getRange() = 15.0F;
		carHeadlightL->getComponent<SpotLight>().getAngle() = PI / 2;
		carHeadlightL->getComponent<SpotLight>().setIntensity(8.0F);
		carHeadlightL->getComponent<SpotLight>().getShadow().setIntensity(1.0F);
		carHeadlightL->getComponent<Transform>().setTranslation(
			Vector3f(-4.391F, 0.709F, 3.321F));
		carHeadlightR->getComponent<SpotLight>().setAttenuation(
			Attenuation(1.0F, 0.0F, 0.05F));
		carHeadlightR->getComponent<SpotLight>().getRange() = 15.0F;
		carHeadlightR->getComponent<SpotLight>().getAngle() = PI / 2;
		carHeadlightR->getComponent<SpotLight>().setIntensity(8.0F);
		carHeadlightR->getComponent<SpotLight>().getShadow().setIntensity(1.0F);
		carHeadlightR->getComponent<Transform>().setTranslation(
			Vector3f( -1.391F, 0.709F, 3.321F));

		// Add all of the initialized objects to the Game Scene hierarchy
		this->gameScene.addChild(*this->car);
		this->gameScene.addChild(*this->cube);
		this->gameScene.addChild(*this->plane);
		this->gameScene.addChild(*this->ambient);
		this->gameScene.addChild(*this->directional);
		this->gameScene.addChild(*this->camera);
		
		// Start the Game Scene and set it as the active scene
		this->gameScene.start();
		GameScene::setActiveScene(this->gameScene);

		GameWindow::getGameWindow()->setWindowTitle("Honeycomb Test Game"); 
	}

	void TestGame::stop() {
		this->gameScene.stop();
	}

	void TestGame::update() {

	}
}