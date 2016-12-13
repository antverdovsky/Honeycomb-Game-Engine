#include "..\..\..\include\shader\phong\PhongAmbientShader.h"

#include <GL\glew.h>

using Honeycomb::Component::Light::AmbientLight;

namespace Honeycomb::Shader::Phong {
	PhongAmbientShader* PhongAmbientShader::phongAmbientShader = nullptr;

	const std::string PhongAmbientShader::VERT_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\phong\\phongAmbientVertex.glsl";
	const std::string PhongAmbientShader::FRAG_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\phong\\phongAmbientFragment.glsl";

	PhongAmbientShader* PhongAmbientShader::getPhongAmbientShader() {
		if (phongAmbientShader == nullptr)
			phongAmbientShader = new PhongAmbientShader();

		return phongAmbientShader;
	}

	PhongAmbientShader::PhongAmbientShader() : ShaderProgram() {
		// Add Shaders & Compile
		addShader(VERT_FILE_LOC, GL_VERTEX_SHADER);
		addShader(FRAG_FILE_LOC, GL_FRAGMENT_SHADER);
		finalizeShaderProgram();

		// Add Shader Uniforms TODO:::
		addUniform("camProjection");
		addUniform("objTransform");
		addUniform("ambientLight.base.color");
		addUniform("ambientLight.base.intensity");
		addUniform("material.ambientColor");
		addUniform("material.diffuseColor");
		addUniform("material.specularColor");
		addUniform("material.shininess");

		this->name = "PhongAmbientShader";
	}

	PhongAmbientShader::~PhongAmbientShader() {

	}
}