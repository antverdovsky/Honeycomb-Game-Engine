#pragma once
#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include "..\..\component\GameComponent.h"
#include "..\..\math\Vector4f.h"

namespace Honeycomb::Component::Light {
	class BaseLight : public Honeycomb::Component::GameComponent {
	public:
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