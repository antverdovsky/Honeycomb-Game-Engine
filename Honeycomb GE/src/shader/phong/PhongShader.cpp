#include "..\..\..\include\shader\phong\PhongShader.h"

/// TODO:
/// Implement Uniform Arrays into the Phong Shader to allow for multiple lights
/// using the ForwardRendererSingle...

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\..\include\math\Vector3f.h"

using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Light::PointLight;
using Honeycomb::Component::Light::SpotLight;
using Honeycomb::Graphics::Material;

using Honeycomb::Math::Vector3f;

namespace Honeycomb::Shader::Phong {
	PhongShader *PhongShader::instance = NULL; // Null instance at first

	std::string VERTEX_SHADER_LOC =
		"..\\Honeycomb GE\\res\\shaders\\phong\\phongVertex.glsl";
	std::string FRAGMENT_SHADER_LOC =
		"..\\Honeycomb GE\\res\\shaders\\phong\\phongFragment.glsl";

	PhongShader::~PhongShader() {

	}

	PhongShader* PhongShader::getPhongShader() {
		if (instance == NULL)
			instance = new PhongShader();

		return instance;
	}

	PhongShader::PhongShader() : ShaderProgram() {
		// Add Shaders & Compile
		addShader(VERTEX_SHADER_LOC, GL_VERTEX_SHADER);
		addShader(FRAGMENT_SHADER_LOC, GL_FRAGMENT_SHADER);
		finalizeShaderProgram();

		// Add Vertex Shader Uniforms
		addUniform("camProjection");
		addUniform("objTransform");

		addUniform("cameraPos");

		this->name = "PhongShader";
	}

	void PhongShader::addUniform_AmbientLight(const AmbientLight &aL) {
		addUniform_BaseLight(aL);
	}

	void PhongShader::addUniform_Attenuation(const BaseLight &bL) {
		addUniform(bL.getName() + ".attenuation.constant");
		addUniform(bL.getName() + ".attenuation.linear");
		addUniform(bL.getName() + ".attenuation.quadratic");
	}

	void PhongShader::addUniform_BaseLight(const BaseLight &aL) {
		addUniform(aL.getName() + ".base.color");
		addUniform(aL.getName() + ".base.intensity");
	}

	void PhongShader::addUniform_DirectionalLight(const DirectionalLight &dL) {
		// TODO: Allow for more lights (duh)
		addUniform(dL.getName() + ".base.color");
		addUniform(dL.getName() + ".base.intensity");
		addUniform(dL.getName() + ".direction");
	}

	void PhongShader::addUniform_Material(const Material &mat) {
		addUniform(mat.getName() + ".ambientColor");
		addUniform(mat.getName() + ".diffuseColor");
		addUniform(mat.getName() + ".specularColor");
		addUniform(mat.getName() + ".shininess");
	}

	void PhongShader::addUniform_PointLight(const PointLight &pL) {
		addUniform(pL.getName() + ".base.color");
		addUniform(pL.getName() + ".base.intensity");
		addUniform_Attenuation(pL);
		addUniform(pL.getName() + ".position");
		addUniform(pL.getName() + ".range");
	}

	void PhongShader::addUniform_SpotLight(const SpotLight &sL) {
		addUniform(sL.getName() + ".base.color");
		addUniform(sL.getName() + ".base.intensity");
		addUniform_Attenuation(sL);
		addUniform(sL.getName() + ".position");
		addUniform(sL.getName() + ".direction");
		addUniform(sL.getName() + ".range");
		addUniform(sL.getName() + ".cosAngle");
	}

	void PhongShader::setUniform_AmbientLight(const AmbientLight &aL) {
		// Upcast the ambient light to a base light so it can be set using the
		// base light helper method.
		setUniform_BaseLight(aL);
	}

	void PhongShader::setUniform_Attenuation(
			const Honeycomb::Component::Light::BaseLight &bL,
			const Honeycomb::Component::Light::BaseLight::Attenuation &atten) {
		setUniform_f(bL.getName() + ".attenuation.constant", 
			atten.getAttenuationConstant());
		setUniform_f(bL.getName() + ".attenuation.linear", 
			atten.getAttenuationLinear());
		setUniform_f(bL.getName() + ".attenuation.quadratic", 
			atten.getAttenuationQuadratic());
	}

	void PhongShader::setUniform_BaseLight(const BaseLight &bL) {
		// TODO: Not all base light uniforms are inherited, therefore it should
		// NOT be .base".uniform"
		setUniform_vec4(bL.getName() + ".base.color", bL.getColor());
		setUniform_f(bL.getName() + ".base.intensity", bL.getIntensity());
	}

	void PhongShader::setUniform_DirectionalLight(const DirectionalLight &dL) {
		setUniform_BaseLight(dL);
		setUniform_vec3(dL.getName() + ".direction", dL.getDirection());
	}

	void PhongShader::setUniform_Material(const Material &mat) {
		std::string name = mat.getName();

		/*
		setUniform_vec4(name + ".ambientColor", mat.getAmbientColor());
		setUniform_vec4(name + ".diffuseColor", mat.getDiffuseColor());
		setUniform_vec4(name + ".specularColor", mat.getSpecularColor());
		setUniform_f(name + ".shininess", mat.getShininess());
		*/
	}

	void PhongShader::setUniform_PointLight(const PointLight &pL) {
		std::string name = pL.getName();

		setUniform_BaseLight(pL);
		setUniform_Attenuation(pL, pL.getAttenuation());
		setUniform_vec3(name + ".position", pL.getPosition());
		setUniform_f(name + ".range", pL.getRange());
	}

	void PhongShader::setUniform_SpotLight(const SpotLight &sL) {
		std::string name = sL.getName();

		setUniform_BaseLight(sL);
		setUniform_Attenuation(sL, sL.getAttenuation());
		setUniform_vec3(name + ".direction", sL.getDirection());
		setUniform_vec3(name + ".position", sL.getPosition());
		setUniform_f(name + ".range", sL.getRange());
		setUniform_f(name + ".cosAngle", cos(sL.getAngle()));
	}
}