#include "..\..\include\shader\GenericStruct.h"

using Honeycomb::Graphics::Texture2D;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;

namespace Honeycomb::Shader {
	void GenericStruct::toShader(ShaderProgram &shader, const std::string &uni)
			const {
		for (const auto &var : this->glFloats.map)
			shader.setUniform_f(uni + "." + var.first, var.second);
		for (const auto &var : this->glInts.map)
			shader.setUniform_i(uni + "." + var.first, var.second);
		for (const auto &var : this->glMatrix4fs.map)
			shader.setUniform_mat4(uni + "." + var.first, var.second);
//		for (const auto &var : this->glSampler2Ds.map)			TODO
//			shader.setUniform_?(var.first, var.second);
		for (const auto &var : this->glVector3fs.map)
			shader.setUniform_vec3(uni + "." + var.first, var.second);
		for (const auto &var : this->glVector4fs.map)
			shader.setUniform_vec4(uni + "." + var.first, var.second);
	}

	GenericStruct::GenericStruct(const ShaderSource &sS, const std::string 
			&structName) {
		this->SHADER_SOURCE = &sS;
		this->structName = structName;

		for (const SourceVariable &var : sS.detStructs.at(structName)) {
			if (var.type == "float")
				this->glFloats.map.insert({ var.name, 0.0F });
			else if (var.type == "int")
				this->glInts.map.insert({ var.name, 0 });
			else if (var.type == "mat4")
				this->glMatrix4fs.map.insert({ var.name, Matrix4f() });
			else if (var.type == "vec3")
				this->glVector3fs.map.insert({ var.name, Vector3f() });
			else if (var.type == "vec4")
				this->glVector4fs.map.insert({ var.name, Vector4f() });
			else if (var.type == "sampler2D")
				this->glSampler2Ds.map.insert({ var.name, nullptr });
		}
	}
}