#include "..\..\..\include\component\light\AmbientLight.h"

#include <algorithm>

#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"

using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Component::Light {
	AmbientLight::AmbientLight() : AmbientLight(BaseLight("AmbientLight")) {

	}

	AmbientLight::AmbientLight(BaseLight bL) : BaseLight(bL) {

	}

	AmbientLight::AmbientLight(const std::string &nam, const float
		&inten, const Vector4f &col) : BaseLight(nam, inten, col) {

	}

	AmbientLight::~AmbientLight() {

	}

	AmbientLight* AmbientLight::clone() const {
		return new AmbientLight(*this);
	}

	void AmbientLight::start() {
		this->getAttached()->getScene()->ambientLights.push_back(this);
	}

	void AmbientLight::stop() {
		std::vector<AmbientLight*> &aLs = 
			this->getAttached()->getScene()->ambientLights;

		aLs.erase(std::remove(aLs.begin(), aLs.end(), this), aLs.end());
	}

	void AmbientLight::toShader(ShaderProgram &shader, const std::string 
			&uni) {
		BaseLight::toShader(shader, uni + ".base");
	}
}