#include "..\..\include\render\Renderer.h"

#include <GL\glew.h>

using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Render {
	Renderer* Renderer::renderer = nullptr;

	Renderer* Renderer::getRenderer() {
		if (renderer == nullptr)
			renderer = new Renderer();

		return renderer;
	}

	void Renderer::render(GameScene &scene) {
		
	}

	Renderer::Renderer() {
//		glCullFace(this->CULL_FACE);
		glClearColor(
			this->CLEAR_SCREEN_COLOR.getX(), this->CLEAR_SCREEN_COLOR.getY(),
			this->CLEAR_SCREEN_COLOR.getZ(), this->CLEAR_SCREEN_COLOR.getW());
		setBoolSettingGL(GL_DEPTH_TEST, this->DEPTH_TEST);
		setBoolSettingGL(GL_CULL_FACE, this->DO_CULL_FACES);
		setBoolSettingGL(GL_MULTISAMPLE, this->MSAA_SAMPLING);
//		glPolygonMode(GL_FRONT_AND_BACK, this->POLYGON_MODE);
	}

	Renderer::~Renderer() {

	}

	void Renderer::setBoolSettingGL(const int &cap, const bool &val) {
		if (val) glEnable(cap);
		else glDisable(cap);
	}
}