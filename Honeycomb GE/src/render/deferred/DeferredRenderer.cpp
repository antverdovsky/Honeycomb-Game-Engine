#include "..\..\..\include\render\deferred\DeferredRenderer.h"

#include <GL/glew.h>

#include "..\..\..\include\component\light\AmbientLight.h"
#include "..\..\..\include\component\light\BaseLight.h"
#include "..\..\..\include\component\light\DirectionalLight.h"
#include "..\..\..\include\component\light\PointLight.h"
#include "..\..\..\include\component\light\SpotLight.h"
#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\component\render\CameraController.h"
#include "..\..\..\include\component\render\MeshRenderer.h"

#include "..\..\..\include\geometry\Vertex.h"
#include "..\..\..\include\object\Builder.h"

using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Component::Light::AmbientLight;
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Light::PointLight;
using Honeycomb::Component::Light::SpotLight;
using Honeycomb::Component::Light::LightType;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::CameraController;
using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Geometry::Vertex;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector2f;
using Honeycomb::Object::Builder;
using Honeycomb::Object::GameObject;
using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Render::Deferred {
	DeferredRenderer* DeferredRenderer::deferredRenderer = nullptr;

	const std::string DeferredRenderer::POINT_LIGHT_VOLUME_MODEL =
		"..\\Honeycomb GE\\res\\models\\light-volumes\\pointLight.fbx";
	const std::string DeferredRenderer::SPOT_LIGHT_VOLUME_MODEL =
		"..\\Honeycomb GE\\res\\models\\light-volumes\\spotLight.fbx";

	DeferredRenderer* DeferredRenderer::getDeferredRenderer() {
		if (DeferredRenderer::deferredRenderer == nullptr)
			DeferredRenderer::deferredRenderer = new DeferredRenderer();

		return DeferredRenderer::deferredRenderer;
	}

	DeferredRenderer::DeferredRenderer() : Renderer() {
		this->gBuffer.initialize();

		this->initializeLightVolumes();
		this->initializeQuad();
		this->initializeShaders();
	}

	DeferredRenderer::~DeferredRenderer() {
		delete this->lightVolumePoint;
		delete this->lightVolumeSpot;
	}

	void DeferredRenderer::initializeLightVolumes() {
		// Get the models containing the Light Volumes
		GameObject *pLModel = Builder::getBuilder()->newModel(
			POINT_LIGHT_VOLUME_MODEL);
		GameObject *sLModel = Builder::getBuilder()->newModel(
			SPOT_LIGHT_VOLUME_MODEL);

		// Extract the actual light volumes from the Model
		this->lightVolumePoint = pLModel->getChild("Icosphere")->clone();
		this->lightVolumeSpot = sLModel->getChild("Cube")->clone();

		// Delete the Light Volume Models
		delete pLModel;
		delete sLModel;

		// Set a null material for the Light Volume Game Objects
		this->lightVolumePoint->getComponent<MeshRenderer>()->setMaterial(
			nullptr);
		this->lightVolumeSpot->getComponent<MeshRenderer>()->setMaterial(
			nullptr);

		// Start the Light Volume Game Objects so that they may be rendered
		this->lightVolumePoint->start();
		this->lightVolumeSpot->start();
	}

	void DeferredRenderer::initializeShaders() {
		this->ambientShader.initialize();
		this->ambientShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\pass\\simpleVS.glsl", GL_VERTEX_SHADER);
		this->ambientShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\light\\ambientLightFS.glsl",
			GL_FRAGMENT_SHADER);
		this->ambientShader.finalizeShaderProgram();

		this->directionalLightShader.initialize();
		this->directionalLightShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\pass\\simpleVS.glsl", GL_VERTEX_SHADER);
		this->directionalLightShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\light\\directionalLightFS.glsl",
			GL_FRAGMENT_SHADER);
		this->directionalLightShader.finalizeShaderProgram();

		this->pointLightShader.initialize();
		this->pointLightShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\light\\lightVS.glsl", GL_VERTEX_SHADER);
		this->pointLightShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\light\\pointLightFS.glsl", GL_FRAGMENT_SHADER);
		this->pointLightShader.finalizeShaderProgram();

		this->spotLightShader.initialize();
		this->spotLightShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\light\\lightVS.glsl", GL_VERTEX_SHADER);
		this->spotLightShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\light\\spotLightFS.glsl", GL_FRAGMENT_SHADER);
		this->spotLightShader.finalizeShaderProgram();

		this->geometryShader.initialize();
		this->geometryShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\geometryVS.glsl", GL_VERTEX_SHADER);
		this->geometryShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\geometryFS.glsl", GL_FRAGMENT_SHADER);
		this->geometryShader.finalizeShaderProgram();

		this->stencilShader.initialize();
		this->stencilShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\stencilVS.glsl", GL_VERTEX_SHADER);
		this->stencilShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\stencilFS.glsl", GL_FRAGMENT_SHADER);
		this->stencilShader.finalizeShaderProgram();

		this->quadShader.initialize();
		this->quadShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\simpleVS.glsl", GL_VERTEX_SHADER);
		this->quadShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\simpleFS.glsl", GL_FRAGMENT_SHADER);
		this->quadShader.finalizeShaderProgram();
	}

	void DeferredRenderer::initializeQuad() {
		// The vertices for a full screen Quad
		Vertex quadVerts[4] = {
			Vertex(Vector3f(0.0F, 0.0F, 0.0F), Vector3f(-1.0F, -1.0F, 0.0F), 
				Vector2f(0.0F, 0.0F)),
			Vertex(Vector3f(0.0F, 0.0F, 0.0F), Vector3f(-1.0F,  1.0F, 0.0F), 
				Vector2f(0.0F, 1.0F)),
			Vertex(Vector3f(0.0F, 0.0F, 0.0F), Vector3f(1.0F,  1.0F, 0.0F), 
				Vector2f(1.0F, 1.0F)),
			Vertex(Vector3f(0.0F, 0.0F, 0.0F), Vector3f(1.0F, -1.0F, 0.0F), 
				Vector2f(1.0F, 0.0F))
		};

		// The indices of the two triangles of the Quad
		int indices[6] = { 0, 3, 2, 2, 1, 0 };

		// Build the Quad Mesh & initialize so that it may be drawn
		this->quad.initialize();
		this->quad.setVertexData(quadVerts, 4);
		this->quad.setIndexData(indices, 6);
	}

	void DeferredRenderer::renderFinal() {
		this->gBuffer.unbind();
		this->gBuffer.bindTexture(GBufferTextureType::FINAL);

		quad.draw(this->quadShader);
	}

	void DeferredRenderer::render(Honeycomb::Scene::GameScene &scene) {
		CameraController::getActiveCamera()->toShader(this->geometryShader,
			"camera");
		
		this->gBuffer.frameBegin(); // Clear rendered texture from last frame 

		this->renderGeometryPass(scene); // Render Geometry
		this->renderLightsPass(scene); // Render Lights

		this->renderFinal();
	}

	void DeferredRenderer::renderGeometryPass(GameScene &scene) {
		// Bind the G Buffer for Drawing Geometry
		this->gBuffer.bindDrawGeometry();

		glDepthMask(GL_TRUE); // Only Geometry Render writes to the Depth
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Buffer
		glEnable(GL_DEPTH_TEST); // Enable the Depth Test for Geometry Render
		
		scene.render(this->geometryShader); // Render the Game Scene Meshes

		glDepthMask(GL_FALSE); // Only Geometry Render writes to the Depth
	}

	void DeferredRenderer::renderLightsPass(GameScene &scene) {
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
		glEnable(GL_STENCIL_TEST);

		this->transformLightPointVolume(pL);
		this->stencilLightVolume(*(this->lightVolumePoint));
		this->renderLightVolume(pL, *(this->lightVolumePoint), 
			this->pointLightShader, "pointLight");
	}

	void DeferredRenderer::renderLightSpot(const SpotLight &sL) {
		glEnable(GL_STENCIL_TEST); // Enable Stencil Testing for S.L.s

		this->transformLightSpotVolume(sL);
		this->stencilLightVolume(*(this->lightVolumeSpot));
		this->renderLightVolume(sL, *(this->lightVolumeSpot),
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
			GameObject &obj, ShaderProgram &shader, const std::string &name) {
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
		obj.render(shader);

		// Enable the culling of the back facing faces
		glCullFace(GL_BACK);
		glDisable(GL_BLEND);
	}

	void DeferredRenderer::stencilLightVolume(GameObject &volume) {
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
		volume.render(this->stencilShader);
	}

	void DeferredRenderer::transformLightPointVolume(const PointLight &pL) {
		// Transform the Light Volume Sphere by scaling and translating it
		this->lightVolumePoint->getComponent<Transform>()->setScale(Vector3f(
			pL.getRange(), pL.getRange(), pL.getRange()));
		this->lightVolumePoint->getComponent<Transform>()->setTranslation(
			pL.glVector3fs.getValue(PointLight::POSITION_VEC3));
	}

	void DeferredRenderer::transformLightSpotVolume(const SpotLight &sL) {
		// Transform the Light Volume Sphere by scaling and translating it
		this->lightVolumeSpot->getComponent<Transform>()->setScale(Vector3f(
			sL.getRange(), sL.getRange(), sL.getRange()));
		this->lightVolumeSpot->getComponent<Transform>()->setTranslation(
			sL.glVector3fs.getValue(SpotLight::POSITION_VEC3));
		this->lightVolumeSpot->getComponent<Transform>()->setRotation(
			sL.getAttached()->getComponent<Transform>()->getLocalRotation());		    // TODO make so it uses sL.direction
		this->lightVolumeSpot->getComponent<Transform>()->rotate(					// todo temporary
			this->lightVolumeSpot->getComponent<Transform>()->getLocalRight(),
			3.1415926159F
		);
	}
}