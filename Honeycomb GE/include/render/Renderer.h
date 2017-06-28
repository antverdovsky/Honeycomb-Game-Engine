#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "../geometry/Mesh.h"
#include "../graphics/Cubemap.h"
#include "../math/Vector4f.h"
#include "../scene/GameScene.h"
#include "../shader/ShaderProgram.h"

namespace Honeycomb { namespace Component { namespace Render { 
    class MeshRenderer; 
} } };

namespace Honeycomb { namespace Render {
	class Renderer {
		friend class Honeycomb::Component::Render::MeshRenderer;
	public:
		/// Represents the different types of Antialiasing supported by the
		/// engine.
		enum AntiAliasing {
			FXAA				= 0,
			NONE				= 1
		};

		/// Represents the modes used for the background of the scene
		enum BackgroundMode {
			SOLID_COLOR			= 0,
			SKYBOX				= 1
		};

		/// Represents the different color spaces supported
		enum ColorSpace {
			LINEAR				= 0,		// Standard Linear Color Space
			GAMMA_POST			= 1			// Post Processing Gamma Shader
		};

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

		/// Returns all of the shaders used in Post Processing the final image
		/// by reference.
		/// return : The modifiable list of all of the shaders used.
		std::vector<Honeycomb::Shader::ShaderProgram>& getPostShaders();

		/// Returns the height of the shadow map texture.
		/// return : The height.
		const int& getShadowMapHeight() const;

		/// Returns the width of the shadow map texture.
		/// return : The width.
		const int& getShadowMapWidth() const;

		/// Virtual method which should be overriden to render the specified
		/// scene.
		/// GameScene &scene : The game scene to be rendered.
		virtual void render(Honeycomb::Scene::GameScene &scene);

		/// Sets the Anti-Aliasing to the specified algorithm, or none.
		/// const AntiAliasing &aa : The Anti-Aliasing to be used when 
		///							 rendering the scene, or none.
		void setAntiAliasing(const AntiAliasing &aa);

		/// Sets the background mode which is to be used for rendering the
		/// background of the scene.
		/// const BackgroundMode &m : The mode which is to be used.
		void setBackgroundMode(const BackgroundMode &m);

		/// Sets the color space which is to be used when rendering the scene.
		/// const ColorSpace &cs : The color space.
		void setColorSpace(const ColorSpace &cs);

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

		/// Should the renderer post process the image according to the post
		/// processing shaders?
		/// const bool &b : True if the renderer should perform post processing
		///					and false otherwise.
		void setDoPostProcess(const bool &b);

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

		/// Sets the skybox which is to be used when rendering the background
		/// color of the scene.
		/// const Cubemap &sky : The skybox cubemap.
		void setSkybox(const std::shared_ptr<Honeycomb::Graphics::Cubemap> 
				&sky);

		/// Sets the solid color which is to be used when rendering the
		/// background color of the scene.
		/// const Vector4f &col : The solid color.
		void setSolidColor(const Honeycomb::Math::Vector4f &col);
	protected:
		static Renderer *renderer; // Singleton Instance

		// Antialiasing Variables
		AntiAliasing antiAliasing;
		Honeycomb::Shader::ShaderProgram fxaaShader;

		// Color Space Variables
		ColorSpace colorSpace;
		Honeycomb::Shader::ShaderProgram gammaShader;

		// Properties for a Background Color & Skybox
		BackgroundMode backgroundMode;
		std::shared_ptr<Honeycomb::Geometry::Mesh> cubemapMesh;
		Honeycomb::Math::Vector4f solidColor;
		Honeycomb::Shader::ShaderProgram solidColorShader;
		std::shared_ptr<Honeycomb::Graphics::Cubemap> skybox;
		Honeycomb::Shader::ShaderProgram skyboxShader;
		
		// Shadow Map Variables
		const static int SHADOW_MAP_WIDTH;
		const static int SHADOW_MAP_HEIGHT;
		// Classic/PCF Shadow Map Buffer, Texture and Shader
		int cShadowMapBuffer;
		std::unique_ptr<Honeycomb::Graphics::Texture2D> cShadowMapTexture;
		Honeycomb::Shader::ShaderProgram cShadowMapShader;
		Honeycomb::Shader::ShaderProgram cShadowMapLinearShader;
		// Variance Shadow Map Buffer, Texture and Shader
		int vShadowMapBuffer;
		std::unique_ptr<Honeycomb::Graphics::Texture2D> vShadowMapTexture;
		std::unique_ptr<Honeycomb::Graphics::Texture2D> vShadowMapTextureAA;
		Honeycomb::Shader::ShaderProgram vShadowMapShader;
		Honeycomb::Shader::ShaderProgram vShadowMapLinearShader;
		Honeycomb::Shader::ShaderProgram vsmGaussianBlurShader;
		
		// Shaders for post processing the Final Image
		std::vector<Honeycomb::Shader::ShaderProgram> postShaders;
		bool doPostProcess;

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

		/// Initializes the dependencies of the Cubemap (Mesh and Shaders).
		void initializeCubemapDependencies();

		/// Initializes the Shader used by the Gamma Correction Post Processing
		/// color spacec algorithm.
		void initializeGammaShader();

		/// Initializes the Shader used by the Fast Approximate Anti Aliasing
		/// (FXAA).
		void initializeFXAAShader();

		/// Initializes the dependencies of the Shadow Map.
		void initializeShadowMapDependencies();

		/// Calls the OpenGL "glEnable" function for the specified cap if val 
		/// is true. Otherwise, calls the OpenGL "glDisable" function
		/// for the specified cap.
		/// const int& &cap : The OpenGL parameter which is to be enabled or
		///					  disabled.
		/// const bool &val : Whether the setting is to be enabled or disabled.
		void setBoolSettingGL(const int &cap, const bool &val);

		/// Sets the value of the gamma to be used for non-linear color space.
		/// const float &g : The gamma value.
		virtual void setGamma(const float &g);
	};
} }

#endif
