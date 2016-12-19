#include "..\..\..\include\component\light\AmbientLight.h"

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

	void AmbientLight::toShader(ShaderProgram &shader, const std::string 
			&uni) {
		BaseLight::toShader(shader, uni + ".base");
	}
}