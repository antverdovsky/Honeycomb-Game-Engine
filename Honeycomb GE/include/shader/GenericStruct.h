#pragma once
#ifndef GENERIC_STRUCT_H
#define GENERIC_STRUCT_H

#include <unordered_map>

#include "ShaderProgram.h"
#include "../debug/Logger.h"
#include "../graphics/Texture2D.h"
#include "../math/Matrix4f.h"
#include "../math/Vector2f.h"
#include "../math/Vector3f.h"
#include "../math/Vector4f.h"

namespace Honeycomb { namespace Shader {
	/// <summary>
	/// Represents a map between the name of some variable and its value. The
	/// name of the variable is typically the name of the uniform for a Shader.
	/// </summary>
	template<typename T>
	class VariableMap {
		friend class GenericStruct;
	public:
		/// <summary>
		/// Gets the value of the variable of the specified name stored in this
		/// Variable Map.
		/// </summary>
		/// <param name="name">
		/// The name of the variable.
		/// </param>
		/// <returns>
		/// The reference to the variable. If the variable cannot be found, an
		/// out_of_range exception is thrown.
		/// </returns>
		/// <exception cref="out_of_range">
		/// If this variable map does not contain a variable with the specified
		/// name.
		/// </exception>
		T& getValue(const std::string &name) {
			return this->map.at(name);
		}

		/// <summary>
		/// Gets the value of the variable of the specified name stored in this
		/// Variable Map.
		/// </summary>
		/// <param name="name">
		/// The name of the variable.
		/// </param>
		/// <returns>
		/// The constant reference to the variable. If the variable cannot be 
		/// found, an out_of_range exception is thrown.
		/// </returns>
		/// <exception cref="out_of_range">
		/// If this variable map does not contain a variable with the specified
		/// name.
		/// </exception>
		const T& getValue(const std::string &name) const {
			return this->map.at(name);
		}
		
		/// <summary>
		/// Sets the value of the variable of the specified name stored in this
		/// Variable Map to the specified value. If the map does not contain
		/// the variable, a out_of_range exception is thrown.
		/// </summary>
		/// <param name="name">
		/// The name of the variable.
		/// </param>
		/// <param name="value">
		/// The new value to be assigned to the variable
		/// </param>
		/// <exception cref="out_of_range">
		/// If this variable map does not contain a variable with the specified
		/// name.
		/// </exception>
		void setValue(const std::string &name, const T &value) {
			this->getValue(name) = value;
		}
	private:
		std::unordered_map<std::string, T> map;
	};

	/// <summary>
	/// Represents any Generic GLSL Structure. This structure stores the
	/// variable maps of all of the variable types of a GLSL structure, where
	/// each variable map contains the name of the variable and the 
	/// corresponding variable value.
	/// </summary>
	class GenericStruct {
	public:
		/// <summary>
		/// Returns the variable map of floats stored in this structure.
		/// </summary>
		/// <returns>
		/// The reference to the map of the names of each float to its value.
		/// </returns>
		VariableMap<float>& getFloats();

		/// <summary>
		/// Returns the variable map of floats stored in this structure.
		/// </summary>
		/// <returns>
		/// The constant reference to the map of the names of each float to its
		/// value.
		/// </returns>
		const VariableMap<float>& getFloats() const;

		/// <summary>
		/// Returns the variable map of ints stored in this structure.
		/// </summary>
		/// <returns>
		/// The reference to the map of the names of each int to its value.
		/// </returns>
		VariableMap<int>& getInts();

		/// <summary>
		/// Returns the variable map of ints stored in this structure.
		/// </summary>
		/// <returns>
		/// The constant reference to the map of the names of each int to its
		/// value.
		/// </returns>
		const VariableMap<int>& getInts() const;

		/// <summary>
		/// Returns the variable map of Matrix4fs stored in this structure.
		/// </summary>
		/// <returns>
		/// The reference to the map of the names of each Matrix4f to its 
		/// value.
		/// </returns>
		VariableMap<Honeycomb::Math::Matrix4f>& getMatrix4fs();

		/// <summary>
		/// Returns the variable map of Matrix4fs stored in this structure.
		/// </summary>
		/// <returns>
		/// The constant reference to the map of the names of each Matrix4f to 
		/// its value.
		/// </returns>
		const VariableMap<Honeycomb::Math::Matrix4f>& getMatrix4fs() const;

		/// <summary>
		/// Returns the name of the struct for which this Generic Struct is
		/// defined.
		/// </summary>
		/// <returns>
		/// The name of the struct as a string.
		/// </returns>
		const std::string& getStructName() const;

