#include "..\..\..\include\shader\phong\PhongShader.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\..\include\math\Vector3f.h"

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

		// Add Fragment Shader Uniforms
		addUniform("ambientLightStrength");
		addUniform("ambientLightColor");

		// TODO [MOVE SOMEWHERE ELSE]
		setUniform_f("ambientLightStrength", 0.25F);
		setUniform_vec3("ambientLightColor", Vector3f(1, 1, 1));
	}
}