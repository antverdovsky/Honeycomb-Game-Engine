#include "..\..\include\object\Builder.h"

#include <string>

#include "..\..\include\component\light\AmbientLight.h"
#include "..\..\include\component\light\BaseLight.h"
#include "..\..\include\component\light\DirectionalLight.h"
#include "..\..\include\component\light\PointLight.h"
#include "..\..\include\component\light\SpotLight.h"
#include "..\..\include\component\physics\Transform.h"
#include "..\..\include\component\render\CameraController.h"
#include "..\..\include\math\Vector4f.h"

using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Light::PointLight;
using Honeycomb::Component::Light::SpotLight;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::CameraController;
using Honeycomb::Geometry::Model;
using Honeycomb::Math::Vector4f;

namespace Honeycomb::Object {
	Builder* Builder::instance = nullptr; // Nullptr before being initialized

	const std::string Builder::CUBE_LOCATION = 
		"..\\Honeycomb GE\\res\\models\\default\\cube.fbx";
	const std::string Builder::PLANE_LOCATION =
		"..\\Honeycomb GE\\res\\models\\default\\plane.fbx";
	const std::string Builder::SPHERE_LOCATION =
		"..\\Honeycomb GE\\res\\models\\default\\sphere.fbx";
	const std::string Builder::SUZANNE_LOCATION =
		"..\\Honeycomb GE\\res\\models\\default\\suzanne.fbx";

	Builder::~Builder() {

	}

	Builder* Builder::getBuilder() {
		if (instance == nullptr)
			instance = new Builder();

		return instance;
	}

	GameObject* Builder::newAmbientLight() {
		// Initialize the Ambient Light Game Object
		GameObject *ambLight = new GameObject("Ambient Light");

		// Initialize the Ambient Light Game Components
		AmbientLight *aL = new AmbientLight();
		Transform *trans = new Transform();

		// Add the initialized components to the Ambient Light Game Object
		ambLight->addComponent(*aL);
		ambLight->addComponent(*trans);

		return ambLight; // Return the Ambient Light Game Object
	}

	GameObject* Builder::newCamera() {
		// Initialize the Camera Game Object
		GameObject *camera = new GameObject("Camera");

		// Initialize the Camera Game Component
		CameraController *cam = new CameraController();
		Transform *trans = new Transform();

		// Add the initialized components to the Camera Game Object
		camera->addComponent(*cam);
		camera->addComponent(*trans);

		return camera; // Return the Camera Game Object
	}

	GameObject* Builder::newDirectionalLight() {
		// Initialize the Directional Light Game Object
		GameObject *dirLight = new GameObject("Directional Light");

		// Initialize the Directional Light Game Components
		DirectionalLight *dL = new DirectionalLight();
		Transform *trans = new Transform();

		// Add the initialized components to the Directional Light Game Object
		dirLight->addComponent(*dL);
		dirLight->addComponent(*trans);

		return dirLight; // Return the Directional Light Game Object
	}

	GameObject* Builder::newCube() {
		return newDefaultImport("Cube", CUBE_LOCATION);
	}

	GameObject* Builder::newModel(std::string path) {
		// Create a Model and return the clone of it (again, do not delete the
		// model so that the Model class may later reuse this model if needed).
		GameObject* obj = Model::loadModel(path).getGameObjectClone();
		GameObject::getRoot().addChild(*obj);

		return obj;
	}

	GameObject* Builder::newPlane() {
		return newDefaultImport("Plane", PLANE_LOCATION);
	}

	GameObject* Builder::newPointLight() {
		// Initialize the Point Light Game Object
		GameObject *pntLight = new GameObject("Point Light");

		// Initialize the Point Light Game Components
		PointLight *pL = new PointLight();
		Transform *trans = new Transform();

		// Add the initialized components to the Point Light Game Object
		pntLight->addComponent(*pL);
		pntLight->addComponent(*trans);

		return pntLight; // Return the Point Light Game Object
	}

	GameObject* Builder::newSphere() {
		return newDefaultImport("Sphere", SPHERE_LOCATION);
	}

	GameObject* Builder::newSpotLight() {
		// Initialize the Spot Light Game Object
		GameObject *sptLight = new GameObject("Spot Light");

		// Initialize the Spot Light Game Components
		SpotLight *sL = new SpotLight();
		Transform *trans = new Transform();

		// Add the initialized components to the Spot Light Game Object
		sptLight->addComponent(*sL);
		sptLight->addComponent(*trans);

		return sptLight; // Return the Spot Light Game Object
	}

	GameObject* Builder::newSuzanne() {
		return newDefaultImport("Suzanne", SUZANNE_LOCATION);
	}

	Builder::Builder() {

	}

	GameObject* Builder::newDefaultImport(std::string name, std::string path) {
		// Get the parent model and extract the child with the given name from
		// it. Add the child to the root so that it may be instantiated.
		GameObject *parent = Model::loadModel(path).getGameObjectClone();
		GameObject *child = parent->getChild(name);
		GameObject::getRoot().addChild(*child);

		// Recycle the parent and return the child (keep the Model since the
		// Model class will use it to avoid re-importation of models).
		delete parent;
		return child;
	}
}