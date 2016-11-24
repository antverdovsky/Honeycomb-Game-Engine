#pragma once
#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include "..\..\component\GameComponent.h"
#include "..\..\conjuncture\Event.h"
#include "..\..\math\Vector4f.h"

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
			/// float c : The constant term of the Attenuation equation.
			/// float l : The linear term of the Attenuation equation.
			/// float q : The quadratic term of the Attenuation equation.
			Attenuation(float c, float l, float q);

			/// Destructs this Attenuation.
			~Attenuation();
			
			/// Gets all of the terms of this Attenuation.
			/// float &c : Where the constant term is to be written.
			/// float &l : Where the linear term is to be written.
			/// float &q : Where the quadratic term is to be written.
			void get(float &c, float &l, float &q);

			/// Gets the constant term in the attenuation equation.
			/// return : The value of the constant term.
			float getAttenuationConstant();

			/// Gets the linear term in the attenuation equation.
			/// return : The value of the linear term.
			float getAttenuationLinear();

			/// Gets the quadratic term in the attenuation equation.
			/// return : The value of the quadratic term.
			float getAttenuationQuadratic();

			/// Gets the event which is triggered when any of the three
			/// attenuation values are changed.
			/// return : The reference to the event.
			Honeycomb::Conjuncture::Event& getChangedEvent();

			/// Sets all of the terms of this Attenuation.
			/// float c : The new constant term of the Attenuation.
			/// float l : The new linear term of the Attenuation.
			/// float q : The new quadratic term of the Attenuation.
			void set(float c, float l, float q);

			/// Sets the constant term in the attenuation equation.
			/// float c : The new value of the constant term.
			void setAttenuationConstant(float c);

			/// Sets the linear term in the attenuation equation.
			/// float l : The new value of the linear term.
			void setAttenuationLinear(float l);

			/// Sets the quadratic term in the attenuation equation.
			/// float q : The new value of the quadratic term.
			void setAttenuationQuadratic(float q);
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

		/// Initializes a new base light with the given intensity and color.
		/// string nam : The name of this light.
		/// float inten : The intensity of the light [0, 1].
		/// Vector4f col : The color of the light ([0, 1], [0, 1], [0, 1],
		///				   [0, 1]).
		BaseLight(std::string nam, float inten, Honeycomb::Math::Vector4f col);

		/// Default Destructor.
		~BaseLight();

		/// Clones this Base Light into a new, dynamically allocated,
		/// Base Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Base Light.
		BaseLight* clone();
		
		/// Gets the color of the base light.
		/// return : The color.
		virtual Honeycomb::Math::Vector4f getColor();

		/// Gets the intensity of this base light.
		/// return : The intensity.
		virtual float getIntensity();

		/// Sets the color of this base light.
		/// Vector4f col : The new color.
		virtual void setColor(Honeycomb::Math::Vector4f col);

		/// Sets the intensity of this base light.
		/// float i : The new intensity.
		virtual void setIntensity(float i);

		/// Starts this base light.
		virtual void start();

		/// Writes the uniforms of this light to the Phong Shader.
		virtual void writeToShader();
	protected:
		float intensity; // The intensity of the light
		Honeycomb::Math::Vector4f color; // The color of the light
	private:
		std::string baseName; // The name of the light + ".base"
	};
}

#endif