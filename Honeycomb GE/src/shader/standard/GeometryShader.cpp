#include "..\..\..\include\shader\standard\GeometryShader.h"

#include <GL\glew.h>

using Honeycomb::Math::Matrix4f;

namespace Honeycomb::Shader::Standard {
	GeometryShader* GeometryShader::geometryShader = nullptr;
	const std::string GeometryShader::FRAG_FILE_LOC = 
		"..\\Honeycomb GE\\res\\shaders\\standard\\geometryFragment.glsl";
	const std::string GeometryShader::VERT_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\standard\\geometryVertex.glsl";
	
	GeometryShader* GeometryShader::getGeometryShader() {
		if (geometryShader == nullptr)
			geometryShader = new GeometryShader();

		return geometryShader;
	}

	GeometryShader::GeometryShader() : ShaderProgram() {
		// Add Shaders & Compile
		addShader(VERT_FILE_LOC, GL_VERTEX_SHADER);
		addShader(FRAG_FILE_LOC, GL_FRAGMENT_SHADER);
		finalizeShaderProgram();

		// Add Shader Uniforms
		addUniform("uvs_Projection");
		addUniform("uvs_Transformation");

		// TODO TEMP
		addUniform("ufs_Material.ambientColor");
		addUniform("ufs_Material.diffuseColor");
		addUniform("ufs_Material.specularColor");
		addUniform("ufs_Material.shininess");
	}

	GeometryShader::~GeometryShader() {

	}

	void GeometryShader::setProjection(const Matrix4f &proj) {
		this->setUniform_mat4("uvs_Projection", proj);
	}

	void GeometryShader::setTransformation(const Matrix4f &trans) {
		this->setUniform_mat4("uvs_Transformation", trans);
	}
}