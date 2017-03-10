#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "..\math\Vector4f.h"
#include "..\scene\GameScene.h"
#include "..\shader\ShaderProgram.h"

namespace Honeycomb::Component::Render { class MeshRenderer; };

namespace Honeycomb::Render {
	class Renderer {
		friend class Honeycomb::Component::Render::MeshRenderer;
	public:
		/// A wrapper enum for the depth and stencil functions which can be 
		///	used when depth or stencil testing.
		enum TestFunction {
			NEVER				= 0x0200,	// from GL_NEVER
			LESS				= 0x0201,	// from GL_LESS
			EQUAL				= 0x0202,	// from GL_EQUAL
			LESS_OR_EQUAL		= 0x0203,	// from GL_LEQUAL
			GREATER				= 0x0204,	// from GL_GREATER
			NOT_EQUAL			= 0x0205,	// from GL_NOTEQUAL
			GREATER_OR_EQUAL	= 0x0206,	// from GL_GEQUAL
			ALWAYS				= 0x0207	// from GL_ALWAYS
		};

		/// A wrapper enum for the front, back and front-and-back faces of a
		/// polygon.
		enum PolygonFace {
			BACK				= 0x405,	// from GL_BACK
			FRONT				= 0x404,	// from GL_FRONT
			FRONT_AND_BACK		= 0x408		// from GL_FRONT_AND_BACK
		};

		/// A wrapper enum for the polygon modes, using which, a face can be
		///	rendered.
		enum PolygonMode {
			POINT				= 0x1B00,	// from GL_POINT
			LINE				= 0x1B01,	// from GL_LINE	
			FILL				= 0x1B02	// from GL_FILL
		};

		/// A wrapper enum for the clockwise and counterclockwise winding
		/// orders.
		enum WindingOrder {
			CLOCKWISE			= 0x0900,	// from GL_CW
			COUNTER_CLOCKWISE	= 0x0901	// from GL_CCW
		};

		/// Gets the singleton instance of the Renderer.
		/// return : The pointer to the singleton.
		static Renderer* getRenderer();

		/// Virtual method which should be overriden to render the specified
		/// scene.
		/// GameScene &scene : The game scene to be rendered.
		virtual void render(Honeycomb::Scene::GameScene &scene);

		/// Sets the polygon face which is to be culled.
		/// const PolygonFace &f : The polygon face (front, back or front-and-
		///						   back).
		void setCullingFace(const PolygonFace &f);
		
		/// Sets the depth function which is to be used when depth testing.
		/// const TestFunction &f : The function which is to be used.
		void setDepthFunction(const TestFunction &f);

		/// Should the renderer cull the non-normal faces?
		/// const bool &b : True if the renderer should cull the non-normal
		///					faces, false otherwise.
		void setDoCullFaces(const bool &b);

		/// Should the renderer perform a depth test when rendering faces?
		/// const bool &b : True if the renderer should perform a depth test,
		///					false otherwise.
		void setDoDepthTest(const bool &b);

		/// Should the renderer perform a stencil test when rendering faces?
		/// const bool &b : True if the renderer should perform a stencil test,
		///				    false otherwise.
		void setDoStencilTest(const bool &b);

		/// Sets the winding order of the Front Face of a polygon.
		/// const WindingOrder &w : The winding order (either clockwise or
		///							counterclockwise).
		void setFrontFace(const WindingOrder &w);

		/// Sets the polygon rasterization mode of the specified face type.
		/// const PolygonFace &f : The face for which the Polygon rasterization
		///						   mode is to be set.
		/// const PolygonMode &m : The rasterization mode which is to be used
		///						   for rendering said faces.
		void setPolygonMode(const PolygonFace &f, const PolygonMode &m);
	protected:
		static Renderer *renderer; // Singleton Instance

		// Face culling variables
		PolygonFace cullingFace;
		WindingOrder frontFace;
		bool doCullFaces;
		
		// Should the depth test be run, and which function should be used?
		bool doDepthTest;
		TestFunction depthFunction;

		// Polygon modes for rendering back and front faces
		PolygonMode polygonModeBack;
		PolygonMode polygonModeFront;

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