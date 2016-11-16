#include "..\..\include\graphics\Material.h"

#include "..\..\include\shader\ShaderProgram.h"

using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Graphics {
	Material::Material() 
		: Material(nullptr, Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	Material::Material(Texture2D *tex, Vector4f col) 
			: albedoTexture(tex), albedoColor(col) {

	}

	Material::~Material() {

	}

	Vector4f& Material::getAlbedoColor() {
		return this->albedoColor;
	}

	Texture2D* Material::getAlbedoTexture() {
		return this->albedoTexture;
	}

	void Material::use() {
		if (this->albedoTexture != nullptr)
			this->albedoTexture->bind();

		ShaderProgram::getActiveShader()->setUniform_vec4("albedoColor",
			this->albedoColor);
	}
}