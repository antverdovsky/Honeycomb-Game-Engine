#include "..\..\..\include\render\deferred\DeferredRenderer.h"

#include <GL/glew.h>

#include "..\..\..\include\component\render\CameraController.h"

#include "..\..\..\include\base\GameWindow.h"
using Honeycomb::Base::GameWindow;
#include "..\..\..\include\geometry\Vertex.h"
using Honeycomb::Geometry::Vertex;
#include "..\..\..\include\math\Vector3f.h"
using Honeycomb::Math::Vector3f;
#include "..\..\..\include\math\Vector2f.h"
using Honeycomb::Math::Vector2f;


using Honeycomb::Scene::GameScene;
using Honeycomb::Component::Render::CameraController;

namespace Honeycomb::Render::Deferred {
	DeferredRenderer* DeferredRenderer::deferredRenderer = nullptr;

	DeferredRenderer* DeferredRenderer::getDeferredRenderer() {
		if (DeferredRenderer::deferredRenderer == nullptr)
			DeferredRenderer::deferredRenderer = new DeferredRenderer();

		return DeferredRenderer::deferredRenderer;
	}

	void DeferredRenderer::render(Honeycomb::Scene::GameScene &scene) {
		CameraController::getActiveCamera()->toShader(this->geometryShader,
			"camera");

		this->renderGeometry(scene);
		this->renderLights(scene);
	}

	DeferredRenderer::DeferredRenderer() : Renderer() {
		this->gBuffer.initialize();

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

	void DeferredRenderer::renderGeometry(GameScene &scene) {
		// Bind the G Buffer & Clear its color & depth buffers
		this->gBuffer.bindDraw();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render the Game Scene Meshes
		scene.render(this->geometryShader);
	}

	void DeferredRenderer::renderLights(GameScene &scene) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->gBuffer.bindTexture(GBufferTextureType::DIFFUSE);
		quad.draw(this->quadShader);
	}
}