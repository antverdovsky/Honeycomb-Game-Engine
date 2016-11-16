#include "..\include\HoneycombTest.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\Honeycomb GE\include\base\GameInput.h"

#include "..\..\Honeycomb GE\include\geometry\importer\Model.h"
#include "..\..\Honeycomb GE\include\geometry\importer\Model_OBJ.h"

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

#include "..\..\Honeycomb GE\include\math\Vector3f.h"
#include "..\..\Honeycomb GE\include\math\Vector4f.h"
#include "..\..\Honeycomb GE\include\math\Quaternion.h"

#include "..\..\Honeycomb GE\include\component\light\BaseLight.h"
#include "..\..\Honeycomb GE\include\component\light\AmbientLight.h"

using Honeycomb::Base::GameInput;

using Honeycomb::Geometry::Importer::Model;
using Honeycomb::Geometry::Importer::Model_OBJ;

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

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Math::Quaternion;

using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::DirectionalLight;

using HoneycombTest::Components::InputTransformable;

namespace HoneycombTest {
	std::string TestGame::CUBE_MODEL_LOC = 
		"..\\Honeycomb GE\\res\\models\\default\\cube.obj";
	std::string TestGame::CUBE_TEXTURE_LOC =
		"..\\Honeycomb GE\\res\\textures\\default\\Checkerboard.bmp";

