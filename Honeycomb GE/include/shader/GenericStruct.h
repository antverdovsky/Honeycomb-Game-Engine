#pragma once
#ifndef GENERIC_STRUCT_H
#define GENERIC_STRUCT_H

#include <unordered_map>

#include "ShaderProgram.h"
#include "..\graphics\Texture2D.h"
#include "..\math\Matrix4f.h"
#include "..\math\Vector2f.h"
#include "..\math\Vector3f.h"
#include "..\math\Vector4f.h"

namespace Honeycomb::Shader {
	template<typename VariableType>
	class VariableMap {
		friend class GenericStruct;

	public:
		/// Gets the value of the variable with the specified name. If the
		/// variable does not exist, the map will insert it anyway, however a 
		/// log warning will be created.
		/// const string &name : The name of the variable.
		/// return : A reference to the variable's value. 
		VariableType& getValue(const std::string &name);

		/// Gets the value of the variable with the specified name. If the
		/// variable does not exist, the map will insert it anyway, however a 
		/// log warning will be created.
		/// const string &name : The name of the variable.
		/// return : A constant reference to the variable's value.
		const VariableType& getValue(const std::string &name) const;
		
		/// Sets the value of the variable with the specified name. If the
		/// variable does not exist, the map will insert it anyway, however a 
		/// log warning will be created.
		/// const string &name : The name of the variable.
		/// const VariableType &value : The value of the variable.
		void setValue(const std::string &name, const VariableType &value);
	private:
		std::unordered_map<std::string, VariableType> map;
	};

	class GenericStruct {
	public:
		/// Writes all of the properties of this Generic Struct to the
		/// specified Shader Program.
		void toShader(ShaderProgram &shader) const;
	protected:
		// Map of the name of the uniform, as found in the Shader, to the value
		// of the uniform, as it will be written to the Shader.
		VariableMap<float> glFloats;
		VariableMap<int> glInts;
		VariableMap<Honeycomb::Math::Matrix4f> glMatrix4fs;
		VariableMap<Honeycomb::Graphics::Texture2D*> glSampler2Ds;
		VariableMap<Honeycomb::Math::Vector3f> glVector3fs;
		VariableMap<Honeycomb::Math::Vector4f> glVector4fs;
		
		/// Initializes a new Generic Struct using the specified Shader Source
		/// and the name of the struct as it appears in the Shader Source.
		/// const ShaderSource &sS : The Shader Source from which the Struct is
		///							 to be initialized.
		/// const string &structName : The name of the Struct in the Shader
		///							   Source.
		GenericStruct(const ShaderSource &sS, const std::string &structName);

		/// Virtual Destructor for destroying this Generic Struct.
		virtual ~GenericStruct();
	};
}

#endif