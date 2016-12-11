#include "..\..\include\core\RenderEngine.h"

using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;

// TODO: temp
#include "..\..\include\component\light\DirectionalLight.h"
#include "..\..\include\component\render\CameraController.h"
#include "..\..\include\component\physics\Transform.h"
#include "..\..\include\shader\standard\GeometryShader.h"
#include "..\..\include\shader\standard\DirectionalShader.h"
#include "..\..\include\object\GameObject.h"
#include "..\..\include\object\Builder.h"
using Honeycomb::Component::Light::DirectionalLight;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::CameraController;
using Honeycomb::Shader::Standard::GeometryShader;
using Honeycomb::Shader::Standard::DirectionalShader;
using Honeycomb::Object::GameObject;
using Honeycomb::Object::Builder;

namespace Honeycomb::Core {
	RenderEngine* RenderEngine::renderEngine = nullptr;

	GameObject *dirLight = Builder::getBuilder()->newDirectionalLight();

	RenderEngine* RenderEngine::getRenderEngine() {
		if (renderEngine == nullptr)
			renderEngine = new RenderEngine();

		return renderEngine;
	}

	void RenderEngine::render() {
		if (GameScene::getActiveScene() != nullptr)
			this->render(*GameScene::getActiveScene());
	}

	void RenderEngine::render(GameScene &scene) {
		// todo: temp
		GeometryShader::getGeometryShader()->setProjection(
			CameraController::getActiveCamera()->getProjection());
		DirectionalShader::getDirectionalShader()->setProjection(
			CameraController::getActiveCamera()->getProjection());
		DirectionalShader::getDirectionalShader()->setUniform_DirectionalLight(
			*dirLight->getComponentOfType<DirectionalLight>("directionalLight"));

		// 1st Pass: Render the Mesh and its Texture
		//
		scene.render(*GeometryShader::getGeometryShader());

		// 2nd Pass: Render the Scene Directional Lights
		//
		///*
		glEnable(GL_BLEND); // Enable Blending
		glBlendFunc(GL_ONE, GL_ONE); // Additive Blending (Light is additive)
		glDepthMask(GL_FALSE); // Disable Depth Buffer
		glDepthFunc(GL_EQUAL); // Do not take into account depth
		//*/
		scene.render(*DirectionalShader::getDirectionalShader());

		///*
		glDepthFunc(GL_LESS); // Take into account depth
		glDepthMask(GL_TRUE); // Enable Depth Buffer
		glDisable(GL_BLEND); // Additive Blending no longer necessary
		//*/
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