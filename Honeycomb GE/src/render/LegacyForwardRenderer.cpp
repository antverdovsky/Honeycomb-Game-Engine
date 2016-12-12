#include "..\..\include\render\LegacyForwardRenderer.h"

#include "..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Scene::GameScene;

using Honeycomb::Shader::Phong::PhongShader; // Default Shader

namespace Honeycomb::Render {
	LegacyForwardRenderer* LegacyForwardRenderer::legacyForwardRenderer = 
		nullptr;
	
	LegacyForwardRenderer* LegacyForwardRenderer::getLegacyForwardRenderer() {
		if (legacyForwardRenderer == nullptr)
			legacyForwardRenderer = new LegacyForwardRenderer();

		return legacyForwardRenderer;
	}

	const ShaderProgram* LegacyForwardRenderer::getShader() const {
		return this->shader;
	}

	void LegacyForwardRenderer::render(GameScene &scene) {
		scene.render(*this->shader);
	}

	void LegacyForwardRenderer::setShader(ShaderProgram *shader) {
		this->shader = shader;
	}

	LegacyForwardRenderer::LegacyForwardRenderer() : Renderer() {
		this->shader = PhongShader::getPhongShader();
	}

	LegacyForwardRenderer::~LegacyForwardRenderer() {

	}
}