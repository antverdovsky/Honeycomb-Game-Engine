#include "..\..\..\include\shader\phong\PhongSpotShader.h"

#include <GL\glew.h>

using Honeycomb::Component::Light::AmbientLight;

namespace Honeycomb::Shader::Phong {
	PhongSpotShader* PhongSpotShader::phongSpotShader =
		nullptr;

	const std::string PhongSpotShader::VERT_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\standard\\source\\vertex\\"
		"stdVertex.glc";
	const std::string PhongSpotShader::FRAG_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\standard\\source\\light\\"
		"stdSpotLight.glc";

	PhongSpotShader* PhongSpotShader::
		getPhongSpotShader() {
		if (phongSpotShader == nullptr)
			phongSpotShader = new PhongSpotShader();

		return phongSpotShader;
	}

	PhongSpotShader::PhongSpotShader() : ShaderProgram() {
		// Add Shaders & Compile
		addShader(VERT_FILE_LOC, GL_VERTEX_SHADER);
		addShader(FRAG_FILE_LOC, GL_FRAGMENT_SHADER);
		finalizeShaderProgram();

		// Add Shader Uniforms TODO:::
		addUniform("camProjection");
		addUniform("objTransform");
		addUniform("cameraPos");
		addUniform("spotLight.base.color");
		addUniform("spotLight.base.intensity");
		addUniform("spotLight.attenuation.constant");
		addUniform("spotLight.attenuation.linear");
		addUniform("spotLight.attenuation.quadratic");
		addUniform("spotLight.position");
		addUniform("spotLight.direction");
		addUniform("spotLight.range");
		addUniform("spotLight.cosAngle");
		addUniform("material.ambientColor");
		addUniform("material.diffuseColor");
		addUniform("material.specularColor");
		addUniform("material.shininess");

		this->name = "PhongSpotShader";
	}

	PhongSpotShader::~PhongSpotShader() {

	}
}