#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture2D.h"
#include "../math/Vector3f.h"
#include "../math/Vector4f.h"
#include "../shader/GenericStruct.h"
#include "../shader/ShaderSource.h"

namespace Honeycomb { namespace Graphics {
	class Material : public Honeycomb::Shader::GenericStruct {
	public:
		/// Initiales a new Default Standard Material.
		Material();

		/// Initializes a new Material instance from the specified struct.
		/// const ShaderSource &sS : The shader source where the struct for
		///							 this Material is defined.
		///	const string &name : The name of the struct for this Material in
		///						 the given shader source.
		Material(const Honeycomb::Shader::ShaderSource &sS, 
			const std::string &name);

		/// Returns the name of the material.
		/// return : The material name.
		const std::string& getName() const;
	private:
		// Variables outlining the file directory of the Shader file and name
		// of the struct where the Default Standard Material is defined.
		const static std::string DEFAULT_FILE;
		const static std::string DEFAULT_STRUCT;

		std::string name; // The name of this material.
	};
} }

#endif
