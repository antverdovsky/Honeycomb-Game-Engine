#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture2D.h"
#include "..\math\Vector3f.h"
#include "..\math\Vector4f.h"

namespace Honeycomb::Graphics {
	class Material {
	public:
		/// Initializes a new material with no albedo texture, and a white 
		/// albedo color. The ambient, diffuse, specular and shininess will all
		/// be set to their default values of { 1.0F, 1.0F, 1.0F, 1.0F } and 
		/// 1.0F. The material will be given the name of "material".
		Material();

		/// Initializes a new material with the specified albedo texture and 
		/// color. The ambient, diffuse, specular and shininess will all be set
		/// to their default values of { 1.0F, 1.0F, 1.0F, 1.0f } and 1.0F. The 
		/// material will be given the name of "material".
		/// Texture2D *tex : The albedo texture of the material.
		Material(Texture2D &tex);

		/// Initializes a new material with the specified alebdo texture,
		/// albedo color, ambient, diffuse, specular and shininess components;
		/// and gives the material the specified name.
		/// string n : The name of the material.
		/// Texture2D *tex : The albedo texture of the material.
		/// Vector4f amb : The ambient color of the material.
		/// Vector4f diff : The diffuse color of the material.
		/// Vector4f spec : The specular highlight of the material.
		/// float shine : The shinniness of the material.
		Material(std::string n, Texture2D &tex, Honeycomb::Math::Vector4f amb, 
			Honeycomb::Math::Vector4f diff, Honeycomb::Math::Vector4f spec, 
			float shine);

		/// Destroys this Material instance.
		~Material();

		/// Returns the albedo texture, if it exists, otherwise a nullptr is
		/// returned.
		/// return : The albedo texture pointer.
		const Texture2D& getAlbedoTexture() const;

		/// Returns the reference to the ambient color of this material.
		/// return : The ambient color.
		const Honeycomb::Math::Vector4f& getAmbientColor() const;

		/// Returns the reference to the diffuse color of this material.
		/// return : The diffuse color.
		const Honeycomb::Math::Vector4f& getDiffuseColor() const;

		/// Returns the name of the material.
		/// return : The material name.
		const std::string& getName() const;

		/// Returns a reference to the shininess of this material.
		/// return : The shininess.
		const float& getShininess() const;

		/// Returns the reference to the specular color of this material.
		/// return : The specular color.
		const Honeycomb::Math::Vector4f& getSpecularColor() const;

		/// Sets the Albedo Texture of this Material (may also be set to null
		/// to indicate this material has no Albedo Texture). 
		/// Texture2D *tex : The Albedo Texture.
		void setAlbedoTexture(Texture2D &tex);

		/// Sets the Ambient Color of this Material.
		/// const Vector4f &col : The new Ambient Color.
		void setAmbientColor(const Honeycomb::Math::Vector4f& col);

		/// Sets the Diffuse Color of this Material.
		/// const Vector4f &col : The new Diffuse Color.
		void setDiffuseColor(const Honeycomb::Math::Vector4f& col);

		/// Sets the Shininess of this Material.
		/// const float *shine : The new shininess.
		void setShininess(const float &shine);

		/// Sets the Specular Color of this Material.
		/// const Vector4f &col : The new Specular Color.
		void setSpecularColor(const Honeycomb::Math::Vector4f& col);

		/// Uses this Material to draw something. The texture of this material
		/// will be binded, and the color will be sent to the active Shader
		/// program.
		void use() const;
	private:
		std::string name; // The name of this material.

		Texture2D &albedoTexture; // The albedo texture

		Honeycomb::Math::Vector4f ambientColor; // Color under Ambient Light
		Honeycomb::Math::Vector4f diffuseColor; // Color under Diffuse Light
		Honeycomb::Math::Vector4f specularColor; // Color of Specular Light
		float shininess; // Effect of the specular spread
	};
}

#endif