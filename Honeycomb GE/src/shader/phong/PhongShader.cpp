#include "..\..\..\include\shader\phong\PhongShader.h"

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
		"..\\Honeycomb GE\\res\\shaders\\phong\\vertexShader.glsl";
	std::string FRAGMENT_SHADER_LOC =
		"..\\Honeycomb GE\\res\\shaders\\phong\\fragShader.glsl";

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
		addUniform("camOrientation");
		addUniform("camTranslation");
		addUniform("objTransform");

		addUniform("cameraPos");
	}

	void PhongShader::addUniform_AmbientLight(AmbientLight aL) {
		addUniform_BaseLight(aL);
	}

	void PhongShader::addUniform_BaseLight(BaseLight aL) {
		addUniform(aL.getName() + ".base.color");
		addUniform(aL.getName() + ".base.intensity");
	}

	void PhongShader::addUniform_DirectionalLight(DirectionalLight dL) {
		// TODO: Allow for more lights (duh)
		addUniform(dL.getName() + ".base.color");
		addUniform(dL.getName() + ".base.intensity");
		addUniform(dL.getName() + ".direction");
	}

	void PhongShader::addUniform_Material(Material mat) {
		addUniform(mat.getName() + ".ambientColor");
		addUniform(mat.getName() + ".diffuseColor");
		addUniform(mat.getName() + ".specularColor");
		addUniform(mat.getName() + ".shininess");
	}

	void PhongShader::addUniform_PointLight(PointLight pL) {
		addUniform(pL.getName() + ".base.color");
		addUniform(pL.getName() + ".base.intensity");
		addUniform(pL.getName() + ".constant");
		addUniform(pL.getName() + ".linear");
		addUniform(pL.getName() + ".quadratic");
		addUniform(pL.getName() + ".position");
		addUniform(pL.getName() + ".range");
	}

	void PhongShader::addUniform_SpotLight(SpotLight sL) {
		addUniform(sL.getName() + ".base.color");
		addUniform(sL.getName() + ".base.intensity");
		addUniform(sL.getName() + ".constant");
		addUniform(sL.getName() + ".linear");
		addUniform(sL.getName() + ".quadratic");
		addUniform(sL.getName() + ".position");
		addUniform(sL.getName() + ".direction");
		addUniform(sL.getName() + ".range");
		addUniform(sL.getName() + ".cosAngle");
	}

	void PhongShader::setUniform_AmbientLight(std::string name,
			AmbientLight aL) {
		// Upcast the ambient light to a base light so it can be set using the
		// base light helper method.
		setUniform_BaseLight(name + ".base", aL);
	}

	void PhongShader::setUniform_BaseLight(std::string name, BaseLight bL) {
		setUniform_vec4(name + ".color", bL.getColor());
		setUniform_f(name + ".intensity", bL.getIntensity());
	}

	void PhongShader::setUniform_DirectionalLight(std::string name,
			DirectionalLight dL) {
		setUniform_BaseLight(name + ".base", dL);
		setUniform_vec3(name + ".direction", dL.getDirection());
	}

	void PhongShader::setUniform_Material(std::string name, Material mat) {
		setUniform_vec4(name + ".ambientColor", mat.getAmbientColor());
		setUniform_vec4(name + ".diffuseColor", mat.getDiffuseColor());
		setUniform_vec4(name + ".specularColor", mat.getSpecularColor());
		setUniform_f(name + ".shininess", mat.getShininess());
	}

	void PhongShader::setUniform_PointLight(std::string name, PointLight pL) {
		setUniform_BaseLight(name + ".base", pL);
		setUniform_f(name + ".constant", pL.getAttenuationConstant());
		setUniform_f(name + ".linear", pL.getAttenuationLinear());
		setUniform_f(name + ".quadratic", pL.getAttenuationQuadratic());
		setUniform_vec3(name + ".position", pL.getPosition());
		setUniform_f(name + ".range", pL.getRange());
	}

	void PhongShader::setUniform_SpotLight(std::string name, SpotLight sL) {
		setUniform_BaseLight(name + ".base", sL);
		setUniform_f(name + ".constant", sL.getAttenuationConstant());
		setUniform_f(name + ".linear", sL.getAttenuationLinear());
		setUniform_f(name + ".quadratic", sL.getAttenuationQuadratic());
		setUniform_vec3(name + ".direction", sL.getDirection());
		setUniform_vec3(name + ".position", sL.getPosition());
		setUniform_f(name + ".range", sL.getRange());
		setUniform_f(name + ".cosAngle", cos(sL.getAngle()));
	}
}