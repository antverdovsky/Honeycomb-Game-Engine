#include "..\..\..\include\component\light\AmbientLight.h"

using Honeycomb::Math::Vector4f;

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
}