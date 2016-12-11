#pragma once
#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <GL\glew.h>

#include "..\math\Vector4f.h"
#include "..\scene\GameScene.h"
#include "..\shader\ShaderProgram.h"

namespace Honeycomb::Core {
	class RenderEngine {
	public:
		/// Gets the singleton instance of the Rendering Engine.
		/// return : The pointer to the singleton.
		static RenderEngine* getRenderEngine();

		/// Renders the current active scene, if it is not null.
		void render();

		/// Renders the specified scene.
		/// GameScene &scene : The game scene to be rendered.
		void render(Honeycomb::Scene::GameScene &scene);
	private:
		static RenderEngine *renderEngine; // Singleton instance

		Honeycomb::Math::Vector4f clearScreenColor = // Clear Screen Color
			Honeycomb::Math::Vector4f(0.0F, 0.0F, 1.0F, 0.0F);

		/// Initializes a new rendering engine and sets the appropriate OpenGL
		/// graphics settings to match the new engine instance.
		RenderEngine();

		/// Destroys this rendering engine.
		~RenderEngine();

		/// Sets the OpenGL graphics settings to match those of this instance.
		void setOpenGLSettings();
	};
}

#endif