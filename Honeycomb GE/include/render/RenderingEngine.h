#pragma once
#ifndef RENDERING_ENGINE
#define RENDERING_ENGINE

#include "Renderer.h"
#include "../scene/GameScene.h"

namespace Honeycomb { namespace Render {
	enum RenderingType {
		TYPE_DEFERRED_RENDERER
	};

	class RenderingEngine {
		friend class Renderer;
	public:
		/// Returns the pointer to the singleton instance of the rendering
		/// engine.
		/// return : A pointer to the Rendering Engine singleton.
		static RenderingEngine* getRenderingEngine();

		/// Renders the specified scene using the render stored in this
		/// Rendering Engine.
		/// GameScene &scene : The game scene to be rendered.
		void render(Honeycomb::Scene::GameScene &scene);

		/// Sets the rendering type which this rendering engine should use when
		/// rendering.
		/// const RenderingType &type : The type of rendering to be used.
		void setRenderingType(const RenderingType &type);
	private:
		static RenderingEngine *renderingEngine; // Singleton Instance

		Honeycomb::Render::Renderer *renderer; // Renderer to be used

		/// Initializes a new instance of the Rendering Engine. The default
		/// rendering type will be set to LEGACY_FORWARD_RENDERER.
		RenderingEngine();

		/// Deletes this instance of the Rendering Engine.
		~RenderingEngine();
	};
} }

#endif
