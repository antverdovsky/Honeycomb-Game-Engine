#pragma once
#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include "..\GameComponent.h"
#include "..\..\math\Vector4f.h"
#include "..\..\shader\ShaderProgram.h"
#include "..\..\shader\GenericStruct.h"

namespace Honeycomb::Component::Light {
	class BaseLight : 
			public Honeycomb::Shader::GenericStruct,
			public Honeycomb::Component::GameComponent {
	public:
		/// Initializes a new base light with the specified Shader Source and
		/// structure definition.
		/// const ShaderSource &src : The Shader Source in which this Light is
		///							  defined.
		/// const string &name : The name of the struct within the Shader
		///						 Source which defines this light (also the
		///						 component name).
		BaseLight(const Honeycomb::Shader::ShaderSource &src, const 
				std::string &name);

		/// Clones this Base Light into a new, dynamically allocated,
		/// Base Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Base Light.
		BaseLight* clone() const;

		/// Starts this base light.
		virtual void start();

		/// Stops this base light.
		virtual void stop();

		// The name of this light's uniform in the preferred shader. [temp: TODO]
		std::string uniformName;
	};
}

#endif