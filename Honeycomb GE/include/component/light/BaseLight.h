#pragma once
#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include "..\..\component\GameComponent.h"
#include "..\..\conjuncture\Event.h"
#include "..\..\math\Vector4f.h"
#include "..\..\shader\ShaderProgram.h"

namespace Honeycomb::Component::Light {
	class BaseLight : public Honeycomb::Component::GameComponent {
	public:
		class Attenuation {
		public:
			/// Initializes the Attenuation to the values: 1.0F for the 
			/// constant, 0.22F for the linear, 0.20F for the quadratic.
			Attenuation();

			/// Initializes the Attenuation to the specified constant, linear 
			/// and quadratic values.
			/// const float &c : The constant term of the Attenuation.
			/// const float &l : The linear term of the Attenuation.
			/// const float &q : The quadratic term of the Attenuation.
			Attenuation(const float &c, const float &l, const float &q);
			
			/// Gets all of the terms of this Attenuation.
			/// float &c : Where the constant term is to be written.
			/// float &l : Where the linear term is to be written.
			/// float &q : Where the quadratic term is to be written.
			void get(float &c, float &l, float &q) const;

			/// Gets the constant term in the attenuation equation.
			/// return : The constant reference to the constant term.
			const float& getAttenuationConstant() const;

			/// Gets the linear term in the attenuation equation.
			/// return : The constant reference to the linear term.
			const float& getAttenuationLinear() const;

			/// Gets the quadratic term in the attenuation equation.
			/// return : The constant reference to the quadratic term.
			const float& getAttenuationQuadratic() const;

			/// Gets the event which is triggered when any of the three
			/// attenuation values are changed.
			/// return : The reference to the event.
			Honeycomb::Conjuncture::Event& getChangedEvent();

			/// Gets the event which is triggered when any of the three
			/// attenuation values are changed.
			/// return : The constant reference to the event.
			const Honeycomb::Conjuncture::Event& getChangedEvent() const;

			/// Sets all of the terms of this Attenuation.
			/// const float &c : The new constant term of the Attenuation.
			/// const float &l : The new linear term of the Attenuation.
			/// const float &q : The new quadratic term of the Attenuation.
			void set(const float &c, const float &l, const float &q);

			/// Sets the constant term in the attenuation equation.
			/// const float &c : The new value of the constant term.
			void setAttenuationConstant(const float &c);

			/// Sets the linear term in the attenuation equation.
			/// const float &l : The new value of the linear term.
			void setAttenuationLinear(const float &l);

			/// Sets the quadratic term in the attenuation equation.
			/// const float &q : The new value of the quadratic term.
			void setAttenuationQuadratic(const float &q);

			/// Writes this attenuation to the specified Shader.
			/// ShaderProgram &shader : Reference to the shader to which the 
			///							attenuation is to be written to.
			/// const string &uni : Name of the attenuation uniform in the 
			///						shader.
			void toShader(Honeycomb::Shader::ShaderProgram &shader, const 
					std::string &uni);
		protected:
			/// Variables for the Attenuation calculation
			float attenConstant;
			float attenLinear;
			float attenQuadratic;
			
			// Attenuation change (constant, linear, or quadratic) event.
			Honeycomb::Conjuncture::Event attenuationChange;
		};

		/// Initializes a new base light with the name "light", an intensity of
		/// 1.0F and a white (1, 1, 1, 1) color.
		BaseLight();

		/// Initializes a new base light with the specified name, an intensity
		/// of 1.0F and a white (1, 1, 1, 1) color.
		/// const std::string &nam : The name of the base light.
		BaseLight(const std::string &nam);

		/// Initializes a new base light with the given intensity and color.
		/// const string &nam : The name of this light.
		/// const float &inten : The intensity of the light [0, 1].
		/// const Vector4f& col : The color of the light ([0, 1], [0, 1], 
		///						  [0, 1], [0, 1]).
		BaseLight(const std::string &nam, const float &inten, 
				const Honeycomb::Math::Vector4f &col);

		/// Destroys this Base Light.
		virtual ~BaseLight();

		/// Clones this Base Light into a new, dynamically allocated,
		/// Base Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Base Light.
		BaseLight* clone() const;

		/// Gets the color of the base light.
		/// return : The color.
		const Honeycomb::Math::Vector4f& getColor() const;

		/// Gets the intensity of this base light.
		/// return : The intensity.
		const float& getIntensity() const;

		/// Gets the Shader of this base light.
		/// return : The pointer to the Shader.
		Honeycomb::Shader::ShaderProgram* getShader();

		/// Sets the color of this base light.
		/// const Vector4f &col : The constant reference to the color.
		virtual void setColor(const Honeycomb::Math::Vector4f &col);

		/// Sets the intensity of this base light.
		/// const float &i : The constant reference to the intensity.
		virtual void setIntensity(const float &i);

		/// Starts this base light.
		virtual void start();

		/// Stops this base light.
		virtual void stop();

		/// Writes the parameters of this base light into its preferred shader.
		virtual void toShader();
	protected:
		// The Shader with which this Light prefers to be rendered, and the
		// uniform name of this light within said shader.
		Honeycomb::Shader::ShaderProgram *shader;
		std::string shaderUniform;

		float intensity; // The intensity of the light
		Honeycomb::Math::Vector4f color; // The color of the light
	};
}

#endif