#include "..\..\..\include\shader\phong\PhongDirectionalShader.h"

#include <GL\glew.h>

using Honeycomb::Component::Light::AmbientLight;

namespace Honeycomb::Shader::Phong {
	PhongDirectionalShader* PhongDirectionalShader::phongDirectionalShader = 
			nullptr;

	const std::string PhongDirectionalShader::VERT_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\standard\\source\\vertex\\"
		"stdVertex.glc";
	const std::string PhongDirectionalShader::FRAG_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\standard\\source\\light\\"
		"stdDirectionalLight.glc";

	PhongDirectionalShader* PhongDirectionalShader::
			getPhongDirectionalShader() {
		if (phongDirectionalShader == nullptr)
			phongDirectionalShader = new PhongDirectionalShader();

		return phongDirectionalShader;
	}

	PhongDirectionalShader::PhongDirectionalShader() : ShaderProgram() {
		// Add Shaders & Compile
		addShader(VERT_FILE_LOC, GL_VERTEX_SHADER);
		addShader(FRAG_FILE_LOC, GL_FRAGMENT_SHADER);
		finalizeShaderProgram();

		//// Add Shader Uniforms TODO:::
		////addUniform("camProjection");
		////addUniform("objTransform");
		////addUniform("cameraPos");
		//addUniform("directionalLight.base.color");
		//addUniform("directionalLight.base.intensity");
		//addUniform("directionalLight.direction");
		//addUniform("material.ambientColor");
		//addUniform("material.diffuseColor");
		//addUniform("material.specularColor");
		//addUniform("material.shininess");

		this->name = "PhongDirectionalShader";
	}

	PhongDirectionalShader::~PhongDirectionalShader() {

	}
}