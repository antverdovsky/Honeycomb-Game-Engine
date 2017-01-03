/******************************************************************************

#include "..\..\include\render\ForwardRendererSingle.h"

#include "..\..\include\shader\phong\PhongShader.h"

/////////////////////////////////////
/// CURRENTLY BROKEN - DO NOT USE ///
/////////////////////////////////////

using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Scene::GameScene;

using Honeycomb::Shader::Phong::PhongShader; // Default Shader

namespace Honeycomb::Render {
	ForwardRendererSingle* ForwardRendererSingle::legacyForwardRenderer = 
		nullptr;
	
	ForwardRendererSingle* ForwardRendererSingle::getLegacyForwardRenderer() {
		if (legacyForwardRenderer == nullptr)
			legacyForwardRenderer = new ForwardRendererSingle();

		return legacyForwardRenderer;
	}

	const ShaderProgram* ForwardRendererSingle::getShader() const {
		return this->shader;
	}

	void ForwardRendererSingle::render(GameScene &scene) {
		scene.render(*this->shader);
	}

	void ForwardRendererSingle::setShader(ShaderProgram *shader) {
		this->shader = shader;
	}

	ForwardRendererSingle::ForwardRendererSingle() : Renderer() {
		this->shader = PhongShader::getPhongShader();
	}

	ForwardRendererSingle::~ForwardRendererSingle() {

	}
}

******************************************************************************/