		/// <summary>
		/// Returns the variable map of Sampler2Ds stored in this structure.
		/// </summary>
		/// <returns>
		/// The reference to the map of the names of each Sampler2D to its 
		/// value.
		/// </returns>
		VariableMap<std::shared_ptr<const Honeycomb::Graphics::Texture2D>>& 
				getSampler2Ds();

		/// <summary>
		/// Returns the variable map of Sampler2Ds stored in this structure.
		/// </summary>
		/// <returns>
		/// The constant reference to the map of the names of each Sampler2D to 
		/// its value.
		/// </returns>
		const VariableMap<std::shared_ptr<
				const Honeycomb::Graphics::Texture2D>>& getSampler2Ds() const;

		/// <summary>
		/// Returns the shader source which contains this Generic Struct
		/// definition.
		/// </summary>
		/// <returns>
		/// The constant reference to the shader source.
		/// </returns>
		const ShaderSource& getShaderSource() const;

		/// <summary>
		/// Returns the variable map of Vector2fs stored in this structure.
		/// </summary>
		/// <returns>
		/// The reference to the map of the names of each Vector2f to its 
		/// value.
		/// </returns>
		VariableMap<Honeycomb::Math::Vector2f>& getVector2fs();

		/// <summary>
		/// Returns the variable map of Vector2fs stored in this structure.
		/// </summary>
		/// <returns>
		/// The constant reference to the map of the names of each Vector2f to 
		/// its value.
		/// </returns>
		const VariableMap<Honeycomb::Math::Vector2f>& getVector2fs() const;

		/// <summary>
		/// Returns the variable map of Vector3fs stored in this structure.
		/// </summary>
		/// <returns>
		/// The reference to the map of the names of each Vector3f to its 
		/// value.
		/// </returns>
		VariableMap<Honeycomb::Math::Vector3f>& getVector3fs();

		/// <summary>
		/// Returns the variable map of Vector3fs stored in this structure.
		/// </summary>
		/// <returns>
		/// The constant reference to the map of the names of each Vector3f to 
		/// its value.
		/// </returns>
		const VariableMap<Honeycomb::Math::Vector3f>& getVector3fs() const;

		/// <summary>
		/// Returns the variable map of Vector4fs stored in this structure.
		/// </summary>
		/// <returns>
		/// The reference to the map of the names of each Vector4f to its 
		/// value.
		/// </returns>
		VariableMap<Honeycomb::Math::Vector4f>& getVector4fs();

		/// <summary>
		/// Returns the variable map of Vector4fs stored in this structure.
		/// </summary>
		/// <returns>
		/// The constant reference to the map of the names of each Vector4f to 
		/// its value.
		/// </returns>
		const VariableMap<Honeycomb::Math::Vector4f>& getVector4fs() const;

		/// <summary>
		/// Writes the value of each uniform stored in this GenericStruct to
		/// the specified Shader under the specified uniform name.
		/// </summary>
		/// <param name="shader">
		/// The shader to which this structure's variable values are to be
		/// written to.
		/// </param>
		/// <param name="uni">
		/// The name of the uniform of the GLSL struct in the specified shader.
		/// </param>
		virtual void toShader(ShaderProgram &shader, const std::string &uni) 
				const;
	protected:
		// For each map, the key is the uniform name as it is found in a GLSL
		// Struct, and the value is the uniform value.
		mutable VariableMap<float> glFloats;
		mutable VariableMap<int> glInts;
		mutable VariableMap<Honeycomb::Math::Matrix4f> glMatrix4fs;
		mutable VariableMap<Honeycomb::Math::Vector2f> glVector2fs;
		mutable VariableMap<Honeycomb::Math::Vector3f> glVector3fs;
		mutable VariableMap<Honeycomb::Math::Vector4f> glVector4fs;
		mutable VariableMap<std::shared_ptr<
				const Honeycomb::Graphics::Texture2D>> glSampler2Ds;

		/// <summary>
		/// Initializes a new GLSL Generic Structure instance. This constructor
		/// automatically finds all of the uniforms declared in the specified
		/// shader source and adds them to this Generic Structure. For each
		/// variable type, a default, generic value is assigned.
		/// </summary>
		/// <param name="sS">
		/// The shader source in which the structure of the name 
		/// <paramref name="structName"/> is located.
		/// </param>
		/// <param name="structName">
		/// The name of the structure for which this Generic Struct is being
		/// built. This must be a declared struct inside of the 
		/// <paramref name="sS"/> shader source.
		/// </param>
		GenericStruct(const ShaderSource &sS, const std::string &structName);

		ShaderSource shaderSource;  // Shader Source where Struct is defined
		std::string structName;     // Name of the Struct in the Shader Source
	};
} }

#endif
