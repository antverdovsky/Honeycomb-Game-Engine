#include "..\..\..\include\shader\phong\PhongShader.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\..\include\math\Vector3f.h"

// TEMP
using Honeycomb::Light::AmbientLight;
using Honeycomb::Light::BaseLight;
using Honeycomb::Light::DirectionalLight;

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

	PhongShader::PhongShader() : ShaderProgram(), 
			ambLight(BaseLight(0.25, Vector3f(1, 1, 1))) {
		// Add Shaders & Compile
		addShader(VERTEX_SHADER_LOC, GL_VERTEX_SHADER);
		addShader(FRAGMENT_SHADER_LOC, GL_FRAGMENT_SHADER);
		finalizeShaderProgram();

		// Add Vertex Shader Uniforms
		addUniform("camProjection");
		addUniform("camOrientation");
		addUniform("camTranslation");
		addUniform("objTransform");

		// Add Ambient Light
		addUniform("ambientLight.base.color");
		addUniform("ambientLight.base.intensity");

		// Add Directional Light
		// TODO: Allow for more lights (duh)
		addUniform("directionalLight.base.color");
		addUniform("directionalLight.base.intensity");
		addUniform("directionalLight.direction");

		// TODO [MOVE SOMEWHERE ELSE]
		setUniform_AmbientLight("ambientLight", this->ambLight);
		setUniform_DirectionalLight("directionalLight", this->dirLight);
	}

	void PhongShader::setUniform_AmbientLight(std::string name, 
			AmbientLight aL) {
		setUniform_BaseLight(name + ".base", aL.getBase());
	}

	void PhongShader::setUniform_BaseLight(std::string name, BaseLight bL) {
		setUniform_vec3(name + ".color", bL.getColor());
		setUniform_f(name + ".intensity", bL.getIntensity());
	}

	void PhongShader::setUniform_DirectionalLight(std::string name,
			DirectionalLight dL) {
		setUniform_BaseLight(name + ".base", dL.getBase());
		setUniform_vec3(name + ".direction", dL.getDirection());
	}
}