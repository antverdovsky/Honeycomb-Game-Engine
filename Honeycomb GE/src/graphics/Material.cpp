#include "..\..\include\graphics\Material.h"

#include "..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Graphics {
	Material::Material() 
		: Material(nullptr, Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	Material::Material(Texture2D *tex, Vector4f col) 
		: Material("material", tex, col, Vector3f(1.0F, 1.0F, 1.0F), 
		  Vector3f(1.0F, 1.0F, 1.0F)) {
		
	}

	Material::Material(std::string n, Texture2D *tex, Vector4f col, 
			Vector3f amb, Vector3f diff) 
		: albedoTexture(tex), ambientColor(amb), diffuseColor(diff) {
		this->name = n;

		PhongShader::getPhongShader()->addUniform_Material(*this);
	}

	Material::~Material() {

	}

	Texture2D* Material::getAlbedoTexture() {
		return this->albedoTexture;
	}

	Vector3f& Material::getAmbientColor() {
		return this->ambientColor;
	}

	Vector3f& Material::getDiffuseColor() {
		return this->diffuseColor;
	}

	std::string Material::getName() {
		return this->name;
	}

	void Material::use() {
		if (this->albedoTexture != nullptr)
			this->albedoTexture->bind();

		PhongShader::getPhongShader()->setUniform_Material(this->name, *this);
	}
}