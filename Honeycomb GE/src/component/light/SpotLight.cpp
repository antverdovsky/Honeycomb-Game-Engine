#include "..\..\..\include\component\light\SpotLight.h"

#include <algorithm>

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\math\MathUtils.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Utils::PI;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb::Component::Light {
	const std::string SpotLight::ATTENUATION_CONSTANT_F =
		"attenuation.constant";
	const std::string SpotLight::ATTENUATION_LINEAR_F = "attenuation.linear";
	const std::string SpotLight::ATTENUATION_QUADRATIC_F =
		"attenuation.quadratic";
	const std::string SpotLight::COLOR_VEC4 = "base.color";
	const std::string SpotLight::INTENSITY_F = "base.intensity";
	const std::string SpotLight::DIRECTION_VEC3 = "direction";
	const std::string SpotLight::POSITION_VEC3 = "position";
	const std::string SpotLight::RANGE_F = "range";
	const std::string SpotLight::ANGLE_F = "angle";

	const std::string SpotLight::structFile = "..\\Honeycomb GE\\res\\"
			"shaders\\standard\\source\\light\\stdSpotLight.glsl";
	const std::string SpotLight::structName = "SpotLight";

	SpotLight::SpotLight() : SpotLight(1.0F, Vector4f(1.0F, 1.0F, 1.0F, 1.0F),
			1.0F, 0.22F, 0.20F, 10.0F, PI / 4.0F) {

	}

	SpotLight::SpotLight(const float &inten, const Honeycomb::Math::Vector4f
			&col, const float &atC, const float &atL, const float &atQ, const 
			float &ran, const float &ang) : 
			BaseLight(*ShaderSource::getShaderSource(structFile), structName) {
		this->glFloats.setValue(SpotLight::INTENSITY_F, inten);
		this->glVector4fs.setValue(SpotLight::COLOR_VEC4, col);
		this->glFloats.setValue(SpotLight::ATTENUATION_CONSTANT_F, atC);
		this->glFloats.setValue(SpotLight::ATTENUATION_LINEAR_F, atL);
		this->glFloats.setValue(SpotLight::ATTENUATION_QUADRATIC_F, atQ);
		this->glFloats.setValue(SpotLight::RANGE_F, ran);
		this->glFloats.setValue(SpotLight::ANGLE_F, ang);

		this->uniformName = "spotLight";
	}

	SpotLight* SpotLight::clone() const {
		return new SpotLight(
			this->glFloats.getValue(SpotLight::INTENSITY_F),
			this->glVector4fs.getValue(SpotLight::COLOR_VEC4),
			this->glFloats.getValue(SpotLight::ATTENUATION_CONSTANT_F),
			this->glFloats.getValue(SpotLight::ATTENUATION_LINEAR_F),
			this->glFloats.getValue(SpotLight::ATTENUATION_QUADRATIC_F),
			this->glFloats.getValue(SpotLight::RANGE_F),
			this->glFloats.getValue(SpotLight::ANGLE_F));
	}

	void SpotLight::start() {
		// Get the position and direction.
		this->position = &this->getAttached()->getComponent<Transform>()->
			getTranslation();
		this->direction = &this->getAttached()->getComponent<Transform>()->
			getLocalForward();

		BaseLight::start();
	}

	void SpotLight::update() {
		this->glVector3fs.setValue(SpotLight::POSITION_VEC3, *this->position);
		this->glVector3fs.setValue(SpotLight::DIRECTION_VEC3, 
			*this->direction);
	}
}