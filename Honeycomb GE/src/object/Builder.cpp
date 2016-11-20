#include "..\..\include\object\Builder.h"

#include <string>

#include "..\..\include\component\light\AmbientLight.h"
#include "..\..\include\component\light\BaseLight.h"
#include "..\..\include\component\light\DirectionalLight.h"
#include "..\..\include\component\physics\Transform.h"
#include "..\..\include\component\render\CameraController.h"
#include "..\..\include\math\Vector4f.h"

using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::DirectionalLight;
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

	Builder::~Builder() {
		// Destroy all the imported models and built objects
//		for (int i = 0; i < this->importedModels.size(); i++)
//			delete this->importedModels.at(i);
//		for (int i = 0; i < this->builtObjects.size(); i++)
//			delete this->builtObjects.at(i);
	}

	Builder* Builder::getBuilder() {
		if (instance == nullptr)
			instance = new Builder();

		return instance;
	}

	GameObject* Builder::newAmbientLight() {
		//
		// TODO: Find way to unify code for ambient, camera, directional
		//

		// Try to find the object, if it has already been built
		GameObject *obj = nullptr;

		// If we cannot find the object, then it has not been built yet, so
		// build it and add it to the the built objects list. Then, return the
		// newly built object.
		if (obj == nullptr) {
			obj = new GameObject("Ambient Light", nullptr);
			BaseLight bL = BaseLight("ambientLight", 1.0F,
				Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
			AmbientLight *aL = new AmbientLight(bL);

			/// TODO: Why doesn't Transform() work without namespace???
			obj->addComponent(*(new Honeycomb::Component::Physics::Transform()));
			obj->addComponent(*aL);
			GameObject::getRoot()->addChild(*obj);

			return obj;
		}

		return obj->clone(); // Otherwise, clone the existing object.
	}

	GameObject* Builder::newCamera() {
		// Try to find the object, if it has already been built
		GameObject *obj = nullptr;

		// If we cannot find the object, then it has not been built yet, so
		// build it and add it to the the built objects list. Then, return the
		// newly built object.
		if (obj == nullptr) {
			obj = new GameObject("Camera", nullptr);
			CameraController *cam = new CameraController();

			obj->addComponent(*(new Honeycomb::Component::Physics::Transform()));
			obj->addComponent(*cam);
			GameObject::getRoot()->addChild(*obj);

			return obj;
		}

		return obj->clone(); // Otherwise, clone the existing object.
	}

	GameObject* Builder::newDirectionalLight() {
		// Try to find the object, if it has already been built
		GameObject *obj = nullptr;

		// If we cannot find the object, then it has not been built yet, so
		// build it and add it to the the built objects list. Then, return the
		// newly built object.
		if (obj == nullptr) {
			obj = new GameObject("Directional Light", nullptr);
			BaseLight bL = BaseLight("directionalLight", 1.0F,
				Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
			DirectionalLight *dL = new DirectionalLight(bL);

			obj->addComponent(*(new Honeycomb::Component::Physics::Transform()));
			obj->addComponent(*dL);
			GameObject::getRoot()->addChild(*obj);

			return obj;
		}

		return obj->clone(); // Otherwise, clone the existing object.
	}

	GameObject* Builder::newCube() {
		return newDefaultImport("Cube", CUBE_LOCATION);
	}

	GameObject* Builder::newPlane() {
		return newDefaultImport("Plane", PLANE_LOCATION);
	}

	GameObject* Builder::newSphere() {
		return newDefaultImport("Sphere", SPHERE_LOCATION);
	}

	GameObject* Builder::newModel(std::string path) {
		// Create a Model and return the clone of it (again, do not delete the
		// model so that the Model class may later reuse this model if needed).
		GameObject* obj = (new Model(path))->getGameObjectClone();
		GameObject::getRoot()->addChild(*obj);

		return obj;
	}

	Builder::Builder() {

	}

	GameObject* Builder::newDefaultImport(std::string name, std::string path) {
		// Get the parent model and extract the child with the given name from
		// it. Add the child to the root so that it may be instantiated.
		GameObject *parent = (new Model(path))->getGameObjectClone();
		GameObject *child = parent->getChild(name);
		GameObject::getRoot()->addChild(*child);

		// Recycle the parent and return the child (keep the Model since the
		// Model class will use it to avoid re-importation of models).
		delete parent;
		return child;
	}
}