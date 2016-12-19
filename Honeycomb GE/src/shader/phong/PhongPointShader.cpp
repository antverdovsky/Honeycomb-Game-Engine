#include "..\..\..\include\shader\phong\PhongPointShader.h"

#include <GL\glew.h>

using Honeycomb::Component::Light::AmbientLight;

namespace Honeycomb::Shader::Phong {
	PhongPointShader* PhongPointShader::phongPointShader =
		nullptr;

	const std::string PhongPointShader::VERT_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\phong\\phongPointVertex.glsl";
	const std::string PhongPointShader::FRAG_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\phong\\phongPointFragment.glsl";

	PhongPointShader* PhongPointShader::
		getPhongPointShader() {
		if (phongPointShader == nullptr)
			phongPointShader = new PhongPointShader();

		return phongPointShader;
	}

	PhongPointShader::PhongPointShader() : ShaderProgram() {
		// Add Shaders & Compile
		addShader(VERT_FILE_LOC, GL_VERTEX_SHADER);
		addShader(FRAG_FILE_LOC, GL_FRAGMENT_SHADER);
		finalizeShaderProgram();

		// Add Shader Uniforms TODO:::
		addUniform("camProjection");
		addUniform("objTransform");
		addUniform("cameraPos");
		addUniform("pointLight.base.color");
		addUniform("pointLight.base.intensity");
		addUniform("pointLight.attenuation.constant");
		addUniform("pointLight.attenuation.linear");
		addUniform("pointLight.attenuation.quadratic");
		addUniform("pointLight.position");
		addUniform("pointLight.range");
		addUniform("material.ambientColor");
		addUniform("material.diffuseColor");
		addUniform("material.specularColor");
		addUniform("material.shininess");

		this->name = "PhongPointShader";
	}

	PhongPointShader::~PhongPointShader() {

	}
}