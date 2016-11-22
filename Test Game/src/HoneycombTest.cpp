#include "..\include\HoneycombTest.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\Honeycomb GE\include\base\GameTime.h"
#include "..\..\Honeycomb GE\include\base\GameInput.h"

#include "..\..\Honeycomb GE\include\geometry\Model.h"

#include "..\..\Honeycomb GE\include\geometry\Mesh.h"
#include "..\..\Honeycomb GE\include\graphics\Texture2D.h"
#include "..\..\Honeycomb GE\include\graphics\Material.h"
#include "..\..\Honeycomb GE\include\shader\ShaderProgram.h"
#include "..\..\Honeycomb GE\include\shader\simple\SimpleShader.h"
#include "..\..\Honeycomb GE\include\shader\phong\PhongShader.h"

#include "..\include\components\InputTransformable.h"
#include "..\..\Honeycomb GE\include\component\GameComponent.h"
#include "..\..\Honeycomb GE\include\component\physics\Transform.h"
#include "..\..\Honeycomb GE\include\component\render\CameraController.h"
#include "..\..\Honeycomb GE\include\component\render\MeshRenderer.h"
#include "..\..\Honeycomb GE\include\object\GameObject.h"
#include "..\..\Honeycomb GE\include\object\Builder.h"

#include "..\..\Honeycomb GE\include\math\MathUtils.h"
#include "..\..\Honeycomb GE\include\math\Vector3f.h"
#include "..\..\Honeycomb GE\include\math\Vector4f.h"
#include "..\..\Honeycomb GE\include\math\Quaternion.h"

#include "..\..\Honeycomb GE\include\component\light\BaseLight.h"
#include "..\..\Honeycomb GE\include\component\light\AmbientLight.h"
#include "..\..\Honeycomb GE\include\component\light\DirectionalLight.h"
#include "..\..\Honeycomb GE\include\component\light\PointLight.h"

using Honeycomb::Base::GameInput;

using Honeycomb::Geometry::Model;

using Honeycomb::Geometry::Mesh;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Graphics::Material;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::Simple::SimpleShader;
using Honeycomb::Shader::Phong::PhongShader;

using Honeycomb::Component::GameComponent;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::CameraController;
using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Object::GameObject;
using Honeycomb::Object::Builder;

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Math::Quaternion;
using Honeycomb::Math::Utils::PI;

using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Light::PointLight;

using HoneycombTest::Components::InputTransformable;

using namespace Honeycomb::Base;

namespace HoneycombTest {
	void TestGame::input() {
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

		suzanne->addComponent(*(new PointLight(BaseLight("pointLight", 1.0F, 
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)), 
			1.0F, 0.22F, 0.20F)));

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
			Vector3f(10.0F, 10.0F, 10.0F));

		sphere->getComponentOfType<Transform>("Transform")->setScale(
			Vector3f(PI, PI, PI));
		sphere->getComponentOfType<Transform>("Transform")->translate(
			Vector3f(PI, PI, PI));

		suzanne->getComponentOfType<Transform>("Transform")->setTranslation(
			Vector3f(-2.5F, 2.5F, 2.5F));


		///
		/// Create a fancy Emerald Material (textured and non-textured).
		///
		Material *emerald = new Material("material", nullptr,
			Vector4f(0.0215F, 0.1745F, 0.0215F, 1.0F),
			Vector4f(0.07568F, 0.61424F, 0.07568F, 1.0F),
			Vector4f(0.633F, 0.727811F, 0.633F, 1.0F),
			0.6F * 128.0F);
		Material *emeraldTex = new Material(*emerald);
		Texture2D *tex =
			cube->getComponentOfType<MeshRenderer>("MeshRenderer")->
			getMaterial()->getAlbedoTexture();
		emeraldTex->setAlbedoTexture(tex);


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
		GameObject *sun = GameObject::getRoot()->getChild("Directional Light");
		Transform *sunTrans = sun->getComponentOfType<Transform>("Transform");
		sunTrans->rotate(sunTrans->getLocalRight(), 
			0.333F * Time::getDeltaTimeSeconds());

		GameObject::getRoot()->update();
	}
}