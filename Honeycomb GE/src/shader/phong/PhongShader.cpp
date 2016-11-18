#include "..\..\..\include\shader\phong\PhongShader.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\..\include\math\Vector3f.h"

using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::DirectionalLight;
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
}