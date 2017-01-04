#include "..\..\..\include\component\light\AmbientLight.h"

#include "..\..\..\include\shader\phong\PhongAmbientShader.h"

using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;
using Honeycomb::Shader::Phong::PhongAmbientShader;

namespace Honeycomb::Component::Light {
	const std::string AmbientLight::COLOR_VEC4 = "base.color";
	const std::string AmbientLight::INTENSITY_F = "base.intensity";

	const std::string AmbientLight::structFile = "..\\Honeycomb GE\\res\\"
			"shaders\\standard\\source\\light\\stdAmbientLight.glsl";
	const std::string AmbientLight::structName = "AmbientLight";

	AmbientLight::AmbientLight() : 
			AmbientLight(1.0F, Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {
		
	}

	AmbientLight::AmbientLight(const float &inten, const Vector4f &col) :
			BaseLight(*ShaderSource::getShaderSource(structFile), structName) {
		this->glFloats.setValue(AmbientLight::INTENSITY_F, inten);
		this->glVector4fs.setValue(AmbientLight::COLOR_VEC4, col);

		this->preferredShader = PhongAmbientShader::getPhongAmbientShader();
		this->uniformName = "ambientLight";
	}

	AmbientLight* AmbientLight::clone() const {
		return new AmbientLight(
			this->glFloats.getValue(AmbientLight::INTENSITY_F),
			this->glVector4fs.getValue(AmbientLight::COLOR_VEC4));
	}

	void AmbientLight::start() {
		BaseLight::start();
	}
}