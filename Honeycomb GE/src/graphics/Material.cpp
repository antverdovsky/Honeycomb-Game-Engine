#include "..\..\include\graphics\Material.h"

#include "..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Graphics {
	Material::Material()
		: Material(*(new Texture2D())) {

	}

	Material::Material(Texture2D &tex)
		: Material("material", tex, Vector4f(1.0F, 1.0F, 1.0F, 1.0F),
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F),
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F), 1.0F) {

	}

	Material::Material(std::string n, Texture2D &tex, Vector4f amb,
			Vector4f diff, Vector4f spec, float shine)
			: albedoTexture(tex), ambientColor(amb), diffuseColor(diff),
			  specularColor(spec) {
		this->name = n;
		this->shininess = shine;

		PhongShader::getPhongShader()->addUniform_Material(*this);
	}

	Material::~Material() {
		int j = 3;
	}

	const Texture2D& Material::getAlbedoTexture() const {
		return this->albedoTexture;
	}

	const Vector4f& Material::getAmbientColor() const {
		return this->ambientColor;
	}

	const Vector4f& Material::getDiffuseColor() const {
		return this->diffuseColor;
	}

	const std::string& Material::getName() const {
		return this->name;
	}

	const float& Material::getShininess() const {
		return this->shininess;
	}

	const Vector4f& Material::getSpecularColor() const {
		return this->specularColor;
	}

	void Material::setAlbedoTexture(Texture2D &tex) {
		this->albedoTexture = tex;
	}

	void Material::setAmbientColor(const Vector4f &col) {
		this->ambientColor = col;
	}

	void Material::setDiffuseColor(const Vector4f &col) {
		this->diffuseColor = col;
	}

	void Material::setShininess(const float &shine) {
		this->shininess = shine;
	}

	void Material::setSpecularColor(const Vector4f &col) {
		this->specularColor = col;
	}

	void Material::use() const {
		this->albedoTexture.bind();

		PhongShader::getPhongShader()->setUniform_Material(*this);
	}
}