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
		/// be set to their default values of { 1.0F, 1.0F, 1.0F } and 1.0F.
		/// The material will be given the name of "material".
		Material();

		/// Initializes a new material with the specified albedo texture and 
		/// color. The ambient, diffuse, specular and shininess will all be set
		/// to their default values of { 1.0F, 1.0F, 1.0F } and 1.0F. The 
		/// material will be given the name of "material".
		/// Texture2D *tex : The albedo texture of the material.
		/// Vector4f col : The albedo color to be applied over the material.
		Material(Texture2D *tex, Honeycomb::Math::Vector4f col);

		/// Initializes a new material with the specified alebdo texture,
		/// albedo color, ambient, diffuse, specular and shininess components;
		/// and gives the material the specified name.
		/// string n : The name of the material.
		/// Texture2D *tex : The albedo texture of the material.
		/// Vector4f col : The albedo color of the material.
		/// Vector3f amb : The ambient color of the material.
		/// Vector3f diff : The diffuse color of the material.
		Material(std::string n, Texture2D *tex, Honeycomb::Math::Vector4f col,
			Honeycomb::Math::Vector3f amb, Honeycomb::Math::Vector3f diff);

		/// Destroys this Material instance.
		~Material();

		/// Returns the albedo texture, if it exists, otherwise a nullptr is
		/// returned.
		/// return : The albedo texture pointer.
		Texture2D* getAlbedoTexture();

		/// Returns the reference to the ambient color of this material.
		/// return : The ambient color.
		Honeycomb::Math::Vector3f& getAmbientColor();

		/// Returns the reference to the diffuse color of this material.
		/// return : The diffuse color.
		Honeycomb::Math::Vector3f& getDiffuseColor();

		/// Returns the name of the material.
		/// return : The material name.
		std::string getName();

		/// Uses this Material to draw something. The texture of this material
		/// will be binded, and the color will be sent to the active Shader
		/// program.
		void use();
	private:
		std::string name; // The name of this material.

		Texture2D *albedoTexture; // The albedo texture, if any

		Honeycomb::Math::Vector3f ambientColor; // Color under Ambient Light
		Honeycomb::Math::Vector3f diffuseColor; // Color under Diffuse Light
	};
}

#endif