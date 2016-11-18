#include "..\..\..\include\component\light\BaseLight.h"

#include "..\..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Component::Light {
	BaseLight::BaseLight() : BaseLight("light", 1.0F, 
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	BaseLight::BaseLight(std::string nam, float inten, Vector4f col) 
			: GameComponent(nam) {
		this->intensity = inten;
		this->color = col;

		this->baseName = nam + ".base";
	}

	BaseLight::~BaseLight() {

	}

	Vector4f BaseLight::getColor() {
		return this->color;
	}

	float BaseLight::getIntensity() {
		return this->intensity;
	}

	void BaseLight::setColor(Vector4f c) {
		this->color = c;

		this->writeToShader();
	}

	void BaseLight::setIntensity(float i) {
		this->intensity = i;

		this->writeToShader();
	}
	
	void BaseLight::start() {
		PhongShader::getPhongShader()->addUniform_BaseLight(*this);

		this->writeToShader();
	}

	void BaseLight::writeToShader() {
		PhongShader::getPhongShader()->setUniform_BaseLight(this->baseName,
			*this);
	}
}