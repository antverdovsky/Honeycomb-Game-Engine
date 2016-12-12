#pragma once
#ifndef LEGACY_FORWARD_RENDERER
#define LEGACY_FORWARD_RENDERER

#include "Renderer.h"
#include "..\shader\ShaderProgram.h"

namespace Honeycomb::Render {
	class LegacyForwardRenderer : public Renderer {
	public:
		/// Returns the singleton instance of the Legacy Forward Renderer.
		/// return : The pointer to the singleton instance.
		static LegacyForwardRenderer* getLegacyForwardRenderer();

		/// Returns the shader which this Legacy Forward Renderer uses to
		/// render a scene.
		/// return : The constant pointer to the Shader Program.
		const Honeycomb::Shader::ShaderProgram* getShader() const;

		/// Renders the specified game scene using the shader attached to this
		/// Legacy Forward Renderer.
		/// GameScene &scene : The scene to be rendered.
		void render(Honeycomb::Scene::GameScene &scene);

		/// Sets the shader which this Legacy Forward Renderer uses to render
		/// to the specified shader.
		/// ShaderProgram* shader : The pointer to the Shader Program.
		void setShader(Honeycomb::Shader::ShaderProgram *shader);
	private:
		static LegacyForwardRenderer *legacyForwardRenderer; // Singleton
		
		// Shader with which the scene is to be drawn
		Honeycomb::Shader::ShaderProgram *shader;

		/// Initializes a new instance of the Legacy Forward Renderer.
		LegacyForwardRenderer();

		/// Destroys this instance of the Legacy Forward Renderer.
		~LegacyForwardRenderer();
	};
}

#endif