	void TestGame::input() {
		if (GameInput::getGameInput()->getKeyDown(
				GameInput::KEY_CODE_LEFT_BRACKET)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (GameInput::getGameInput()->getKeyDown(
				GameInput::KEY_CODE_RIGHT_BRACKET)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (GameInput::getGameInput()->getKeyDown(
				GameInput::KEY_CODE_1)) {
			this->cubeObject->getComponentOfType<MeshRenderer>("MeshRenderer")
				->getMaterial().getAlbedoColor() = 
					Vector4f(1.0F, 0.0F, 0.0F, 1.0F);
		}
		else if (GameInput::getGameInput()->getKeyDown(
			GameInput::KEY_CODE_2)) {
			this->cubeObject->getComponentOfType<MeshRenderer>("MeshRenderer")
				->getMaterial().getAlbedoColor() = 
					Vector4f(0.0F, 1.0F, 0.0F, 1.0F);
		}
		else if (GameInput::getGameInput()->getKeyDown(
			GameInput::KEY_CODE_3)) {
			this->cubeObject->getComponentOfType<MeshRenderer>("MeshRenderer")
				->getMaterial().getAlbedoColor() = 
					Vector4f(0.0F, 0.0F, 1.0F, 1.0F);
		}
		else if (GameInput::getGameInput()->getKeyDown(
			GameInput::KEY_CODE_4)) {
			this->cubeObject->getComponentOfType<MeshRenderer>("MeshRenderer")
				->getMaterial().getAlbedoColor() = 
					Vector4f(1.0F, 1.0F, 1.0F, 1.0F);
		}
		else if (GameInput::getGameInput()->getKeyDown(
			GameInput::KEY_CODE_5)) {
			this->cubeObject->getComponentOfType<MeshRenderer>("MeshRenderer")
				->getMaterial().getAlbedoColor() =
				Vector4f(1.0F, 0.0F, 0.0F, 0.25F);
		}
		else if (GameInput::getGameInput()->getKeyDown(
			GameInput::KEY_CODE_6)) {
			this->cubeObject->getComponentOfType<MeshRenderer>("MeshRenderer")
				->getMaterial().getAlbedoColor() =
				Vector4f(0.0F, 1.0F, 0.0F, 0.25F);
		}
		else if (GameInput::getGameInput()->getKeyDown(
			GameInput::KEY_CODE_7)) {
			this->cubeObject->getComponentOfType<MeshRenderer>("MeshRenderer")
				->getMaterial().getAlbedoColor() =
				Vector4f(0.0F, 0.0F, 1.0F, 0.25F);
		}
		else if (GameInput::getGameInput()->getKeyDown(
			GameInput::KEY_CODE_8)) {
			this->cubeObject->getComponentOfType<MeshRenderer>("MeshRenderer")
				->getMaterial().getAlbedoColor() =
				Vector4f(1.0F, 1.0F, 1.0F, 0.25F);
		}

		GameObject::getRoot()->input();
	}

	void TestGame::render() {
		GameObject::getRoot()->render();
	}

	void TestGame::start() {
		// Import the Cube Model
		Model *cubeModel = Model_OBJ::loadModel(CUBE_MODEL_LOC);

		// Initialize the Cube Mesh, Shader and Texture
		Mesh *cubeMesh = new Mesh(*cubeModel);
		ShaderProgram *cubeShader = PhongShader::getPhongShader();
		Texture2D *cubeTexture = new Texture2D();

		///// TODO [Remove]: Temporary Cube in the Back
		Mesh *backCubeMesh = new Mesh(*cubeModel);
		Material *backCubeMaterial = new Material();
		MeshRenderer *backCubeRenderer = 
			new MeshRenderer(*backCubeMesh, *cubeShader, *backCubeMaterial);
		Transform *backCubeTransform =
			new Transform(Vector3f(0.0F, 0.0F, -7.5F), Quaternion(),
				Vector3f(1.0F, 1.0F, 1.0F));
		GameObject *backCubeObject = new GameObject("back cube");
		backCubeObject->addComponent(*backCubeRenderer);
		backCubeObject->addComponent(*backCubeTransform);

		// Initialize the Texture
		// [TODO] Add method(s) to Texture2D class which will allow easier
		// initialization...
		cubeTexture->setImageData(CUBE_TEXTURE_LOC, GL_RGB, GL_RGB);
		cubeTexture->setTextureFiltering(GL_NEAREST, GL_NEAREST);
		cubeTexture->setTextureWrap(GL_REPEAT, GL_REPEAT);
		cubeTexture->genMipMap();

		Material *cubeMaterial = new Material(cubeTexture, 
			Vector4f(1.0F, 1.0F, 1.0F, 0.1F));

		// Create Cube Components & the Cube Object
		MeshRenderer *cubeRenderer = new MeshRenderer(*cubeMesh, *cubeShader,
			*cubeMaterial);
		Transform *cubeTransform =
			new Transform(Vector3f(0.0F, 0.0F, -5.0F), Quaternion(), 
				Vector3f(1.0F, 1.0F, 1.0F));
		InputTransformable *cubeInputTransformable = new InputTransformable(
			GameInput::KEY_CODE_UP, GameInput::KEY_CODE_DOWN,
			GameInput::KEY_CODE_LEFT, GameInput::KEY_CODE_RIGHT,
			GameInput::KEY_CODE_COMMA, GameInput::KEY_CODE_PERIOD,
			GameInput::KEY_CODE_R, GameInput::KEY_CODE_T,
			GameInput::KEY_CODE_F, GameInput::KEY_CODE_G,
			GameInput::KEY_CODE_V, GameInput::KEY_CODE_B,
			0.05F, 0.05F);
		this->cubeObject = new GameObject("Cube");
		this->cubeObject->addComponent(*cubeRenderer);
		this->cubeObject->addComponent(*cubeTransform);
		this->cubeObject->addComponent(*cubeInputTransformable);

		// Create Camera Components & Camera Object
		CameraController *cameraController =
			new CameraController(CameraController::CameraType::PERSPECTIVE,
				100.0F, 0.3F, 75.0F, 768.0F, 1024.0F); // [TODO]: Perspective Size!!!
		Transform *cameraTransform =
			new Transform(Vector3f(),
				Quaternion(Vector3f::getGlobalUp(), 3.1415926),
				Vector3f(1.0F, 1.0F, 1.0F));
		InputTransformable *cameraInputTransformable =
			new InputTransformable();
		DirectionalLight *directionalLight = new DirectionalLight(
			BaseLight("directionalLight", 1.0F, Vector3f(1.0F, 1.0F, 1.0F)));
		this->cameraObject = new GameObject("Camera");
		this->cameraObject->addComponent(*cameraController);
		this->cameraObject->addComponent(*cameraTransform);
		this->cameraObject->addComponent(*cameraInputTransformable);
		this->cameraObject->addComponent(*directionalLight);

		// Create ambient light
		GameObject *ambientObject = new GameObject("Ambient Light");
		AmbientLight *ambientComponent = new AmbientLight(
			BaseLight("ambientLight", 0.25F, Vector3f(1.0F, 1.0F, 1.0F)));
		ambientObject->addComponent(*ambientComponent);

		delete cubeModel;

		GameObject::getRoot()->start();
	}

	void TestGame::stop() {
		GameObject::getRoot()->stop();
	}

	void TestGame::update() {
		GameObject::getRoot()->update();
	}
}