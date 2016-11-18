#include "..\..\include\graphics\Material.h"

#include "..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Graphics {
	Material::Material()
			: Material(nullptr) {

	}

	Material::Material(Texture2D *tex)
			: Material("material", tex, Vector4f(1.0F, 1.0F, 1.0F, 1.0F),
			  Vector4f(1.0F, 1.0F, 1.0F, 1.0F), 
			  Vector4f(1.0F, 1.0F, 1.0F, 1.0F), 1.0F) {

	}

	Material::Material(std::string n, Texture2D *tex, Vector4f amb, 
			Vector4f diff, Vector4f spec, float shine)
			: albedoTexture(tex), ambientColor(amb), diffuseColor(diff),
		      specularColor(spec) {
		this->name = n;
		this->shininess = shine;

		PhongShader::getPhongShader()->addUniform_Material(*this);
	}

	Material::~Material() {

	}

	Texture2D* Material::getAlbedoTexture() {
		return this->albedoTexture;
	}

	Vector4f& Material::getAmbientColor() {
		return this->ambientColor;
	}

	Vector4f& Material::getDiffuseColor() {
		return this->diffuseColor;
	}

	std::string Material::getName() {
		return this->name;
	}

	float& Material::getShininess() {
		return this->shininess;
	}

	Vector4f& Material::getSpecularColor() {
		return this->specularColor;
	}

	void Material::use() {
		if (this->albedoTexture != nullptr)
			this->albedoTexture->bind();

		PhongShader::getPhongShader()->setUniform_Material(this->name, *this);
	}
}