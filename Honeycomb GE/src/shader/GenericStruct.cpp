#include "..\..\include\shader\GenericStruct.h"

#include "..\..\include\debug\Logger.h"

using Honeycomb::Debug::Logger;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;

namespace Honeycomb::Shader {
	template <typename VariableType>
	VariableType& VariableMap<VariableType>::getValue(const std::string 
			&name) {
		return const_cast<VariableType&>(static_cast<const VariableMap&>
			(this)->getValue(name));
	}

	template <typename VariableType>
	const VariableType& VariableMap<VariableType>::getValue(const std::string
			&name) const {
		if (this->map.count(name) != 1) {// TODO: throw exception
			Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
				"Unable to retrieve variable of name " + name + " from "
				"Variable Map " + this);
		}

		return this->map[name];
	}

	template <typename VariableType>
	void VariableMap<VariableType>::setValue(const std::string &name, const
			VariableType &value) {
		this->getValue(name) = value;
	}

	void GenericStruct::toShader(ShaderProgram &shader) const {
		for (const auto &var : this->glFloats.map)
			shader.setUniform_f(var.first, var.second);
		for (const auto &var : this->glInts.map)
			shader.setUniform_i(var.first, var.second);
		for (const auto &var : this->glMatrix4fs.map)
			shader.setUniform_mat4(var.first, var.second);
//		for (const auto &var : this->glSampler2Ds.map)			TODO
//			shader.setUniform_?(var.first, var.second);
		for (const auto &var : this->glVector3fs.map)
			shader.setUniform_vec3(var.first, var.second);
		for (const auto &var : this->glVector4fs.map)
			shader.setUniform_vec4(var.first, var.second);
	}

	GenericStruct::GenericStruct(const ShaderSource &sS, const std::string 
			&structName) {
		for (const SourceVariable &var : sS.detUniforms) {
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

	GenericStruct::~GenericStruct() {

	}
}