#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "..\math\Vector4f.h"
#include "..\scene\GameScene.h"
#include "..\shader\ShaderProgram.h"

namespace Honeycomb::Render {
	class Renderer {
	public:
		/// Gets the singleton instance of the Renderer.
		/// return : The pointer to the singleton.
		static Renderer* getRenderer();

		/// Virtual method which should be overriden to render the specified
		/// scene.
		/// GameScene &scene : The game scene to be rendered.
		virtual void render(Honeycomb::Scene::GameScene &scene);
	protected:
		static Renderer *renderer; // Singleton Instance

		/// TODO: More Options
//		const int CULL_FACE = GL_BACK; // Which face should be culled
		const Honeycomb::Math::Vector4f CLEAR_SCREEN_COLOR = // Clear Color
			Honeycomb::Math::Vector4f(0.0F, 0.0F, 0.0F, 0.0F);
		const bool DEPTH_TEST = true; // Should depth tests occur?
		const bool DO_CULL_FACES = true; // Should the cull face be culled?
		const bool MSAA_SAMPLING = true; // Do Multisampling?
//		const int POLYGON_MODE = GL_FILL; // Render mode (wireframe, poly, etc)

		/// Initializes a new renderer and sets the appropriate OpenGL
		/// graphics settings to match the new engine instance.
		Renderer();

		/// Destroys this renderer.
		~Renderer();

		/// Calls the OpenGL "glEnable" function for the specified cap if val 
		/// is true. Otherwise, calls the OpenGL "glDisable" function
		/// for the specified cap.
		/// const int& &cap : The OpenGL parameter which is to be enabled or
		///					disabled.
		/// const bool &val : Whether the setting is to be enabled or disabled.
		void setBoolSettingGL(const int &cap, const bool &val);
	};
}

#endif