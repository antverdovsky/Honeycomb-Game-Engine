#include "..\..\..\include\component\light\AmbientLight.h"

#include "..\..\..\include\shader\phong\PhongAmbientShader.h"

using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::Phong::PhongAmbientShader;

namespace Honeycomb::Component::Light {
	AmbientLight::AmbientLight() : 
			AmbientLight(BaseLight("AmbientLight")) {

	}

	AmbientLight::AmbientLight(BaseLight bL) :
			AmbientLight(bL.getName(), bL.getIntensity(), bL.getColor()) {

	}

	AmbientLight::AmbientLight(const std::string &nam, const float
			&inten, const Vector4f &col) : BaseLight(nam, inten, col) {
		this->shader = PhongAmbientShader::getPhongAmbientShader();
		this->shaderUniform = "ambientLight";
	}

	AmbientLight::~AmbientLight() {

	}

	AmbientLight* AmbientLight::clone() const {
		return new AmbientLight(*this);
	}

	void AmbientLight::toShader() {
		BaseLight::toShader();
	}
}