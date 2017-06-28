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

			MATERIAL				= GBufferTextureType::MATERIAL,

			DEPTH					= GBufferTextureType::DEPTH,

			FINAL					= GBufferTextureType::FINAL_1,

			CLASSIC_SHADOW_MAP,
			VARIANCE_SHADOW_MAP
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

		const static int SHADOW_MAP_INDEX; // Index of Shadow Map Sampler2D

		// The directories of the Point and Spot Lights Volume models
		const static std::string POINT_LIGHT_VOLUME_MODEL;
		const static std::string SPOT_LIGHT_VOLUME_MODEL;

		// Full screen quad which is rendered with a GBuffer's texture
		std::unique_ptr<Honeycomb::Geometry::Mesh> quad;

		GBuffer gBuffer; // The G Buffer of the Renderer
		FinalTexture final; // The texture which will be rendered to screen

		// Geometry, Full Screen Quad and Stencil Shaders
		Honeycomb::Shader::ShaderProgram geometryShader;
		Honeycomb::Shader::ShaderProgram quadShader;
		Honeycomb::Shader::ShaderProgram stencilShader;
		
		// Shaders used by all of the lights
		Honeycomb::Shader::ShaderProgram ambientShader;
		Honeycomb::Shader::ShaderProgram pointLightShader;
		Honeycomb::Shader::ShaderProgram directionalLightShader;
		Honeycomb::Shader::ShaderProgram spotLightShader;

		// Meshes of the Light Volumes
		std::shared_ptr<Honeycomb::Geometry::Mesh> lightVolumePoint;
		std::shared_ptr<Honeycomb::Geometry::Mesh> lightVolumeSpot;

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
		/// settings of the Renderer) of the scene. The background is only
		/// rendered if the final texture target is NOT a depth or shadow map.
		void renderBackground();
		
		/// Renders the specified Ambient Light using Deferred Rendering.
		/// const AmbientLight &aL : The ambient light to be rendered.
		void renderLightAmbient(const Honeycomb::Component::Light::AmbientLight
			&aL);

		/// Renders the specified Directional Light using Deferred Rendering.
		/// const DirectionalLight &dL : The directional light to be rendered.
		/// const GameScene &scene : The scene to be rendered.
		void renderLightDirectional(const Honeycomb::Component::Light::
				DirectionalLight &dL, Honeycomb::Scene::GameScene &scene);

		/// Renders the specified Point Light using Deferred Rendering.
		/// const PointLight &pL : The point light to be rendered.
		void renderLightPoint(const Honeycomb::Component::Light::PointLight
			&pL);

		/// Renders the specified Spot Light using Deferred Rendering.
		/// const SpotLight &pL : The spot light to be rendered.
		/// const GameScene &scene : The scene to be rendered.
		void renderLightSpot(const Honeycomb::Component::Light::SpotLight &sL,
				Honeycomb::Scene::GameScene &scene);

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
		/// Mesh &volume : The game object representing the volume of the light
		///				   to be rendered.
		/// const ShaderProgram &shader : The shader program to be used when
		///								  rendering the light quad.
		/// const string &name : The name of the light uniform in the Shader.
		void renderLightVolume(const Honeycomb::Component::Light::BaseLight
			&bL, Honeycomb::Geometry::Mesh &volume,
			Honeycomb::Shader::ShaderProgram &shader, const std::string
			&name);

		/// Renders the geometry of the specified scene. Geometry is not
		/// rendered if the final target is a shadow map.
		/// GameScene &scene : The scene whose geometry is to be rendered.
		void renderPassGeometry(Honeycomb::Scene::GameScene &scene);

		/// Renders the lights of the specified scene, if the final target of
		/// this Renderer is set to FINAL. If the final target is set to
		/// shadow map, only the shadow map is rendered from the perspective of
		/// the light.
		/// GameScene &scene : The scene whose lights are to be rendered.
		void renderPassLight(Honeycomb::Scene::GameScene &scene);

		/// Writes the final texture target data to the GBuffer::FINAL_2 and
		/// performs post processing on the FINAL_2 buffer. At the end, the
		/// texture containing the final post processed image is returned.
		/// return : The texture containing the post processed final image.
		Honeycomb::Graphics::Texture2D& renderPassPostProcess();

		/// Reads in a texture from the read buffer, post processes it with the
		/// specified shader, and writes it to the write buffer. The read and
		/// write are then swapped so that the read equals the old write, and
		/// vice versa.
		/// ShaderProgram &shader : The shader program to be used to post
		///							process the texture.
		/// int &read : The GBuffer texture index containing the image to be
		///				post processed.
		/// int &write : The color attachment index into which the post 
		///				 processed image is to be drawn into.
		void renderPostProcessShader(Honeycomb::Shader::ShaderProgram &shader,
				int &read, int &write);

		/// Reads in a texture from the read texture, post processes it with 
		/// the specified shader, and writes it to the write buffer. The read
		/// texture is not modified. Note that the color attachment buffer is
		/// now changed to the write integer and must be changed back after
		/// this method completes!
		/// ShaderProgram &shader : The shader program to be used to post
		///							process the texture.
		/// const Texture2D &read : The texture from which to read.
		/// const int &write : The color attachment index into which the post 
		///					   processed image is to be drawn into.
		void renderPostProcessShader(Honeycomb::Shader::ShaderProgram &shader,
			const Honeycomb::Graphics::Texture2D &read, const int &write);

		/// Renders the shadow map of a flat light (Directional or Spot Light).
		/// const bool &linear : Should the depth be rendered linearly? (Yes
		///                      for spot lights, No for directional lights).
		/// const Shadow &shadow : The shadow information to be used when
		///                        rendering the light.
		/// GameScene &scene : The scene for which the shadow map is to be
		///					   rendered.
		/// const Vector3f &pos : Optional parameter specifying the position of
		///                       the light in world space. This should only be
		///                       used for linear lights.
		/// const float &zFar : Optional parameter specifying the z-far plane
		///                     value. This should only be used for linear 
		///                     lights.
		void renderTextureShadowMap(
				const bool &linear,
				const Honeycomb::Component::Light::Shadow &shadow,
				Honeycomb::Scene::GameScene &scene,
				const Honeycomb::Math::Vector3f &pos = 
					Honeycomb::Math::Vector3f(),
				const float &zFar = 0.0F);

		/// Renders the specified texture to the screen.
		/// const Texture2D &tex : The texture which is to be rendered as a 
		///						   full screen quad.
		void renderTexture(const Honeycomb::Graphics::Texture2D &tex);

		/// Sets the value of the gamma to be used for non-linear color space.
		/// const float &g : The gamma value.
		void setGamma(const float &g);

		/// Performs the stencil pass on the light with the specified light
		///	volume.
		/// Mesh &volume : The object representing the light volume of the 
		///				   light.
		void stencilLightVolume(Honeycomb::Geometry::Mesh &volume);

		/// Writes the transform of the point light to the stencil and point
		/// light shader.
		/// const PointLight &pL : The Point Light for which the light volume
		///					       is to be transformed.
		void writePointLightTransform(const Honeycomb::Component::Light::
				PointLight &pL);

		/// Writes the transform of the point light to the stencil and spot
		/// light shader.
		/// const SpotLight &sL : The Spot Light for which the light volume is
		///						  to be transformed.
		void writeSpotLightTransform(const Honeycomb::Component::Light::
				SpotLight &sL);

		/// Binds the shadow map of the specified shadow type to the specified
		/// shader.
		/// const ShadowType &shadow : The shadow type.
		/// ShaderProgram &shader : The shader to which the shadow map is to be
		///                         binded to.
		void writeShadowMapToShader(
				const Honeycomb::Component::Light::ShadowType &shadow, 
				Honeycomb::Shader::ShaderProgram &shader);
	};
} } }

#endif
