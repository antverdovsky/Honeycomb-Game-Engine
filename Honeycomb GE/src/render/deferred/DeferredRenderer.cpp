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
		// TEMPORARY
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
		this->pointLightSphere->start();

		this->geometryShader.initialize();
		this->geometryShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\geometryVS.glsl", GL_VERTEX_SHADER);
		this->geometryShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\geometryFS.glsl", GL_FRAGMENT_SHADER);
		this->geometryShader.finalizeShaderProgram();

		this->quadShader.initialize();
		this->quadShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\simpleVS.glsl", GL_VERTEX_SHADER);
		this->quadShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\simpleFS.glsl", GL_FRAGMENT_SHADER);
		this->quadShader.finalizeShaderProgram();

		this->pointLightShader.initialize();
		this->pointLightShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pointLightVS.glsl", GL_VERTEX_SHADER);
		this->pointLightShader.addShader("..\\Honeycomb GE\\res\\shaders\\"
			"render\\deferred\\pointLightFS.glsl", GL_FRAGMENT_SHADER);
		this->pointLightShader.finalizeShaderProgram();

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

	void DeferredRenderer::render(Honeycomb::Scene::GameScene &scene) {
		CameraController::getActiveCamera()->toShader(this->geometryShader,
			"camera");

		this->renderGeometry(scene);
		this->renderLights(scene);
	}

	void DeferredRenderer::renderGeometry(GameScene &scene) {
		// Bind the G Buffer for Drawing
		this->gBuffer.bindDraw();

		glDepthMask(GL_TRUE); // Only Geometry Render writes to the Depth
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Buffer
		glEnable(GL_DEPTH_TEST); // Enable the Depth Test for Geometry Render
		glDisable(GL_BLEND); // Disable blending as only light uses it

		scene.render(this->geometryShader); // Render the Game Scene Meshes
	}

	void DeferredRenderer::renderLights(GameScene &scene) {
		glDepthMask(GL_FALSE); // Light passes will not draw to Depth
		glDisable(GL_DEPTH_TEST); // Light does not need Depth Testing
		glEnable(GL_BLEND); // Each light's contribution is blended together
		glBlendEquation(GL_FUNC_ADD); // Lights are added together with an
		glBlendFunc(GL_ONE, GL_ONE);  // equal contribution from each source

		this->gBuffer.bindRead(); // Bind GBuffer's color attachments
		this->gBuffer.bindTextures(this->pointLightShader); 
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Bind default for draw
		glClear(GL_COLOR_BUFFER_BIT); // Clear the Color Buffer

		for (BaseLight *bL : scene.getActiveLights()) {
			if (bL->getName() == "PointLight") { // TODO temporary
				this->renderLightPoint(
					*bL->getAttached()->getComponent<PointLight>());
			}
		}

//		this->gBuffer.bindTexture(GBufferTextureType::POSITION);
//		quad.draw(this->quadShader);
	}

	void DeferredRenderer::renderLightPoint(const PointLight &pL) {
		// Write the Camera Projection & Light to the Point Light Shader
		CameraController::getActiveCamera()->toShader(this->pointLightShader,
			"camera");
		pL.toShader(this->pointLightShader, "pointLight");

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

		// Get the radius (or scale) of the point light sphere & scale the
		// point light sphere accordingly.
		float scl = (-kL + sqrt(kL * kL - 4 * kQ * (kC - kK * kM))) / (2 * kQ);
//		this->pointLightSphere->getComponent<Transform>()->setScale(Vector3f(
//			scl, scl, scl));
		this->pointLightSphere->getComponent<Transform>()->setScale(Vector3f(
			5.0F, 5.0F, 5.0F));
		this->pointLightSphere->getComponent<Transform>()->setTranslation(
			pL.glVector3fs.getValue(PointLight::POSITION_VEC3));
		this->pointLightSphere->render(this->pointLightShader);
	}
}