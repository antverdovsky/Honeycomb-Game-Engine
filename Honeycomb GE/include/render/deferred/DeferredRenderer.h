#pragma once
#ifndef DEFERRED_RENDERER_H
#define DEFERRED_RENDERER_H

#include "GBuffer.h"
#include "..\Renderer.h"

#include "..\..\geometry\Mesh.h"

namespace Honeycomb::Render::Deferred {
	class DeferredRenderer : public Honeycomb::Render::Renderer {
	public:
		/// Returns the Deferred Renderer singleton instance.
		/// return : A pointer to the singleton instance of the Deferred
		///			 Renderer structure.
		static DeferredRenderer* getDeferredRenderer();

		/// Renders the specified Game Scene using this Deferred Renderer.
		/// GameScene &scene : The scene which is to be rendered.
		void render(Honeycomb::Scene::GameScene &scene);
	private:
		static DeferredRenderer *deferredRenderer; // Singleton instance

		Honeycomb::Geometry::Mesh quad; // Quad to which buffer is rendered

		GBuffer gBuffer; // The G Buffer of the Renderer

		Honeycomb::Shader::ShaderProgram geometryShader;
		Honeycomb::Shader::ShaderProgram quadShader;
		Honeycomb::Shader::ShaderProgram stencilShader;
		
		Honeycomb::Shader::ShaderProgram ambientShader;
		Honeycomb::Shader::ShaderProgram pointLightShader;
		Honeycomb::Shader::ShaderProgram directionalLightShader;

		Honeycomb::Object::GameObject *pointLightIcosphere;
		Honeycomb::Object::GameObject *directionalLightPlane;

		/// Initializes a new Deferred Renderer.
		DeferredRenderer();

		/// Destroys this Deferred Renderer.
		~DeferredRenderer();

		/// Renders the final produced texture from the GBuffer to the screen.
		void renderFinal();

		/// Renders the geometry of the specified scene.
		/// GameScene &scene : The scene whose geometry is to be rendered.
		void renderGeometryPass(Honeycomb::Scene::GameScene &scene);

		/// Renders the lights of the specified scene.
		/// GameScene &scene : The scene whose lights are to be rendered.
		void renderLightsPass(Honeycomb::Scene::GameScene &scene);

		/// Renders the specified Ambient Light using Deferred Rendering.
		/// const AmbientLight &aL : The ambient light to be rendered.
		void renderLightAmbient(const Honeycomb::Component::Light::AmbientLight
				&aL);

		/// Renders the specified Directional Light using Deferred Rendering.
		/// const DirectionalLight &dL : The directional light to be rendered.
		void renderLightDirectional(const Honeycomb::Component::Light::
				DirectionalLight &dL);

		/// Renders the specified Point Light using Deferred Rendering.
		/// const PointLight &pL : The point light to be rendered.
		void renderLightPoint(const Honeycomb::Component::Light::PointLight	
				&pL);
		
		/// Performs the stencil pass on the specified Point Light.
		/// const PointLight &pL : The point light to be rendered.
		void stencilLightPoint(const Honeycomb::Component::Light::PointLight 
				&pL);

		/// Scales and translates the Point Light's Sphere Volume based on the 
		/// attenuation, color, intensity and position of the specified point 
		/// light. The range of the light will also be modified to reflect the
		/// scale of the light sphere volume.
		/// PointLight &pL : The Point Light for which the light volume
		///					 is to be transformed.
		void transformLightPointVolume(Honeycomb::Component::Light::
			PointLight &pL);
	};
}

#endif