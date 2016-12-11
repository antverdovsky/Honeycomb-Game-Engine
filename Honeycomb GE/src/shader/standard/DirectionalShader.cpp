#include "..\..\..\include\shader\standard\DirectionalShader.h"

#include <GL\glew.h>

using Honeycomb::Math::Matrix4f;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::DirectionalLight;

namespace Honeycomb::Shader::Standard {
	DirectionalShader* DirectionalShader::directionalShader = nullptr;
	const std::string DirectionalShader::FRAG_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\standard\\directionalFragment.glsl";
	const std::string DirectionalShader::VERT_FILE_LOC =
		"..\\Honeycomb GE\\res\\shaders\\standard\\directionalVertex.glsl";

	DirectionalShader* DirectionalShader::getDirectionalShader() {
		if (directionalShader == nullptr)
			directionalShader = new DirectionalShader();

		return directionalShader;
	}

	DirectionalShader::DirectionalShader() : ShaderProgram() {
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
		addUniform("ufs_CameraPosition");
		addUniform("ufs_DirectionalLight.base.color");
		addUniform("ufs_DirectionalLight.base.intensity");
		addUniform("ufs_DirectionalLight.direction");
	}

	DirectionalShader::~DirectionalShader() {

	}

	void DirectionalShader::setProjection(const Matrix4f &proj) {
		this->setUniform_mat4("uvs_Projection", proj);
	}

	void DirectionalShader::setTransformation(const Matrix4f &trans) {
		this->setUniform_mat4("uvs_Transformation", trans);
	}

	void DirectionalShader::setUniform_BaseLight(const BaseLight &bL) {
		// TODO: Not all base light uniforms are inherited, therefore it should
		// NOT be .base".uniform"
		setUniform_vec4("ufs_DirectionalLight.base.color", bL.getColor());
		setUniform_f("ufs_DirectionalLight.base.intensity", bL.getIntensity());
	}

	void DirectionalShader::setUniform_DirectionalLight(const 
			DirectionalLight &dL) {
		setUniform_BaseLight(dL);
		setUniform_vec3("ufs_DirectionalLight.direction", dL.getDirection());
	}
}