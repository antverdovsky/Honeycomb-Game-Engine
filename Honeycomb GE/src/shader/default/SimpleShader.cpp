#include "..\..\..\include\shader\default\SimpleShader.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Honeycomb::Shader::Default {
	SimpleShader *SimpleShader::instance = NULL; // Null instance at first

	std::string VERTEX_SHADER_LOC = 
		"..\\Honeycomb GE\\res\\shaders\\default\\vertexShader.vs";
	std::string FRAGMENT_SHADER_LOC =
		"..\\Honeycomb GE\\res\\shaders\\default\\fragShader.fs";

	SimpleShader::~SimpleShader() {

	}

	SimpleShader* SimpleShader::getSimpleShader() {
		if (instance == NULL)
			instance = new SimpleShader();

		return instance;
	}

	SimpleShader::SimpleShader() : ShaderProgram() {
		// Add Shaders & Compile
		addShader(VERTEX_SHADER_LOC, GL_VERTEX_SHADER);
		addShader(FRAGMENT_SHADER_LOC, GL_FRAGMENT_SHADER);
		finalizeShaderProgram();

		// Add Uniforms
		addUniform("camProjection");
		addUniform("camOrientation");
		addUniform("camTranslation");
		addUniform("objTransform");
	}
}