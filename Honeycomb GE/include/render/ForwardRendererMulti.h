#pragma once
#ifndef FORWARD_RENDERER_MULTI
#define FORWARD_RENDERER_MULTI

#include "Renderer.h"
#include "..\scene\GameScene.h"
#include "..\shader\ShaderProgram.h"

namespace Honeycomb::Render {
	class ForwardRendererMulti : public Renderer {
	public:
		/// Returns the singleton instance of the forward renderer multi-pass
		/// renderer.
		/// return : The pointer to the singleton instance.
		static ForwardRendererMulti* getForwardRendererMulti();

		/// Renders the specified game scene in multiple passes using the
		/// shaders stored in this instance.
		/// GameScene &scene : The reference to the scene to be rendered.
		void render(Honeycomb::Scene::GameScene &scene);
	private:
		static ForwardRendererMulti* forwardRendererMulti; // Singleton

		/// Instantiates a new instance of the Forward Renderer Mutli-pass
		/// Renderer.
		ForwardRendererMulti();
		
		/// Deletes this instance of the Forward Renderer Multi-pass Renderer.
		~ForwardRendererMulti();
	};
}

#endif