#include "..\..\include\core\RenderEngine.h"

using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;

// TODO: temp
#include "..\..\include\component\render\CameraController.h"
using Honeycomb::Component::Render::CameraController;

namespace Honeycomb::Core {
	RenderEngine* RenderEngine::renderEngine = nullptr;

	RenderEngine* RenderEngine::getRenderEngine() {
		if (renderEngine == nullptr)
			renderEngine = new RenderEngine();

		return renderEngine;
	}

	void RenderEngine::render(ShaderProgram &shader) {
		if (GameScene::getActiveScene() != nullptr)
			this->render(*GameScene::getActiveScene(), shader);
	}

	void RenderEngine::render(GameScene &scene, ShaderProgram &shader) {
		// todo: temp
		shader.setUniform_mat4("uvs_Projection", 
			CameraController::getActiveCamera()->getProjection());

		scene.render(shader);
	}

	RenderEngine::RenderEngine() {
		setOpenGLSettings();
	}

	RenderEngine::~RenderEngine() {

	}
	
	void RenderEngine::setOpenGLSettings() {
		glClearColor(
			this->clearScreenColor.getX(), this->clearScreenColor.getY(),
			this->clearScreenColor.getZ(), this->clearScreenColor.getW());

		/// TODO: Implement all of these as settings in the rendering engine...

		if (true) { // Should back faces be drawn? TODO
			glCullFace(GL_BACK); // Do not draw the back face (CW)
			glEnable(GL_CULL_FACE); // Disable rendering unseen back faces
		}
		glEnable(GL_MULTISAMPLE); // Enable MSAA
		glEnable(GL_TEXTURE_2D); // Enable 2D texturing
		glShadeModel(GL_SMOOTH); // Smooth Shading
		glEnable(GL_DEPTH_TEST); // Enable depth perception for drawing order
//		glEnable(GL_BLEND); // Enable blending for transparency
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Blend Function
	}
}