#include "..\..\include\graphics\Material.h"

#include "..\..\include\shader\ShaderProgram.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Graphics {
	Material::Material() : Material(nullptr, Vector3f(1.0F, 1.0F, 1.0F)) {

	}

	Material::Material(Texture2D *tex, Vector3f col) 
			: albedoTexture(tex), albedoColor(col) {

	}

	Material::~Material() {

	}

	Vector3f& Material::getAlbedoColor() {
		return this->albedoColor;
	}

	Texture2D* Material::getAlbedoTexture() {
		return this->albedoTexture;
	}

	void Material::use() {
		if (this->albedoTexture != nullptr)
			this->albedoTexture->bind();

		ShaderProgram::getActiveShader()->setUniform_vec3("albedoColor",
			this->albedoColor);
	}
}