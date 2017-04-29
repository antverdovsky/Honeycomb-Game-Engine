#include "../../../include/render/deferred/DeferredRenderer.h"

#include <GL/glew.h>

#include "../../../include/base/GameWindow.h"

#include "../../../include/component/light/AmbientLight.h"
#include "../../../include/component/light/BaseLight.h"
#include "../../../include/component/light/DirectionalLight.h"
#include "../../../include/component/light/PointLight.h"
#include "../../../include/component/light/SpotLight.h"
#include "../../../include/component/physics/Transform.h"
#include "../../../include/component/render/CameraController.h"
#include "../../../include/component/render/MeshRenderer.h"

#include "../../../include/geometry/Vertex.h"
#include "../../../include/object/Builder.h"

using Honeycomb::Base::GameWindow;
using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Light::PointLight;
using Honeycomb::Component::Light::SpotLight;
using Honeycomb::Component::Light::LightType;
using Honeycomb::Component::Light::Shadow;
using Honeycomb::Component::Light::ShadowType;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::CameraController;
using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Geometry::Mesh;
using Honeycomb::Geometry::Vertex;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Object::Builder;
using Honeycomb::Object::GameObject;
using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderType;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb { namespace Render { namespace Deferred {
	DeferredRenderer* DeferredRenderer::deferredRenderer = nullptr;

	const std::string DeferredRenderer::POINT_LIGHT_VOLUME_MODEL =
		"../Honeycomb GE/res/models/light-volumes/pointLight.fbx";
	const std::string DeferredRenderer::SPOT_LIGHT_VOLUME_MODEL =
		"../Honeycomb GE/res/models/light-volumes/spotLight.fbx";
	const int DeferredRenderer::SHADOW_MAP_INDEX = GBufferTextureType::COUNT;

	DeferredRenderer* DeferredRenderer::getDeferredRenderer() {
		if (DeferredRenderer::deferredRenderer == nullptr)
			DeferredRenderer::deferredRenderer = new DeferredRenderer();

		return DeferredRenderer::deferredRenderer;
	}

	void DeferredRenderer::render(Honeycomb::Scene::GameScene &scene) {
		Texture2D target; // Target containing the final image

		CameraController::getActiveCamera()->toShader(this->geometryShader,
			"camera");
		this->gBuffer.frameBegin(); 

		this->renderPassGeometry(scene);		// Render Geometry
		this->renderPassLight(scene);			// Render Lights
		this->renderBackground();				// Render Background Cubebox
		
		target = this->renderPassPostProcess(); // Post Process the Final Image
		this->renderTexture(target);			// Render the final image
	}

	void DeferredRenderer::setFinalTexture(const FinalTexture &fin) {
		this->final = fin;
	}

	DeferredRenderer::DeferredRenderer() : Renderer() {
		this->gBuffer.initialize();

		this->initializeLightVolumes();
		this->initializeQuad();
		this->initializeShaders();

		this->setFinalTexture(FinalTexture::FINAL);
		
		// Even though the color space is set in the parent Renderer class, we
		// have to set it here again since we must write the gamma value to our
		// geometry pass shader.
		this->setColorSpace(ColorSpace::GAMMA_POST);
	}

	DeferredRenderer::~DeferredRenderer() {
		
	}

	void DeferredRenderer::initializeLightVolumes() {
		// Get the models containing the Light Volumes
		GameObject *pLModel = Builder::getBuilder()->newModel(
			POINT_LIGHT_VOLUME_MODEL);
		GameObject *sLModel = Builder::getBuilder()->newModel(
			SPOT_LIGHT_VOLUME_MODEL);

		// Extract the actual light volume meshes from the Model
		this->lightVolumePoint = pLModel->getChild("Icosphere")->
			getComponent<MeshRenderer>()->getMesh();
		this->lightVolumeSpot = sLModel->getChild("Cube")->
			getComponent<MeshRenderer>()->getMesh();

		// Delete the Light Volume Models
		delete pLModel;
		delete sLModel;
	}

	void DeferredRenderer::initializeShaders() {
		this->ambientShader.initialize();
		this->ambientShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/geometry/simpleVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->ambientShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/light/blinn-phong/ambientLightFS.glsl",
			ShaderType::FRAGMENT_SHADER);
		this->ambientShader.finalizeShaderProgram();

		this->directionalLightShader.initialize();
		this->directionalLightShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/geometry/simpleVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->directionalLightShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/light/blinn-phong/directionalLightFS.glsl",
			ShaderType::FRAGMENT_SHADER);
		this->directionalLightShader.finalizeShaderProgram();

		this->pointLightShader.initialize();
		this->pointLightShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/light/blinn-phong/lightVS.glsl",
			ShaderType::VERTEX_SHADER);
		this->pointLightShader.addShader("../Honeycomb GE/res/shaders/"
			"/render/deferred/light/blinn-phong/pointLightFS.glsl",
			ShaderType::FRAGMENT_SHADER);
		this->pointLightShader.finalizeShaderProgram();

		this->spotLightShader.initialize();
		this->spotLightShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/light/blinn-phong/lightVS.glsl",
			ShaderType::VERTEX_SHADER);
		this->spotLightShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/light/blinn-phong/spotLightFS.glsl",
			ShaderType::FRAGMENT_SHADER);
		this->spotLightShader.finalizeShaderProgram();
		
		this->geometryShader.initialize();
		this->geometryShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/geometry/geometryVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->geometryShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/geometry/geometryFS.glsl", 
			ShaderType::FRAGMENT_SHADER);
		this->geometryShader.finalizeShaderProgram();

		this->stencilShader.initialize();
		this->stencilShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/geometry/stencilVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->stencilShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/geometry/stencilFS.glsl", 
			ShaderType::FRAGMENT_SHADER);
		this->stencilShader.finalizeShaderProgram();

		this->quadShader.initialize();
		this->quadShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/geometry/simpleVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->quadShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/geometry/simpleFS.glsl", 
			ShaderType::FRAGMENT_SHADER);
		this->quadShader.finalizeShaderProgram();
	}

	void DeferredRenderer::initializeQuad() {
		// The vertices for a full screen Quad
		Vertex quadVerts[4] = {
			Vertex(Vector3f(-1.0F, -1.0F, 0.0F), Vector3f(0.0F, 0.0F, 0.0F),
				Vector3f(0.0F, 0.0F, 0.0F), Vector2f(0.0F, 0.0F)),
			Vertex(Vector3f(-1.0F,  1.0F, 0.0F), Vector3f(0.0F, 0.0F, 0.0F),
				Vector3f(0.0F, 0.0F, 0.0F), Vector2f(0.0F, 1.0F)),
			Vertex(Vector3f( 1.0F,  1.0F, 0.0F), Vector3f(0.0F, 0.0F, 0.0F),
				Vector3f(0.0F, 0.0F, 0.0F), Vector2f(1.0F, 1.0F)),
			Vertex(Vector3f( 1.0F, -1.0F, 0.0F), Vector3f(0.0F, 0.0F, 0.0F),
				Vector3f(0.0F, 0.0F, 0.0F), Vector2f(1.0F, 0.0F))
		};

		// The indices of the two triangles of the Quad
		int indices[6] = { 0, 3, 2, 2, 1, 0 };

		// Build the Quad Mesh & initialize so that it may be drawn
		this->quad.initialize();
		this->quad.setVertexData(quadVerts, 4);
		this->quad.setIndexData(indices, 6);
	}

	void DeferredRenderer::renderBackground() {
		// Skip Rendering if this is a Depth Map or a Shadow Map.
		if (this->final == FinalTexture::DEPTH ||
			this->final == FinalTexture::CLASSIC_SHADOW_MAP ||
			this->final == FinalTexture::VARIANCE_SHADOW_MAP) return;

		// Skybox will be drawn to the final image
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + this->final);
		
		// Do NOT write to the depth buffer, but do enable a depth test and
		// render the skybox if the depth buffer value is less than or equal to
		// 1.0F (skybox depth is at 1.0F, so it must be less than or equal).
		glDepthMask(GL_FALSE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);

		switch (this->backgroundMode) {
		case BackgroundMode::SKYBOX:
			this->skyboxShader.bindShaderProgram();
			CameraController::getActiveCamera()->toShader(
				this->skyboxShader, "camera");
			this->skyboxShader.setUniform_i("cube", 0);
			this->skybox.bind(0);

			this->cubemapMesh.draw(this->skyboxShader);
			break;
		case BackgroundMode::SOLID_COLOR:
			this->solidColorShader.bindShaderProgram();
			CameraController::getActiveCamera()->toShader(
				this->solidColorShader, "camera");
			this->solidColorShader.setUniform_vec4(
				"solidColor", this->solidColor);

			this->cubemapMesh.draw(this->solidColorShader);
			break;
		}

		// Undo the changes to OpenGL rendering
		glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
	}

	void DeferredRenderer::renderLightAmbient(const AmbientLight &aL) {
		glDisable(GL_STENCIL_TEST);
		this->renderLightQuad(aL, this->ambientShader, "ambientLight");
		glEnable(GL_STENCIL_TEST);
	}

	void DeferredRenderer::renderLightDirectional(const DirectionalLight &dL,
			GameScene &scene) {
		this->renderDirectionalShadowMap(dL, scene);
		
		// Do not render the light itself if we are only looking for a shadow
		// map
		if (this->final != FinalTexture::CLASSIC_SHADOW_MAP &&
			this->final != FinalTexture::VARIANCE_SHADOW_MAP) {
			glDisable(GL_STENCIL_TEST);

			this->directionalLightShader.setUniform_i("shadowMap", 
				DeferredRenderer::SHADOW_MAP_INDEX);
			
			// Bind the shadow map texture at the shadow map index for the
			// light shaders
			auto shadowType = dL.getShadow().getShadowType();
			if (Shadow::isClassicShadow(shadowType)) {
				this->cShadowMapTexture.bind(SHADOW_MAP_INDEX);
			} else if (Shadow::isVarianceShadow(shadowType)) {
				this->vShadowMapTexture.bind(SHADOW_MAP_INDEX);
			}

			this->renderLightQuad(dL, this->directionalLightShader,
				"directionalLight");
			glEnable(GL_STENCIL_TEST);
		}
	}

	void DeferredRenderer::renderLightPoint(const PointLight &pL) {
		this->writePointLightTransform(pL);
		
		glEnable(GL_STENCIL_TEST);
		this->stencilLightVolume(this->lightVolumePoint);
		this->renderLightVolume(pL, this->lightVolumePoint,
			this->pointLightShader, "pointLight");
		glDisable(GL_STENCIL_TEST);
	}

	void DeferredRenderer::renderLightSpot(const SpotLight &sL) {
		this->writeSpotLightTransform(sL);
		
		glEnable(GL_STENCIL_TEST);
		this->stencilLightVolume(this->lightVolumeSpot);
		this->renderLightVolume(sL, this->lightVolumeSpot,
			this->spotLightShader, "spotLight");
		glDisable(GL_STENCIL_TEST);
	}

	void DeferredRenderer::renderLightQuad(const BaseLight &bL,
			ShaderProgram &shader, const std::string &name) {
		CameraController::getActiveCamera()->toShader(shader, "camera");
		bL.toShader(shader, name);

		glDisable(GL_DEPTH_TEST); // Light does not need Depth Testing
		glEnable(GL_BLEND); // Each light's contribution is blended together
		glBlendEquation(GL_FUNC_ADD); // Lights are added together with an
		glBlendFunc(GL_ONE, GL_ONE);  // equal contribution from each source
		glEnable(GL_CULL_FACE);

		this->gBuffer.bindDrawLight(shader, bL.getType());
		
		quad.draw(shader);

		// Undo the Changes
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	void DeferredRenderer::renderLightVolume(const BaseLight &bL,
			Mesh &volume, ShaderProgram &shader, const std::string &name) {
		// Write the Camera Projection & Light to the Point Light Shader
		CameraController::getActiveCamera()->toShader(shader, "camera");
		bL.toShader(shader, name);

		this->gBuffer.bindDrawLight(shader, bL.getType());

		// Set the Stencil Function to pass when the stencil value != 0
		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

		glDisable(GL_DEPTH_TEST); // Light does not need Depth Testing
		glEnable(GL_BLEND); // Each light's contribution is blended together
		glBlendEquation(GL_FUNC_ADD); // Lights are added together with an
		glBlendFunc(GL_ONE, GL_ONE);  // equal contribution from each source
		glEnable(GL_CULL_FACE); // Enable the culling of
		glCullFace(GL_FRONT);	// front faces.

		// Render the point light sphere with the given shader
		volume.draw(shader);

		// Undo the Changes
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	void DeferredRenderer::renderPassGeometry(GameScene &scene) {
		// Skip if we're only rendering a Shadow Map
		if (this->final == FinalTexture::CLASSIC_SHADOW_MAP ||
			this->final == FinalTexture::VARIANCE_SHADOW_MAP) return;

		// Bind the G Buffer for Drawing Geometry
		this->gBuffer.bindDrawGeometry();

		// Draw the geometry using the mode requested by the user
		glPolygonMode(PolygonFace::FRONT, this->polygonModeFront);
		glPolygonMode(PolygonFace::BACK, this->polygonModeBack);

		// Cull faces as necessary, if the user wants to
		glFrontFace(this->frontFace);
		glCullFace(this->cullingFace);
		this->setBoolSettingGL(GL_CULL_FACE, this->doCullFaces);

		// Enable Depth Testing, if the user wants to.
		this->setBoolSettingGL(GL_DEPTH_TEST, this->doDepthTest);

		glDepthMask(GL_TRUE); // Only Geometry Render writes to the Depth
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Buffer

		// Bind the skybox for Reflection (reason for binding it to 31 is so
		// that the material can take the other GL_TEXTURE fields for itself).
		this->geometryShader.bindShaderProgram();
		this->geometryShader.setUniform_i("skybox", 31);
		this->skybox.bind(31);

		scene.render(this->geometryShader); // Render the Game Scene Meshes

		glDepthMask(GL_FALSE); // Only Geometry Render writes to the Depth
	}

	void DeferredRenderer::renderPassLight(GameScene &scene) {
		// Don't render any lights if we are not using the final render target
		// or we are not rendering a shadow map
		if (this->final != FinalTexture::FINAL &&
			this->final != FinalTexture::CLASSIC_SHADOW_MAP &&
			this->final != FinalTexture::VARIANCE_SHADOW_MAP) return;

		// Since the polygon mode only applies to geometry, change to FILL
		// mode when drawing lights.
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		for (BaseLight *bL : scene.getActiveLights()) {
			switch (bL->getType()) {
			case LightType::LIGHT_TYPE_AMBIENT:
				this->renderLightAmbient(*(bL->downcast<AmbientLight>()));
				break;
			case LightType::LIGHT_TYPE_DIRECTIONAL:
				this->renderLightDirectional(*(
					bL->downcast<DirectionalLight>()), scene);
				break;
			case LightType::LIGHT_TYPE_POINT:
//				this->renderLightPoint(*(bL->downcast<PointLight>()));
				break;
			case LightType::LIGHT_TYPE_SPOT:
//				this->renderLightSpot(*(bL->downcast<SpotLight>()));
				break;
			}
		}

		// Once all lights are rendered, we do not need to worry about any
		// stencil tests.
		glDisable(GL_STENCIL_TEST);
	}

	Texture2D DeferredRenderer::renderPassPostProcess() {
		// Bind the FINAL_2 buffer so that we may write the rendered (geometry
		// and light) image into it.
		this->gBuffer.bind();
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + GBufferTextureType::FINAL_2);

		// Depth test must be disabled, since we just want to render a texture
		// to FINAL_2.
		glDisable(GL_DEPTH_TEST);

		// Bind the texture to the quad shader
		this->quadShader.setUniform_i("fsTexture", 0);
		if (this->final <= FinalTexture::FINAL) {
			this->gBuffer.bufferTextures[this->final].bind(0);
		} else if (this->final == FinalTexture::CLASSIC_SHADOW_MAP) {
			this->cShadowMapTexture.bind(0);
		} else if (this->final == FinalTexture::VARIANCE_SHADOW_MAP) {
			this->vShadowMapTexture.bind(0);
		}

		// Render the texture using the quad shader into the FINAL_2 buffer
		this->quad.draw(this->quadShader);

		// Now the FINAL_2 buffer contains the geometry + light rendered data.
		// When post processing, we will read from the read buffer and write to
		// the write buffer, then swap the buffers for each shader (since we
		// cannot read to and write from the same buffer).
		int read = GBufferTextureType::FINAL_2;
		int write = GBufferTextureType::FINAL_1;

		// Post Process the image with all of the user's custom post process
		// shaders.
		if (this->doPostProcess) {
			for (ShaderProgram &s : this->getPostShaders()) {
				this->renderPostProcessShader(s, read, write);
			}
		}

		// FXAA post process
		if (this->antiAliasing == AntiAliasing::FXAA) {
			CameraController::getActiveCamera()->toShader(this->fxaaShader,
				"camera");
			this->renderPostProcessShader(this->fxaaShader, read, write);
		}

		// Gamma post process
		if (this->colorSpace == ColorSpace::GAMMA_POST) {
			this->renderPostProcessShader(this->gammaShader, read, write);
		}

		// Now return the texture containing the last texture we wrote into
		// (which is now the read texture). This contains the final post
		// processed image.
		return this->gBuffer.bufferTextures[read];
	}

	void DeferredRenderer::renderPostProcessShader(ShaderProgram &shader,
			int &read, int &write) {
		// Set the draw buffer to write and render image using this
		// post processing shader
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + write);
		this->gBuffer.bindTexture((GBufferTextureType)read, shader, 
				"gBufferFinal");
		quad.draw(shader);

		// Now read and write the other way (swap read and write)
		int tmp = read;
		read = write;
		write = tmp;
	}

	void DeferredRenderer::renderDirectionalShadowMap(
			const DirectionalLight &dL, GameScene &scene) {
		// Do not bother rendering the shadow map if the light is not going to
		// use it!
		if (dL.getShadow().getShadowType() == ShadowType::SHADOW_NONE) return;

		// Bind the Shadow Map Buffer
		glDepthMask(GL_TRUE);
		this->gBuffer.unbind();
		auto shadowType = dL.getShadow().getShadowType();
		if (Shadow::isClassicShadow(shadowType)) {
			glBindFramebuffer(GL_FRAMEBUFFER, this->cShadowMapBuffer);
			glClear(GL_DEPTH_BUFFER_BIT);
		} else if (Shadow::isVarianceShadow(shadowType)) {
			glBindFramebuffer(GL_FRAMEBUFFER, this->vShadowMapBuffer);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		// Enable Culling of Back Faces
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
		// Set the window render viewport size to the Shadow Map Size
		glViewport(0, 0, this->SHADOW_MAP_WIDTH, this->SHADOW_MAP_HEIGHT);

		// Fetch the Light Projection matrix and write it to the light shaders,
		// and render the scene from the perspective of the camera using the
		// shadow shader.
		Matrix4f lP = dL.getShadow().getProjection();
		if (Shadow::isClassicShadow(shadowType)) {
			this->cShadowMapShader.setUniform_mat4("lightProjection", lP);
			scene.render(this->cShadowMapShader);
		} else if (Shadow::isVarianceShadow(shadowType)) {
			this->vShadowMapShader.setUniform_mat4("lightProjection", lP);
			scene.render(this->vShadowMapShader);
		}

		// Set the window render viewport size back to the Window Size
		glViewport(0, 0,
			GameWindow::getGameWindow()->getWindowWidth(),
			GameWindow::getGameWindow()->getWindowHeight());

		// Undo Culling & Depth Mask Changes
		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);

		// Rebind the GBuffer
		this->gBuffer.bind();
	}

	void DeferredRenderer::renderTexture(const Texture2D &tex) {
		this->gBuffer.unbind();
		glDisable(GL_DEPTH_TEST);

		tex.bind(0);
		this->quadShader.setUniform_i("fsTexture", 0);
		quad.draw(this->quadShader);

		glEnable(GL_DEPTH_TEST);
	}

	void DeferredRenderer::setGamma(const float &g) {
		Renderer::setGamma(g);

		this->geometryShader.setUniform_f("gamma", g);
		this->skyboxShader.setUniform_f("gamma", g);
	}

	void DeferredRenderer::stencilLightVolume(Mesh &volume) {
		CameraController::getActiveCamera()->toShader(this->stencilShader,
			"camera");
		this->gBuffer.bindStencil(); // Bind buffer for Stencil information

		glEnable(GL_DEPTH_TEST); // Enable depth testing for stencil
		glDisable(GL_CULL_FACE); // For processing ALL (front & back) faces
		glClear(GL_STENCIL_BUFFER_BIT); // Clear Stencil for this pass

		// Set the Stencil Test to always successeed, since only the depth is
		// to be tested.
		glStencilFunc(GL_ALWAYS, 0, 0);

		// Configure stencil operation for back facing polygons to increment
		// the value in the stencil buffer only when the depth test fails. For
		// front facing polygons, decrement the value in the stencil buffer
		// only when the depth test fails.
		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

		// Render the Cone with the basic stencil shader
		volume.draw(this->stencilShader);

		// Clean up
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		this->gBuffer.bindDraw();
	}

	void DeferredRenderer::writePointLightTransform(const PointLight &pL) {
		Transform pLT = *(pL.getAttached()->getComponent<Transform>());
		Matrix4f transformM = pLT.getTransformationMatrix();
		float pLRange = pL.getRange();

		this->pointLightShader.setUniform_mat4("objTransform", transformM);
		this->pointLightShader.setUniform_f("lvRange", pLRange);

		this->stencilShader.setUniform_mat4("objTransform", transformM);
		this->stencilShader.setUniform_f("lvRange", pLRange);
	}

	void DeferredRenderer::writeSpotLightTransform(const SpotLight &sL) {
		Transform sLT = *(sL.getAttached()->getComponent<Transform>());
		Matrix4f transformM = sLT.getTransformationMatrix();
		float sLRange = sL.getRange();

		this->spotLightShader.setUniform_mat4("objTransform", transformM);
		this->spotLightShader.setUniform_f("lvRange", sLRange);

		this->stencilShader.setUniform_mat4("objTransform", transformM);
		this->stencilShader.setUniform_f("lvRange", sLRange);
	}
} } }
