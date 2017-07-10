#pragma once
#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include "../GameComponent.h"
#include "../../math/Vector3f.h"
#include "../../shader/ShaderProgram.h"
#include "../../shader/GenericStruct.h"

namespace Honeycomb { namespace Component { namespace Light {
	enum LightType {
		LIGHT_TYPE_AMBIENT,			// Ambient Light
		LIGHT_TYPE_DIRECTIONAL,		// Directional Light
		LIGHT_TYPE_POINT,			// Point Light
		LIGHT_TYPE_SPOT				// Spot Light
	};

	enum ShadowType {
		SHADOW_NONE,				// Light uses no shadows

		// Classic Shadows:
		SHADOW_HARD,				// Light uses hard shadows with no aliasing
		SHADOW_INTERPOLATED,		// Light uses interpolated "soft" shadows
		SHADOW_PCF,					// Light uses PCF Soft Shadows
		SHADOW_PCF_INTERPOLATED,	// Light uses PCF Interpolated Soft Shadows

		// Variance Shadows:
		SHADOW_VARIANCE,			// Light uses Variance Shadow Mapping
		SHADOW_VARIANCE_AA			// Light uses Antialiased VSM
	};

	class BaseLight : 
			public Honeycomb::Shader::GenericStruct,
			public Honeycomb::Component::GameComponent {
	public:
		// Uniforms containing the color, intensity of the light
		static const std::string COLOR_VEC3;
		static const std::string INTENSITY_F;

		/// Initializes a new base light with the specified Shader Source and
		/// structure definition.
		/// const ShaderSource &src : The Shader Source in which this Light is
		///							  defined.
		/// const string &name : The name of the struct within the Shader
		///						 Source which defines this light (also the
		///						 component name).
		/// const LightType &type : The type of this Light.
		BaseLight(const Honeycomb::Shader::ShaderSource &src, const 
				std::string &name, const LightType &type);

		/// Clones this Base Light into a new, dynamically allocated,
		/// Base Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Base Light.
		std::unique_ptr<BaseLight> clone() const;
		
		/// Downcasts this light depending on the type of the light. The
		/// type passed to the template function must match the type of this
		/// light. If the type passed in does not match the type of this light,
		/// a nullptr will be returned instead.
		/// return : A constant pointer to the downcast instance; nullptr if 
		///			 the light could not be downcast.
		template<typename T> const T* downcast() const {
			return dynamic_cast<const T*>(this);
		}

		/// Downcasts this light depending on the type of the light. The
		/// type passed to the template function must match the type of this
		/// light. If the type passed in does not match the type of this light,
		/// a nullptr will be returned instead.
		/// return : A pointer to the downcast instance; nullptr if the light
		///			 could not be downcast.
		template<typename T> T* downcast() {
			return dynamic_cast<T*>(this);
		}

		/// Returns a reference to the color of this Base Light.
		/// return : The color reference.
		Honeycomb::Math::Vector3f& getColor();

		/// Returns a constant reference to the color of this Base Light.
		/// return : The constant color reference.
		const Honeycomb::Math::Vector3f& getColor() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Base Light.
		/// </summary>
		/// <returns>
		/// The Component ID of the Base Light Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// Returns a reference to the intensity of this Base Light.
		/// return : The intensity reference.
		float& getIntensity();

		/// Returns a constant reference to the intensity of this Base Light.
		/// return : The constant intensity reference.
		const float& getIntensity() const;

		/// Returns a constant reference to the type of this Light.
		/// return : The type of this light.
		const LightType& getType() const;
		//todo
		void onAttach() override;
		//todo
		void onDetach() override;

		/// Sets the color of this Base Light.
		/// const Vector4f &col : The new color of this BaseLight.
		void setColor(const Honeycomb::Math::Vector3f &col);

		/// Sets the intensity of this Base Light.
		/// const float &inten : The new intensity of this Base Light.
		void setIntensity(const float &inten);
	protected:
		LightType type; // The type of this Light
	private:
		virtual BaseLight* cloneInternal() const override;
	};

