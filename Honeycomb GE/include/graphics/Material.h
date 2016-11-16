#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture2D.h"
#include "..\math\Vector4f.h"

namespace Honeycomb::Graphics {
	class Material {
	public:
		/// Initializes a new material with no texture, and a white color.
		Material();

		/// Initializes a new material with the specified texture and color.
		/// Texture2D tex : The texture of the material.
		/// Vector4f col : The color to be applied over the material.
		Material(Texture2D *tex, Honeycomb::Math::Vector4f col);

		/// Destroys this Material instance.
		~Material();

		/// Return the albedo color vector.
		/// return : The albedo color.
		Honeycomb::Math::Vector4f& getAlbedoColor();

		/// Returns the albedo texture, if it exists, otherwise a nullptr is
		/// returned.
		/// return : The albedo texture pointer.
		Texture2D* getAlbedoTexture();

		/// Uses this Material to draw something. The texture of this material
		/// will be binded, and the color will be sent to the active Shader
		/// program.
		void use();
	private:
		Texture2D *albedoTexture; // The albedo texture, if any
		Honeycomb::Math::Vector4f albedoColor; // The albedo color
	};
}

#endif