#pragma once
#ifndef HONEYCOMB_ENGINE_H
#define HONEYCOMB_ENGINE_H

/// This Header contains all of Honeycomb's built in classes and functions, so
/// that the user of the engine can simply include this engine to gain full
/// functionality of the engine, rather than having to import each individual
/// header. Additionally, this header creates a new HoneycombEngine namespace
/// which uses all of the internal namespaces. In order to use this header,
/// simply include it and use the HoneycombEngine namespace.

#include "base\BaseGame.h"
#include "base\BaseMain.h"
#include "base\GameInput.h"
#include "base\GameTime.h"
#include "base\GameWindow.h"

#include "component\GameComponent.h"
#include "component\light\AmbientLight.h"
#include "component\light\BaseLight.h"
#include "component\light\DirectionalLight.h"
#include "component\light\PointLight.h"
#include "component\physics\Transform.h"
#include "component\render\CameraController.h"
#include "component\render\MeshRenderer.h"

#include "conjuncture\Event.h"
#include "conjuncture\EventHandler.h"

#include "file\FileIO.h"

#include "geometry\Mesh.h"
#include "geometry\Model.h"
#include "geometry\Vertex.h"

#include "graphics\Material.h"
#include "graphics\Texture2D.h"

#include "math\MathUtils.h"
#include "math\Matrix4f.h"
#include "math\Quaternion.h"
#include "math\Vector2f.h"
#include "math\Vector3f.h"
#include "math\Vector4f.h"

#include "object\Builder.h"
#include "object\GameObject.h"

#include "scene\GameScene.h"

#include "shader\ShaderProgram.h"

namespace HoneycombEngine {
	using namespace Honeycomb::Base;

	using namespace Honeycomb::Component;
	using namespace Honeycomb::Component::Light;
	using namespace Honeycomb::Component::Physics;
	using namespace Honeycomb::Component::Render;

	using namespace Honeycomb::Conjuncture;

	using namespace Honeycomb::File;

	using namespace Honeycomb::Geometry;

	using namespace Honeycomb::Graphics;

	using namespace Honeycomb::Math;
	using namespace Honeycomb::Math::Utils;

	using namespace Honeycomb::Object;

	using namespace Honeycomb::Scene;

	using namespace Honeycomb::Shader;
}

#endif