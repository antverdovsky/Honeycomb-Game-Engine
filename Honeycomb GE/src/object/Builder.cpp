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
		for (int i = 0; i < this->importedModels.size(); i++)
			delete this->importedModels.at(i);
		for (int i = 0; i < this->builtObjects.size(); i++)
			delete this->builtObjects.at(i);
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
		GameObject *obj = this->findObject("Ambient Light");

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
			this->builtObjects.push_back(obj);
		}

		return obj->clone(); // Otherwise, clone the existing object.
	}

	GameObject* Builder::newCamera() {
		// Try to find the object, if it has already been built
		GameObject *obj = this->findObject("Camera");

		// If we cannot find the object, then it has not been built yet, so
		// build it and add it to the the built objects list. Then, return the
		// newly built object.
		if (obj == nullptr) {
			obj = new GameObject("Camera", nullptr);
			CameraController *cam = new CameraController();

			obj->addComponent(*(new Honeycomb::Component::Physics::Transform()));
			obj->addComponent(*cam);
			GameObject::getRoot()->addChild(*obj);
			this->builtObjects.push_back(obj);
		}

		return obj->clone(); // Otherwise, clone the existing object.
	}

	GameObject* Builder::newDirectionalLight() {
		// Try to find the object, if it has already been built
		GameObject *obj = this->findObject("Directional Light");

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
			this->builtObjects.push_back(obj);
		}

		return obj->clone(); // Otherwise, clone the existing object.
	}

	GameObject* Builder::newCube() {
		return this->newImport("Cube", CUBE_LOCATION);
	}

	GameObject* Builder::newPlane() {
		return this->newImport("Plane", PLANE_LOCATION);
	}

	GameObject* Builder::newSphere() {
		return this->newImport("Sphere", SPHERE_LOCATION);
	}

	GameObject* Builder::newObjectWithPath(std::string path) {
		// Try to find the model, if it has already been imported.
		Model *model = this->findModel(path);
		
		// If we cannot find the model, then it has not been imported yet, so
		// import it and add it to the imported models list.
		if (model == nullptr) {
			model = new Model(path);
			this->importedModels.push_back(model);
		}

		// Return a cloned object of the model (regardless of whether it has
		// already been imported or not).
		return model->getGameObjectClone();
	}

	Builder::Builder() {

	}

	Model* Builder::findModel(std::string path) {
		for (int i = 0; i < this->importedModels.size(); i++) {
			Model *mod = this->importedModels.at(i); // Get current model

			// If the model has the same path as the specified path, return it.
			if (mod->getPath() == path) return mod;
		}

		return nullptr; // If no model with matching path found -> return NULL
	}

	GameObject* Builder::findObject(std::string name) {
		for (int i = 0; i < this->builtObjects.size(); i++) {
			GameObject *obj = this->builtObjects.at(i); // Get current object

			// If the obj. has the same name as the specified name, return it.
			if (obj->getName() == name) return obj;
		}

		return nullptr; // If no object with matching name found -> return NULL
	}

	GameObject* Builder::newImport(std::string name, std::string path) {
		// Try to find the object, if it has already been built
		GameObject *obj = this->findObject(name);

		// If we cannot find the object, then it has not been built yet, so
		// build it and add it to the the built objects list. Then, return the
		// newly built object.
		if (obj == nullptr) {
			obj = this->newObjectWithPath(path)->getChild(name);
			GameObject::getRoot()->addChild(*obj);
			this->builtObjects.push_back(obj);
		}

		return obj->clone(); // Otherwise, clone the existing object.
	}
}