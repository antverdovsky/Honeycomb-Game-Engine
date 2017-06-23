#include "../../include/object/GameObjectFactory.h"

#include <string>

#include "../../include/component/light/AmbientLight.h"
#include "../../include/component/light/BaseLight.h"
#include "../../include/component/light/DirectionalLight.h"
#include "../../include/component/light/PointLight.h"
#include "../../include/component/light/SpotLight.h"
#include "../../include/component/physics/Transform.h"
#include "../../include/component/render/CameraController.h"
#include "../../include/math/Vector4f.h"

using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Light::PointLight;
using Honeycomb::Component::Light::SpotLight;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::CameraController;
using Honeycomb::Geometry::Model;
using Honeycomb::Geometry::ModelSettings;
using Honeycomb::Math::Vector4f;

namespace Honeycomb { namespace Object {
	const std::string GameObjectFactory::CONE_LOCATION =
		"../Honeycomb GE/res/models/default/cone.fbx";
	const std::string GameObjectFactory::CUBE_LOCATION = 
		"../Honeycomb GE/res/models/default/cube.fbx";
	const std::string GameObjectFactory::ICOSPHERE_LOCATION =
		"../Honeycomb GE/res/models/default/icosphere.fbx";
	const std::string GameObjectFactory::PLANE_LOCATION =
		"../Honeycomb GE/res/models/default/plane.fbx";
	const std::string GameObjectFactory::SPHERE_LOCATION =
		"../Honeycomb GE/res/models/default/sphere.fbx";
	const std::string GameObjectFactory::SUZANNE_LOCATION =
		"../Honeycomb GE/res/models/default/suzanne.fbx";

	GameObjectFactory& GameObjectFactory::getFactory() {
		static GameObjectFactory factory;
		return factory;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newAmbientLight() {
		auto obj = std::make_unique<GameObject>("Ambient Light");
		obj->addComponent<AmbientLight>();

		return obj;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newCamera() {
		auto obj = std::make_unique<GameObject>("Camera");
		obj->addComponent<CameraController>();

		return obj;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newDirectionalLight() {
		auto obj = std::make_unique<GameObject>("Directional Light");
		obj->addComponent<DirectionalLight>();

		return obj;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newCone() {
		return newDefaultImport("Cone", CONE_LOCATION);
	}

	std::unique_ptr<GameObject> GameObjectFactory::newCube() {
		return newDefaultImport("Cube", CUBE_LOCATION);
	}

	std::unique_ptr<GameObject> GameObjectFactory::newIcosphere() {
		return newDefaultImport("Icosphere", ICOSPHERE_LOCATION);
	}

	std::unique_ptr<GameObject> GameObjectFactory::newModel(
			const std::string &path, const ModelSettings &settings) {
		auto clone = Model::loadModel(path, settings).getGameObjectClone();
		auto clonePtr = std::unique_ptr<GameObject>(std::move(clone));

		return clonePtr;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newPlane() {
		return newDefaultImport("Plane", PLANE_LOCATION);
	}

	std::unique_ptr<GameObject> GameObjectFactory::newPointLight() {
		auto obj = std::make_unique<GameObject>("Point Light");
		obj->addComponent<PointLight>();

		return obj;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newSphere() {
		return newDefaultImport("Sphere", SPHERE_LOCATION);
	}

	std::unique_ptr<GameObject> GameObjectFactory::newSpotLight() {
		auto obj = std::make_unique<GameObject>("Spot Light");
		obj->addComponent<SpotLight>();

		return obj;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newSuzanne() {
		return newDefaultImport("Suzanne", SUZANNE_LOCATION);
	}

	std::unique_ptr<GameObject> GameObjectFactory::newDefaultImport(
			const std::string &name, const std::string &path) {
		// Get the parent model and extract the child with the given name from
		// it.
		auto parent = Model::loadModel(path).getGameObjectClone();
		//GameObject &child = parent->getChild(name);
		//child.deparent();
		std::unique_ptr<GameObject> child = 
				parent->removeChild(&parent->getChild(name));

		// Recycle the parent and return the child (keep the Model since the
		// Model class will use it to avoid re-importation of models).
		return std::move(child);
	}
} }
