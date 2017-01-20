#include "..\..\..\include\render\deferred\DeferredRenderer.h"

#include <GL/glew.h>

#include "..\..\..\include\component\render\CameraController.h"

#include "..\..\..\include\base\GameWindow.h"
using Honeycomb::Base::GameWindow;
#include "..\..\..\include\geometry\Vertex.h"
using Honeycomb::Geometry::Vertex;
#include "..\..\..\include\math\Vector4f.h"
using Honeycomb::Math::Vector4f;
#include "..\..\..\include\math\Vector3f.h"
using Honeycomb::Math::Vector3f;
#include "..\..\..\include\math\Vector2f.h"
using Honeycomb::Math::Vector2f;
#include "..\..\..\include\component\light\BaseLight.h"
using Honeycomb::Component::Light::BaseLight;
#include "..\..\..\include\component\light\AmbientLight.h"
using Honeycomb::Component::Light::AmbientLight;
#include "..\..\..\include\component\light\DirectionalLight.h"
using Honeycomb::Component::Light::DirectionalLight;
#include "..\..\..\include\component\light\PointLight.h"
using Honeycomb::Component::Light::PointLight;
#include "..\..\..\include\object\Builder.h"
using Honeycomb::Object::Builder;
#include "..\..\..\include\component\render\MeshRenderer.h"
using Honeycomb::Component::Render::MeshRenderer;
#include "..\..\..\include\component\physics\Transform.h"
using Honeycomb::Component::Physics::Transform;
#include "..\..\..\include\graphics\Material.h"
using Honeycomb::Graphics::Material;
#include "..\..\..\include\graphics\Texture2D.h"
using Honeycomb::Graphics::Texture2D;

using Honeycomb::Scene::GameScene;
using Honeycomb::Component::Render::CameraController;

namespace Honeycomb::Render::Deferred {
	DeferredRenderer* DeferredRenderer::deferredRenderer = nullptr;

	DeferredRenderer* DeferredRenderer::getDeferredRenderer() {
		if (DeferredRenderer::deferredRenderer == nullptr)
			DeferredRenderer::deferredRenderer = new DeferredRenderer();

		return DeferredRenderer::deferredRenderer;
	}

	DeferredRenderer::DeferredRenderer() : Renderer() {
		this->gBuffer.initialize();

		this->pointLightSphere = Builder::getBuilder()->newSphere();
		this->directionalLightPlane = Builder::getBuilder()->newPlane();
		// TEMPORARY
		/*
		Texture2D *blank = new Texture2D();
		blank->initialize();
		blank->setImageData();
		Material *mat = new Material();
		mat->glVector4fs.setValue("ambientColor",
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
		mat->glVector4fs.setValue("diffuseColor",
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
		mat->glVector4fs.setValue("specularColor",
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
		mat->glFloats.setValue("shininess", 1.0F * 128.0F);
		mat->glSampler2Ds.setValue("albedoTexture", *blank);
		this->pointLightSphere->getComponent<MeshRenderer>()->setMaterial(*mat);
		*/
		this->pointLightSphere->getComponent<MeshRenderer>()->setMaterial(nullptr);
		this->pointLightSphere->start();

		this->geometryShader.initialize();
		this->geometryShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\geometryVS.glsl", GL_VERTEX_SHADER);
		this->geometryShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\geometryFS.glsl", GL_FRAGMENT_SHADER);
		this->geometryShader.finalizeShaderProgram();

		this->quadShader.initialize();
		this->quadShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\simpleVS.glsl", GL_VERTEX_SHADER);
		this->quadShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\simpleFS.glsl", GL_FRAGMENT_SHADER);
		this->quadShader.finalizeShaderProgram();

		this->ambientShader.initialize();
		this->ambientShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\pass\\simpleVS.glsl", GL_VERTEX_SHADER);
		this->ambientShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\light\\ambientLightFS.glsl", 
			GL_FRAGMENT_SHADER);
		this->ambientShader.finalizeShaderProgram();

		this->pointLightShader.initialize();
		this->pointLightShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\light\\lightVS.glsl", GL_VERTEX_SHADER);
		this->pointLightShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\light\\pointLightFS.glsl", GL_FRAGMENT_SHADER);
		this->pointLightShader.finalizeShaderProgram();

