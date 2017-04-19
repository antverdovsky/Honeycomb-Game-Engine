#include "../../../include/render/deferred/DeferredRenderer.h"

#include <GL/glew.h>

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

using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Light::PointLight;
using Honeycomb::Component::Light::SpotLight;
using Honeycomb::Component::Light::LightType;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::CameraController;
using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Geometry::Mesh;
using Honeycomb::Geometry::Vertex;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector2f;
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

	DeferredRenderer* DeferredRenderer::getDeferredRenderer() {
		if (DeferredRenderer::deferredRenderer == nullptr)
			DeferredRenderer::deferredRenderer = new DeferredRenderer();

		return DeferredRenderer::deferredRenderer;
	}

	void DeferredRenderer::render(Honeycomb::Scene::GameScene &scene) {
		GBufferTextureType target; // Target containing the final image

		CameraController::getActiveCamera()->toShader(this->geometryShader,
			"camera");
		this->gBuffer.frameBegin(); 

		this->renderPassGeometry(scene);	// Render Geometry
		this->renderPassLight(scene);		// Render Lights
		this->renderBackground();			// Render Background Cubebox
		
		target = this->renderPostProcess(); // Post Process the Final Image
		this->renderTexture(target);		// Render the final image
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
		this->ambientShader.addShader("../Honeycomb GE/res/shaders"
			"/render/deferred/pass/simpleVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->ambientShader.addShader("../Honeycomb GE/res/shaders"
			"/render/deferred/light/ambientLightFS.glsl",
			ShaderType::FRAGMENT_SHADER);
		this->ambientShader.finalizeShaderProgram();

		this->directionalLightShader.initialize();
		this->directionalLightShader.addShader("../Honeycomb GE/res/shaders"
			"/render/deferred/pass/simpleVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->directionalLightShader.addShader("../Honeycomb GE/res/shaders"
			"/render/deferred/light/directionalLightFS.glsl",
			ShaderType::FRAGMENT_SHADER);
		this->directionalLightShader.finalizeShaderProgram();

		this->pointLightShader.initialize();
		this->pointLightShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/light/lightVS.glsl",
			ShaderType::VERTEX_SHADER);
		this->pointLightShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/light/pointLightFS.glsl", 
			ShaderType::FRAGMENT_SHADER);
		this->pointLightShader.finalizeShaderProgram();

		this->spotLightShader.initialize();
		this->spotLightShader.addShader("../Honeycomb GE/res/shaders"
			"/render/deferred/light/lightVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->spotLightShader.addShader("../Honeycomb GE/res/shaders"
			"/render/deferred/light/spotLightFS.glsl", 
			ShaderType::FRAGMENT_SHADER);
		this->spotLightShader.finalizeShaderProgram();
		
		this->geometryShader.initialize();
		this->geometryShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/pass/geometryVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->geometryShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/pass/geometryFS.glsl", 
			ShaderType::FRAGMENT_SHADER);
		this->geometryShader.finalizeShaderProgram();

		this->stencilShader.initialize();
		this->stencilShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/pass/stencilVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->stencilShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/pass/stencilFS.glsl", 
			ShaderType::FRAGMENT_SHADER);
		this->stencilShader.finalizeShaderProgram();

		this->quadShader.initialize();
		this->quadShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/pass/simpleVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->quadShader.addShader("../Honeycomb GE/res/shaders/"
			"render/deferred/pass/simpleFS.glsl", 
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

		// Undo the Depth Mask and Depth Test changes
		glDepthMask(GL_TRUE);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}

	void DeferredRenderer::renderFXAA(const GBufferTextureType &r,
			const GBufferTextureType &w) {
		// Bind the buffer to which we will write the FXAA corrected image.
		// Bind the preprocessed image to the FXAA Shader, and write the camera
		// information to the Shader.
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + w);
		this->gBuffer.bindTexture(r, this->fxaaShader, "gBufferFinal");
		CameraController::getActiveCamera()->toShader(this->fxaaShader, 
			"camera");
		quad.draw(this->fxaaShader);
	}

	void DeferredRenderer::renderGamma(const GBufferTextureType &r,
			const GBufferTextureType &w) {
		// Bind the buffer to which we will write the Gamma corrected image.
		// Bind the preprocessed image to the Gamma Shader, and post process.
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + w);
		this->gBuffer.bindTexture(r, this->gammaShader, "gBufferFinal");
		quad.draw(this->gammaShader);
	}

	void DeferredRenderer::renderLightAmbient(const AmbientLight &aL) {
		glDisable(GL_STENCIL_TEST);

		this->renderLightQuad(aL, this->ambientShader, "ambientLight");
	}

	void DeferredRenderer::renderLightDirectional(const DirectionalLight &dL) {
		glDisable(GL_STENCIL_TEST);

		this->renderLightQuad(dL, this->directionalLightShader,
			"directionalLight");
	}

	void DeferredRenderer::renderLightPoint(const PointLight &pL) {
		glEnable(GL_STENCIL_TEST); // Enable Stencil Testing for P.L.s
		
		this->writePointLightTransform(pL);
		this->stencilLightVolume(this->lightVolumePoint);
		this->renderLightVolume(pL, this->lightVolumePoint,
			this->pointLightShader, "pointLight");
	}

	void DeferredRenderer::renderLightSpot(const SpotLight &sL) {
		glEnable(GL_STENCIL_TEST); // Enable Stencil Testing for S.L.s

		this->writeSpotLightTransform(sL);
		this->stencilLightVolume(this->lightVolumeSpot);
		this->renderLightVolume(sL, this->lightVolumeSpot,
			this->spotLightShader, "spotLight");
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

		glDisable(GL_BLEND);
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

		// Enable the culling of the front facing faces 
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		// Render the point light sphere with the given shader
		volume.draw(shader);

		// Enable the culling of the back facing faces
		glCullFace(GL_BACK);
		glDisable(GL_BLEND);
	}

	void DeferredRenderer::renderPassGeometry(GameScene &scene) {
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
		if (this->final != FinalTexture::FINAL) return;

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
					bL->downcast<DirectionalLight>()));
				break;
			case LightType::LIGHT_TYPE_POINT:
				this->renderLightPoint(*(bL->downcast<PointLight>()));
				break;
			case LightType::LIGHT_TYPE_SPOT:
				this->renderLightSpot(*(bL->downcast<SpotLight>()));
				break;
			}
		}
	}

	GBufferTextureType DeferredRenderer::renderPostProcess() {
		// Since we are going to read from one buffer and write to another,
		// establish now which buffer will be read from and which one we will
		// write to.
		GBufferTextureType readBuffer  = (GBufferTextureType)(this->final);
		GBufferTextureType writeBuffer = GBufferTextureType::FINAL_2;

		// Post Process using the user's post process shaders
		if (this->doPostProcess) {
			for (ShaderProgram &s : this->getPostShaders()) {
				// Set the draw buffer to write and render image using this
				// post processing shader
				glDrawBuffer(GL_COLOR_ATTACHMENT0 + writeBuffer);
				this->gBuffer.bindTexture(readBuffer, s, "gBufferFinal");
				quad.draw(s);

				// Now read and write the other way (swap read and write)
				GBufferTextureType tmp = readBuffer;
				readBuffer = writeBuffer;
				writeBuffer = tmp;
			}
		}

		// If Anti Aliasing is enabled, apply the FXAA Post Processing Shader
		if (this->antiAliasing == AntiAliasing::FXAA) {
			this->renderFXAA(readBuffer, writeBuffer);

			// Now read and write the other way (swap read and write buffers)
			GBufferTextureType tmp = readBuffer;
			readBuffer = writeBuffer;
			writeBuffer = tmp;
		}

		// If post processing Gamma correction is enabled, apply the gamma
		// shader.
		if (this->colorSpace == ColorSpace::GAMMA_POST) {
			this->renderGamma(readBuffer, writeBuffer);

			// Now read and write the other way (swap read and write buffers)
			GBufferTextureType tmp = readBuffer;
			readBuffer = writeBuffer;
			writeBuffer = tmp;
		}

		// Image to which we wrote last is the FINAL final (note that since we
		// swapped the buffers, the image to which we wrote last is now the
		// read buffer).
		return readBuffer;
	}

	void DeferredRenderer::renderTexture(const GBufferTextureType &tex) {
		this->gBuffer.unbind();
		this->gBuffer.bindTexture(tex);

		glDisable(GL_DEPTH_TEST);

		quad.draw(this->quadShader);
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
