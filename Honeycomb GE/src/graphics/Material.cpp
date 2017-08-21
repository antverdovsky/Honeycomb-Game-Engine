#include "../../include/graphics/Material.h"

#include "../../include/shader/ShaderProgram.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::GenericStruct;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb { namespace Graphics {
	const std::string Material::DEFAULT_FILE =
		"../Honeycomb GE/res/shaders/standard/structs/stdMaterial.glsl";
	const std::string Material::DEFAULT_STRUCT = "Material";

	Material::Material() : Material(ShaderSource::getShaderSource(
			Material::DEFAULT_FILE), Material::DEFAULT_STRUCT) {

	}
	
	Material::Material(const Honeycomb::Shader::ShaderSource &sS,
			const std::string &name) : GenericStruct(sS, name) {
		this->name = name;
	}

	const std::string& Material::getName() const {
		return this->name;
	}
} }