	class Attenuation :
			public Honeycomb::Shader::GenericStruct {
	public:
		// Struct File and Struct Name of the Attenuation Declaration
		static const std::string STRUCT_FILE;
		static const std::string STRUCT_NAME;

		// Uniforms containing the attenuation values
		static const std::string ATTENUATION_CONSTANT_F;
		static const std::string ATTENUATION_LINEAR_F;
		static const std::string ATTENUATION_QUADRATIC_F;
		
		/// Initializes default attenuation values of 1.0F for constant,
		/// 0.22F for linear, and 0.20 for quadratic.
		Attenuation();

		/// Initializes attenuation of the specified values.
		/// const float &atC : The constant attenuation value.
		/// const float &atL : The linear attenuation value.
		/// const float &atQ : The quadratic attenuation value.
		Attenuation(const float &atC, const float &atL, const float &atQ);

		/// Calculates the range for the light given the light, its attenuation
		///	and the minimum intensity of the light (the intensity of the light
		/// at its range).
		/// const BaseLight &bL : The base light for which the range is to be
		///						  computed.
		/// const Attenuation &atten : The attenuation of the light.
		///	const float &minI : The minimum intensity of the Light, at its 
		///						range. The intensity must be greater than zero.
		/// return : The recommended range of the light.
		static float calculateRange(const BaseLight &bL, const Attenuation 
				&atten, const float &minI = 5.0F / 256.0F);

		/// Returns a reference to the constant term of the attenuation.
		/// return : A reference to the constant term.
		float& getConstantTerm();

		/// Returns a constant reference to the constant term of the 
		///	attenuation.
		/// return : A constant reference to the constant term.
		const float& getConstantTerm() const;

		/// Returns a reference to the linear term of the attenuation.
		/// return : A reference to the linear term.
		float& getLinearTerm();

		/// Returns a constant reference to the linear term of the 
		///	attenuation.
		/// return : A constant reference to the linear term.
		const float& getLinearTerm() const;

		/// Returns a reference to the quadratic term of the attenuation.
		/// return : A reference to the quadratic term.
		float& getQuadraticTerm();

		/// Returns a constant reference to the quadratic term of the 
		///	attenuation.
		/// return : A constant reference to the quadratic term.
		const float& getQuadraticTerm() const;

		/// Sets the constant term of the attenuation.
		/// const float &atC : The new constant term of the attenuation.
		void setConstantTerm(const float &atC);

		/// Sets the linear term of the attenuation.
		/// const float &atL : The new linear term of the attenuation.
		void setLinearTerm(const float &atL);

		/// Sets the quadratic term of the attenuation.
		/// const float &atQ : The new quadratic term of the attenuation.
		void setQuadraticTerm(const float &atQ);
	};

	class Shadow :
			public Honeycomb::Shader::GenericStruct {
	public:
		// Struct File and Struct Name of the Shadow Declaration
		static const std::string STRUCT_FILE;
		static const std::string STRUCT_NAME;

		// Uniforms containing the Shadow Information values
		static const std::string INTENSITY_F;
		static const std::string MIN_BIAS_F;
		static const std::string MAX_BIAS_F;
		static const std::string PROJECTION_MAT4;
		static const std::string SHADOW_TYPE_I;
		static const std::string SOFTNESS_F;

		/// Returns a boolean indicating whether the following shadow is of 
		/// type SHADOW_HARD or SHADOW_PCF. The classic depth buffer should be
		/// used for these types of shadows.
		/// const ShadowType &shdw : The shadow type to be checked.
		/// return : True if the shadow is of type SHADOW_HARD or SHADOW_PCF.
		///			 False otherwise.
		static bool isClassicShadow(const ShadowType &shdw);

		/// Returns a boolean indicating whether the following shadow is of
		/// type SHADOW_VARIANCE. The variance RG16F buffer should be used for
		/// these types of shadows.
		/// const ShadowType &shdw : The shadow type to be checked.
		/// return : True if the shadow is of type SHADOW_VARIANCE. False
		///			 otherwise.
		static bool isVarianceShadow(const ShadowType &shdw);

		/// Initializes a default Shadow with a shadow type of Variance, 0.005F 
		/// minimum bias, 0.050F maximum bias, 0.75F intensity and 1.0F
		/// softness.
		Shadow();

		/// Initializes a Shadow with the specified shadow type.
		/// const ShadowType &shdw : The shadow type.
		Shadow(const ShadowType &shdw);

		/// Returns the intensity of this Shadow.
		/// return : The intensity value.
		const float& getIntensity() const;

		/// Returns the maximum bias of this Shadow.
		/// return : The bias value.
		const float& getMaximumBias() const;

		/// Returns the minimum bias of this Shadow.
		/// return : The bias value.
		const float& getMinimumBias() const;

		/// Returns the light projection of this Shadow.
		/// return : A constant reference to the projection.
		const Honeycomb::Math::Matrix4f& getProjection() const;

		/// Returns the shadow type of this Shadow.
		/// return : The shadow type enumeration.
		ShadowType getShadowType() const;

		/// Returns the softness of this Shadow.
		/// return : The softness value of the shadow.
		const float& getSoftness() const;

		/// Sets the intensity of this Shadow.
		/// const float &i : The intensity value.
		void setIntensity(const float &i);

		/// Sets the maximum bias of the Shadow (used when light is 
		/// perpendicular to the surface).
		/// const float &bias : The bias value.
		void setMaximumBias(const float &bias);

		/// Sets the minimum bias of the Shadow (used when light is parallel to
		/// the surface).
		/// const float &bias : The bias value.
		void setMinimumBias(const float &bias);

		/// Sets the projection of this Shadow.
		/// const Matrix4f &proj : The projection.
		void setProjection(const Honeycomb::Math::Matrix4f &proj);

		/// Sets the shadow type of this Shadow.
		/// const ShadowType &shdw : The shadow type.
		void setShadowType(const ShadowType &shdw);

		/// Sets the softness value of this Shadow.
		/// const float &soft : The softness value. The value should be clamped
		///                     between 0.0F and 1.0F.
		void setSoftness(const float &soft);
	};
} } }

#endif
