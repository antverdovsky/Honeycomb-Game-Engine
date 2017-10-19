#include "../../include/shader/GenericStruct.h"

using Honeycomb::Graphics::Texture2D;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;

namespace Honeycomb { namespace Shader {
	VariableMap<float>& GenericStruct::getFloats() {
		return this->glFloats;
	}

	const VariableMap<float>& GenericStruct::getFloats() const {
		return this->glFloats;
	}

	VariableMap<int>& GenericStruct::getInts() {
		return this->glInts;
	}

	const VariableMap<int>& GenericStruct::getInts() const {
		return this->glInts;
	}

	VariableMap<Matrix4f>& GenericStruct::getMatrix4fs() {
		return this->glMatrix4fs;
	}

	const VariableMap<Matrix4f>& GenericStruct::getMatrix4fs() const {
		return this->glMatrix4fs;
	}

	const std::string& GenericStruct::getStructName() const {
		return this->structName;
	}

	VariableMap<std::shared_ptr<const Texture2D>>& 
			GenericStruct::getSampler2Ds() {
		return this->glSampler2Ds;
	}

	const VariableMap<std::shared_ptr<const Texture2D>>& 
			GenericStruct::getSampler2Ds() const {
		return this->glSampler2Ds;
	}

	const ShaderSource& GenericStruct::getShaderSource() const {
		return this->shaderSource;
	}

	VariableMap<Vector2f>& GenericStruct::getVector2fs() {
		return this->glVector2fs;
	}

	const VariableMap<Vector2f>& GenericStruct::getVector2fs() const {
		return this->glVector2fs;
	}

	VariableMap<Vector3f>& GenericStruct::getVector3fs() {
		return this->glVector3fs;
	}

	const VariableMap<Vector3f>& GenericStruct::getVector3fs() const {
		return this->glVector3fs;
	}

	VariableMap<Vector4f>& GenericStruct::getVector4fs() {
		return this->glVector4fs;
	}

	const VariableMap<Vector4f>& GenericStruct::getVector4fs() const {
		return this->glVector4fs;
	}

	void GenericStruct::toShader(ShaderProgram &shader, const std::string &uni)
			const {
		// Create a new string with the uniform name and a dot appended, so
		// that this is not done for each variable in the struct.
		std::string uniDot = uni + ".";

		for (const auto &var : this->glFloats.map)
			shader.setUniform_f(uniDot + var.first, var.second);
		for (const auto &var : this->glInts.map)
			shader.setUniform_i(uniDot + var.first, var.second);
		for (const auto &var : this->glMatrix4fs.map)
			shader.setUniform_mat4(uniDot + var.first, var.second);
		for (const auto &var : this->glVector2fs.map)
			shader.setUniform_vec2(uniDot + var.first, var.second);
		for (const auto &var : this->glVector3fs.map)
			shader.setUniform_vec3(uniDot + var.first, var.second);
		for (const auto &var : this->glVector4fs.map)
			shader.setUniform_vec4(uniDot + var.first, var.second);
		
		int texIndex = 0; // Texture Index (displacement from GL_TEXTURE0)
		for (const auto &var : this->glSampler2Ds.map) {
			// Set the texture index which the sampler2D will reference and
			// bind the texture at that location.
			shader.setUniform_i(uniDot + var.first, texIndex);
			var.second->bind(texIndex);

			texIndex++;
		}
	}

	GenericStruct::GenericStruct(const ShaderSource &sS, const std::string 
			&structName) : shaderSource(sS) {
		for (const SourceVariable &var : sS.detStructs.at(structName)) {
			if (var.type == "float") {
				this->glFloats.map.insert({ var.name, 0.0F });
			} else if (var.type == "int") {
				this->glInts.map.insert({ var.name, 0 });
			} else if (var.type == "mat4") {
				this->glMatrix4fs.map.insert({ var.name, Matrix4f() });
			} else if (var.type == "vec2") {
				this->glVector2fs.map.insert({ var.name, Vector2f() });
			} else if (var.type == "vec3") {
				this->glVector3fs.map.insert({ var.name, Vector3f() });
			} else if (var.type == "vec4") {
				this->glVector4fs.map.insert({ var.name, Vector4f() });
			} else if (var.type == "sampler2D") {
				const auto &white = Texture2D::getTextureWhite();
				this->glSampler2Ds.map.insert({ var.name, white });
			}
		}
	}
} }
