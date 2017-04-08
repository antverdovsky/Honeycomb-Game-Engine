#pragma once
#ifndef DEFERRED_RENDERER_H
#define DEFERRED_RENDERER_H

#include "GBuffer.h"
#include "../Renderer.h"

#include "../../geometry/Mesh.h"

namespace Honeycomb { namespace Render { namespace Deferred {
	class DeferredRenderer : public Honeycomb::Render::Renderer {
	public:
		// Enum representing what the final texture rendered should be.
		enum FinalTexture {
			POSITION				= GBufferTextureType::POSITION,
			NORMAL					= GBufferTextureType::NORMAL,

			DIFFUSE					= GBufferTextureType::DIFFUSE,
			SPECULAR				= GBufferTextureType::SPECULAR,
			
			DEPTH					= GBufferTextureType::DEPTH,

			FINAL					= GBufferTextureType::FINAL_1
		};

		/// Returns the Deferred Renderer singleton instance.
		/// return : A pointer to the singleton instance of the Deferred
		///			 Renderer structure.
		static DeferredRenderer* getDeferredRenderer();

		/// Renders the specified Game Scene using this Deferred Renderer.
		/// GameScene &scene : The scene which is to be rendered.
		void render(Honeycomb::Scene::GameScene &scene);

		/// Sets the final texture which will be rendered to the screen after
		/// the entire Deferred Renderer pipeline. Do note that the lights will
		/// ONLY be rendered for the FINAL texture, and that the background
		/// mode is IGNORED for the DEPTH Texture.
		/// const FinalTexture &fin : The final texture to be rendered.
		void setFinalTexture(const FinalTexture &fin);
	private:
		static DeferredRenderer *deferredRenderer; // Singleton instance

		// The directories of the Point and Spot Lights Volume models
		const static std::string POINT_LIGHT_VOLUME_MODEL;
		const static std::string SPOT_LIGHT_VOLUME_MODEL;

		// Full screen quad which is rendered with a GBuffer's texture
		Honeycomb::Geometry::Mesh quad;

		GBuffer gBuffer; // The G Buffer of the Renderer
		FinalTexture final; // The texture which will be rendered to screen

		Honeycomb::Shader::ShaderProgram geometryShader;
		Honeycomb::Shader::ShaderProgram quadShader;
		Honeycomb::Shader::ShaderProgram stencilShader;
		
		Honeycomb::Shader::ShaderProgram ambientShader;
		Honeycomb::Shader::ShaderProgram pointLightShader;
		Honeycomb::Shader::ShaderProgram directionalLightShader;
		Honeycomb::Shader::ShaderProgram spotLightShader;

		// The Point Light Volume (Icosphere) and the Spot Light Volume (Cone)
		Honeycomb::Object::GameObject *lightVolumePoint;
		Honeycomb::Object::GameObject *lightVolumeSpot;

		/// Initializes a new Deferred Renderer.
		DeferredRenderer();

		/// Destroys this Deferred Renderer.
		~DeferredRenderer();

		/// Initializes the Light Volumes used by the Spot and Point Light
		/// structures.
		void initializeLightVolumes();

		/// Initializes the Geometry Shader, Quad Shader, Stencil Shader, and
		/// the light component shaders.
		void initializeShaders();

		/// Initializes the Quad Mesh.
		void initializeQuad();

		/// Renders the background (solid color or skybox, depending on the
		/// settings of the Renderer) of the scene.
		void renderBackground();
		
		/// Postprocesses the image using the FXAA antialiasing correction
		/// algorithm.
		/// const GBufferTextureType &r : The buffer from which we read the
		///								  image which will be FXAA corrected.
		/// const GBufferTextureType &r : The buffer to which we write the
		///								  image which will be FXAA corrected.
		void renderFXAA(const GBufferTextureType &r, 
			const GBufferTextureType &w);

		/// Postprocesses the image using the Gamma correction algorithm.
		/// const GBufferTextureType &r : The buffer from which we read the
		///								  image which will be FXAA corrected.
		/// const GBufferTextureType &r : The buffer to which we write the
		///								  image which will be FXAA corrected.
		void renderGamma(const GBufferTextureType &r,
			const GBufferTextureType &w);

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

		/// Renders the specified Spot Light using Deferred Rendering.
		/// const SpotLight &pL : The spot light to be rendered.
		void renderLightSpot(const Honeycomb::Component::Light::SpotLight &sL);

		/// Renders the specified Base Light using a full screen quad.
		/// const BaseLight &bL : The base light to be rendered.
		/// const ShaderProgram &shader : The shader program to be used when
		///								  rendering the light quad.
		/// const string &name : The name of the light uniform in the Shader.
		void renderLightQuad(const Honeycomb::Component::Light::BaseLight &bL,
			Honeycomb::Shader::ShaderProgram &shader, const std::string
			&name);

		/// Renders the specified Base Light using a full screen quad.
		/// const BaseLight &bL : The base light to be rendered.
		/// GameObject &volume : The game object representing the volume
		///						 of the light to be rendered.
		/// const ShaderProgram &shader : The shader program to be used when
		///								  rendering the light quad.
		/// const string &name : The name of the light uniform in the Shader.
		void renderLightVolume(const Honeycomb::Component::Light::BaseLight
			&bL, Honeycomb::Object::GameObject &volume,
			Honeycomb::Shader::ShaderProgram &shader, const std::string
			&name);

		/// Renders the geometry of the specified scene.
		/// GameScene &scene : The scene whose geometry is to be rendered.
		void renderPassGeometry(Honeycomb::Scene::GameScene &scene);

		/// Renders the lights of the specified scene, if the final target of
		/// this Renderer is set to FINAL.
		/// GameScene &scene : The scene whose lights are to be rendered.
		void renderPassLight(Honeycomb::Scene::GameScene &scene);

		/// Post processes the specified target texture and returns the
		/// texture which contains the final "final" texture (post processed).
		/// return : The texture type containing the post processed image.
		GBufferTextureType renderPostProcess();

		/// Renders the specified texture to the screen.
		/// const GBufferTextureType &tex : The texture which is to be rendered
		///									as a full screen quad.
		void renderTexture(const GBufferTextureType &tex);

		/// Sets the value of the gamma to be used for non-linear color space.
		/// const float &g : The gamma value.
		void setGamma(const float &g);

		/// Performs the stencil pass on the light with the specified light
		///	volume.
		/// GameObject &volume : The object representing the light volume of 
		///						 the light.
		void stencilLightVolume(Honeycomb::Object::GameObject &volume);

		/// Scales and translates the Point Light's Sphere Volume based on the 
		/// attenuation, color, intensity and position of the specified point 
		/// light.
		/// const PointLight &pL : The Point Light for which the light volume
		///					       is to be transformed.
		void transformLightPointVolume(const Honeycomb::Component::Light::
				PointLight &pL);

		/// Scales and translates the Spot Light's Sphere Volume based on the 
		/// attenuation, color, intensity and position of the specified point 
		/// light.
		/// const SpotLight &sL : The Spot Light for which the light volume is
		///						  to be transformed.
		void transformLightSpotVolume(const Honeycomb::Component::Light::
				SpotLight &sL);
	};
} } }

#endif
