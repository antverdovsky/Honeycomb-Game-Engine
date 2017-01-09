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

		/// Initializes a new Deferred Renderer.
		DeferredRenderer();

		/// Destroys this Deferred Renderer.
		~DeferredRenderer();

		/// Renders the geometry of the specified scene.
		/// GameScene &scene : The scene whose geometry is to be rendered.
		void renderGeometry(Honeycomb::Scene::GameScene &scene);

		/// Renders the lights of the specified scene.
		/// GameScene &scene : The scene whose lights are to be rendered.
		void renderLights(Honeycomb::Scene::GameScene &scene);
	};
}

#endif