		this->directionalLightShader.initialize();
		this->directionalLightShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\pass\\simpleVS.glsl", GL_VERTEX_SHADER);
		this->directionalLightShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\render\\deferred\\light\\directionalLightFS.glsl", 
			GL_FRAGMENT_SHADER);
		this->directionalLightShader.finalizeShaderProgram();

		this->stencilShader.initialize();
		this->stencilShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\stencilVS.glsl", GL_VERTEX_SHADER);
		this->stencilShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pass\\stencilFS.glsl", GL_FRAGMENT_SHADER);
		this->stencilShader.finalizeShaderProgram();

		Vertex quadVerts[4] = {
			Vertex(Vector3f(0.0F, 0.0F, 0.0F), Vector3f(-1.0F, -1.0F, 0.0F), Vector2f(0.0F, 0.0F)),
			Vertex(Vector3f(0.0F, 0.0F, 0.0F), Vector3f(-1.0F,  1.0F, 0.0F), Vector2f(0.0F, 1.0F)),
			Vertex(Vector3f(0.0F, 0.0F, 0.0F), Vector3f( 1.0F,  1.0F, 0.0F), Vector2f(1.0F, 1.0F)),
			Vertex(Vector3f(0.0F, 0.0F, 0.0F), Vector3f( 1.0F, -1.0F, 0.0F), Vector2f(1.0F, 0.0F))
		};

		int indices[6] = {
			0, 3, 2, 2, 1, 0
		};

		quad.initialize();
		quad.setVertexData(quadVerts, 4);
		quad.setIndexData(indices, 6);
	}

	DeferredRenderer::~DeferredRenderer() {

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
			if (bL->getName() == "PointLight") { // TODO temporary
				glEnable(GL_STENCIL_TEST); // Enable Stencil Testing for P.L.s
				
				this->transformLightPointVolume(
					*bL->getAttached()->getComponent<PointLight>());

				this->stencilLightPoint(
					*bL->getAttached()->getComponent<PointLight>());
				this->renderLightPoint(
					*bL->getAttached()->getComponent<PointLight>());
			} else if (bL->getName() == "DirectionalLight") {
				glDisable(GL_STENCIL_TEST); // Disable Stencil Testing

				this->renderLightDirectional(
					*bL->getAttached()->getComponent<DirectionalLight>());
			} else if (bL->getName() == "AmbientLight") {
				glDisable(GL_STENCIL_TEST);

				this->renderLightAmbient(
					*bL->getAttached()->getComponent<AmbientLight>());
			}
		}
	}

	void DeferredRenderer::renderLightAmbient(const AmbientLight &aL) {
		// Write the Camera Projection & Light to the Point Light Shader
		CameraController::getActiveCamera()->toShader(
			this->ambientShader, "camera");
		aL.toShader(this->ambientShader, "ambientLight");

		glDisable(GL_DEPTH_TEST); // Light does not need Depth Testing
		glEnable(GL_BLEND); // Each light's contribution is blended together
		glBlendEquation(GL_FUNC_ADD); // Lights are added together with an
		glBlendFunc(GL_ONE, GL_ONE);  // equal contribution from each source

		glEnable(GL_CULL_FACE);

		glDrawBuffer(GL_COLOR_ATTACHMENT0 + GBufferTextureType::FINAL);
		this->gBuffer.bindTexture(GBufferTextureType::DIFFUSE, 
			this->ambientShader);

		//this->directionalLightPlane->render(this->directionalLightShader);
		quad.draw(this->ambientShader);

		glDisable(GL_BLEND);
	}

	void DeferredRenderer::renderLightDirectional(const DirectionalLight &dL) {
		// Write the Camera Projection & Light to the Point Light Shader
		CameraController::getActiveCamera()->toShader(
			this->directionalLightShader, "camera");
		dL.toShader(this->directionalLightShader, "directionalLight");

		glDisable(GL_DEPTH_TEST); // Light does not need Depth Testing
		glEnable(GL_BLEND); // Each light's contribution is blended together
		glBlendEquation(GL_FUNC_ADD); // Lights are added together with an
		glBlendFunc(GL_ONE, GL_ONE);  // equal contribution from each source

		glEnable(GL_CULL_FACE);

		this->gBuffer.bindDrawLight(this->directionalLightShader);

		//this->directionalLightPlane->render(this->directionalLightShader);
		quad.draw(this->directionalLightShader);

		glDisable(GL_BLEND);
	}

	void DeferredRenderer::renderLightPoint(const PointLight &pL) {
		// Write the Camera Projection & Light to the Point Light Shader
		CameraController::getActiveCamera()->toShader(this->pointLightShader,
			"camera");
		pL.toShader(this->pointLightShader, "pointLight");

		this->gBuffer.bindDrawLight(this->pointLightShader);

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
		this->pointLightSphere->render(this->pointLightShader);

		// Enable the culling of the back facing faces
		glCullFace(GL_BACK);
		glDisable(GL_BLEND);
	}

	void DeferredRenderer::stencilLightPoint(const PointLight &pL) {
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

		// Render the Sphere with the basic stencil shader
		this->pointLightSphere->render(this->stencilShader);
	}

	void DeferredRenderer::transformLightPointVolume(PointLight &pL) {
		// Retrieve the RGBA color of the Point Light and get the maximum
		// RGB component of the color.
		Vector4f rgba = pL.glVector4fs.getValue(PointLight::COLOR_VEC4);
		float kM = fmaxf(rgba.getX(), fmaxf(rgba.getY(), rgba.getZ()));

		// Constant representing the inverse of the brightness at the radius of
		// the sphere.
		float kK = 256.0F / 5.0F;

		// Retrieve all of the attenuation constants
		float kC = pL.glFloats.getValue(PointLight::ATTENUATION_CONSTANT_F);
		float kL = pL.glFloats.getValue(PointLight::ATTENUATION_LINEAR_F);
		float kQ = pL.glFloats.getValue(PointLight::ATTENUATION_QUADRATIC_F);

		// Get the radius (or scale) of the point light sphere
		float scl = (-kL + sqrt(kL * kL - 4 * kQ * (kC - kK * kM))) / (2 * kQ);
		
		// Transform the Light Volume Sphere by scaling and translating it
		this->pointLightSphere->getComponent<Transform>()->setScale(Vector3f(
			scl, scl, scl));
		this->pointLightSphere->getComponent<Transform>()->setTranslation(
			pL.glVector3fs.getValue(PointLight::POSITION_VEC3));

		pL.glFloats.setValue(PointLight::RANGE_F, scl);
	}
}