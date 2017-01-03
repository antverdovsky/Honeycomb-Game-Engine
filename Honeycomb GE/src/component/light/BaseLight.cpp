#include "..\..\..\include\component\light\BaseLight.h"

#include <algorithm>

#include "..\..\..\include\debug\Logger.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"

using Honeycomb::Debug::Logger;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::GenericStruct;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb::Component::Light {
	BaseLight::BaseLight(const Honeycomb::Shader::ShaderSource &src, const
			std::string &name) : 
			GenericStruct(src, name), GameComponent(name) {

	}

	BaseLight* BaseLight::clone() const {
		return new BaseLight(*GenericStruct::SHADER_SOURCE, 
			GenericStruct::structName);
	}

	void BaseLight::start() {
		this->getAttached()->getScene()->activeLights.push_back(this);
	}

	void BaseLight::stop() {
		std::vector<BaseLight*> &lights =
			this->getAttached()->getScene()->activeLights;

		lights.erase(std::remove(lights.begin(), lights.end(), this),
			lights.end());
	}
}