#include "..\..\include\render\ForwardRendererMulti.h"

#include <GL\glew.h>

#include <vector>

#include "..\..\include\component\light\BaseLight.h"
#include "..\..\include\component\render\CameraController.h"

using Honeycomb::Component::Light::BaseLight;
using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Component::Render::CameraController;

namespace Honeycomb::Render {
	ForwardRendererMulti* ForwardRendererMulti::forwardRendererMulti = nullptr;

	ForwardRendererMulti* ForwardRendererMulti::getForwardRendererMulti() {
		if (forwardRendererMulti == nullptr)
			forwardRendererMulti = new ForwardRendererMulti();

		return forwardRendererMulti;
	}

	void ForwardRendererMulti::render(GameScene &scene) {
		// Get the List of Active Lights
		std::vector<BaseLight*> &activeLights = scene.getActiveLights();
		
		// Render the very first active light regularly [clean up this mess TODO]
		BaseLight firstLight = *activeLights.at(0);
		firstLight.toShader(*this->lightShaders.at(firstLight.getName()),
			firstLight.uniformName);
		CameraController::getActiveCamera()->toShader(
			*this->lightShaders.at(firstLight.getName()), "camera");
		scene.render(*this->lightShaders.at(firstLight.getName()));

		// Enable Special Rendering parameters for remaining passes
		glEnable(GL_BLEND); // Blend light contributions from various sources
		glBlendFunc(GL_ONE, GL_ONE); // Blend full contribution of both sources
		glDepthMask(GL_FALSE); // Disable Rendering to Depth Buffer
		glDepthFunc(GL_EQUAL); // Only render if same depth

		// Render the scene for the remaining lights
		for (BaseLight *bL : activeLights) {
			ShaderProgram *bLShader = this->lightShaders.at(bL->getName());

			// todo, if shader doesnt exist for the light...

			bL->toShader(*bLShader, bL->uniformName);
			CameraController::getActiveCamera()->toShader(*bLShader, "camera");
			scene.render(*bLShader);
		}

		// Enable Regular Rendering for the first pass only
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	ForwardRendererMulti::ForwardRendererMulti() : Renderer() {
		// Initialize all of the Light Shaders which are used for the
		// renderable lights.
		ShaderProgram *ambientShader = new ShaderProgram;
		ambientShader->addShader("..\\Honeycomb GE\\res\\shaders\\standard\\"
			"source\\vertex\\stdVertex.glsl", GL_VERTEX_SHADER);
		ambientShader->addShader("..\\Honeycomb GE\\res\\shaders\\standard\\"
			"source\\light\\stdAmbientLight.glsl", GL_FRAGMENT_SHADER);
		ambientShader->finalizeShaderProgram();

		ShaderProgram *directionalShader = new ShaderProgram;
		directionalShader->addShader("..\\Honeycomb GE\\res\\shaders\\standard"
			"\\source\\vertex\\stdVertex.glsl", GL_VERTEX_SHADER);
		directionalShader->addShader("..\\Honeycomb GE\\res\\shaders\\standard"
			"\\source\\light\\stdDirectionalLight.glsl", GL_FRAGMENT_SHADER);
		directionalShader->finalizeShaderProgram();

		ShaderProgram *pointShader = new ShaderProgram;
		pointShader->addShader("..\\Honeycomb GE\\res\\shaders\\standard\\"
			"source\\vertex\\stdVertex.glsl", GL_VERTEX_SHADER);
		pointShader->addShader("..\\Honeycomb GE\\res\\shaders\\standard\\"
			"source\\light\\stdPointLight.glsl", GL_FRAGMENT_SHADER);
		pointShader->finalizeShaderProgram();

		ShaderProgram *spotShader = new ShaderProgram;
		spotShader->addShader("..\\Honeycomb GE\\res\\shaders\\standard\\"
			"source\\vertex\\stdVertex.glsl", GL_VERTEX_SHADER);
		spotShader->addShader("..\\Honeycomb GE\\res\\shaders\\standard\\"
			"source\\light\\stdSpotLight.glsl", GL_FRAGMENT_SHADER);
		spotShader->finalizeShaderProgram();

		
		this->lightShaders.insert({ "AmbientLight", ambientShader });
		this->lightShaders.insert({ "DirectionalLight", directionalShader });
		this->lightShaders.insert({ "PointLight", pointShader });
		this->lightShaders.insert({ "SpotLight", spotShader });
	}

	ForwardRendererMulti::~ForwardRendererMulti() {

	}
}