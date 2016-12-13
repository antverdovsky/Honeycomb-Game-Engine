#include "..\..\include\graphics\Material.h"

#include "..\..\include\shader\ShaderProgram.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Graphics {
	Material::Material()
		: Material(Texture2D::getNonTexture()) {

	}

	Material::Material(const Texture2D &tex)
		: Material("material", tex, Vector4f(1.0F, 1.0F, 1.0F, 1.0F),
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F),
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F), 1.0F) {

	}

	Material::Material(const std::string &nam, const Texture2D &tex, 
			const Vector4f &amb, const Vector4f &diff, const Vector4f &spec,
			const float &shine) : albedoTexture(&tex), ambientColor(amb), 
			diffuseColor(diff), specularColor(spec) {
		this->name = nam;
		this->shininess = shine;

		/// TODO:::
		///PhongShader::getPhongShader()->addUniform_Material(*this);
	}

	Material::~Material() {
		int j = 3;
	}

	const Texture2D& Material::getAlbedoTexture() const {
		return *this->albedoTexture;
	}

	Vector4f& Material::getAmbientColor() {
		return this->ambientColor;
	}

	const Vector4f& Material::getAmbientColor() const {
		return this->ambientColor;
	}

	Vector4f& Material::getDiffuseColor() {
		return this->diffuseColor;
	}

	const Vector4f& Material::getDiffuseColor() const {
		return this->diffuseColor;
	}

	const std::string& Material::getName() const {
		return this->name;
	}

	float& Material::getShininess() {
		return this->shininess;
	}

	const float& Material::getShininess() const {
		return this->shininess;
	}

	Vector4f& Material::getSpecularColor() {
		return this->specularColor;
	}

	const Vector4f& Material::getSpecularColor() const {
		return this->specularColor;
	}

	void Material::setAlbedoTexture(Texture2D &tex) {
		this->albedoTexture = &tex;
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

	void Material::use(ShaderProgram &shader) const {
		this->albedoTexture->bind();

		// TODO:::
		//PhongShader::getPhongShader()->setUniform_Material(*this);
		shader.setUniform_vec4("material.ambientColor", this->ambientColor);
		shader.setUniform_vec4("material.diffuseColor", this->diffuseColor);
		shader.setUniform_vec4("material.specularColor", this->specularColor);
		shader.setUniform_f("material.shininess", this->shininess);
	}
}