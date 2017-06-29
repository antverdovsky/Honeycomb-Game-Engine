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
		static Model cone{ "../Honeycomb GE/res/models/default/cone.fbx" };
		return newDefaultImport(cone, "Cone");
	}

	std::unique_ptr<GameObject> GameObjectFactory::newCube() {
		static Model cube{ "../Honeycomb GE/res/models/default/cube.fbx" };
		return newDefaultImport(cube, "Cube");
	}

	std::unique_ptr<GameObject> GameObjectFactory::newGameObject(
			const Model &model) {
		return model.getGameObjectClone();
	}

	std::unique_ptr<GameObject> GameObjectFactory::newIcosphere() {
		static Model ico{ "../Honeycomb GE/res/models/default/icosphere.fbx" };
		return newDefaultImport(ico, "Icosphere");
	}

	std::unique_ptr<GameObject> GameObjectFactory::newPlane() {
		static Model plane{ "../Honeycomb GE/res/models/default/plane.fbx" };
		return newDefaultImport(plane, "Plane");
	}

	std::unique_ptr<GameObject> GameObjectFactory::newPointLight() {
		auto obj = std::make_unique<GameObject>("Point Light");
		obj->addComponent<PointLight>();

		return obj;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newSphere() {
		static Model sphere{ "../Honeycomb GE/res/models/default/sphere.fbx" };
		return newDefaultImport(sphere, "Sphere");
	}

	std::unique_ptr<GameObject> GameObjectFactory::newSpotLight() {
		auto obj = std::make_unique<GameObject>("Spot Light");
		obj->addComponent<SpotLight>();

		return obj;
	}

	std::unique_ptr<GameObject> GameObjectFactory::newSuzanne() {
		static Model suz{ "../Honeycomb GE/res/models/default/suzanne.fbx" };
		return newDefaultImport(suz, "Suzanne");
	}

	std::unique_ptr<GameObject> GameObjectFactory::newDefaultImport(
			const Model &model, const std::string &name) {
		auto root = model.getGameObjectClone();
		auto child = root->removeChild(&(root->getChild(name)));

		return std::move(child);
	}
} }
