#include "..\..\include\render\ForwardRendererMulti.h"

#include <GL\glew.h>

#include <vector>

#include "..\..\include\component\light\BaseLight.h"
#include "..\..\include\component\render\CameraController.h"

#include "..\..\include\shader\phong\PhongAmbientShader.h"
#include "..\..\include\shader\phong\PhongDirectionalShader.h"
#include "..\..\include\shader\phong\PhongPointShader.h"
#include "..\..\include\shader\phong\PhongSpotShader.h"

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
		
		// Render the very first active light regularly
		activeLights.at(0)->toShader();
		CameraController::getActiveCamera()->toShader(
			*activeLights.at(0)->getShader());
		scene.render(*activeLights.at(0)->getShader());

		// Enable Special Rendering parameters for remaining passes
		glEnable(GL_BLEND); // Blend light contributions from various sources
		glBlendFunc(GL_ONE, GL_ONE); // Blend full contribution of both sources
		glDepthMask(GL_FALSE); // Disable Rendering to Depth Buffer
		glDepthFunc(GL_EQUAL); // Only render if same depth

		// Render the scene for the remaining lights
		for (int i = 1; i < activeLights.size(); i++) {
			activeLights.at(i)->toShader();
			CameraController::getActiveCamera()->toShader(
				*activeLights.at(i)->getShader());
			scene.render(*activeLights.at(i)->getShader());
		}

		// Enable Regular Rendering for the first pass only
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	ForwardRendererMulti::ForwardRendererMulti() : Renderer() {

	}

	ForwardRendererMulti::~ForwardRendererMulti() {

	}
}