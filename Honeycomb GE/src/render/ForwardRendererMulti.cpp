#include "..\..\include\render\ForwardRendererMulti.h"

using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;

/// TEMPORARY ///
#include "..\..\include\shader\phong\PhongAmbientShader.h"
using Honeycomb::Shader::Phong::PhongAmbientShader;

#include "..\..\include\math\Vector4f.h";
using Honeycomb::Math::Vector4f;
#include "..\..\include\component\light\AmbientLight.h"
using Honeycomb::Component::Light::AmbientLight;

namespace Honeycomb::Render {
	ForwardRendererMulti* ForwardRendererMulti::forwardRendererMulti = nullptr;

	ForwardRendererMulti* ForwardRendererMulti::getForwardRendererMulti() {
		if (forwardRendererMulti == nullptr)
			forwardRendererMulti = new ForwardRendererMulti();

		return forwardRendererMulti;
	}

	void ForwardRendererMulti::render(GameScene &scene) {
		this->ambientShader->bindShaderProgram();
		/// TEMPORARY TODO: SOME METHOD TO MAKE THIS EASIER ///
		this->ambientShader->setUniform_vec4("ambientLight.base.color",
			ambientLightObject1.getComponentOfType<AmbientLight>("AmbientLight")->
			getColor());
		this->ambientShader->setUniform_f("ambientLight.base.intensity",
			ambientLightObject1.getComponentOfType<AmbientLight>("AmbientLight")->
			getIntensity());
		scene.render(*this->ambientShader);
	}

	void ForwardRendererMulti::setAmbientLightShader(ShaderProgram *shader) {
		this->ambientShader = shader;
	}

	ForwardRendererMulti::ForwardRendererMulti() : Renderer() {
		this->ambientShader = PhongAmbientShader::getPhongAmbientShader();

		/// TEMPORARY LIGHT INITIALIZATION ///
		this->ambientLightObject1 = *Honeycomb::Object::Builder::getBuilder()->
			newAmbientLight();
		this->ambientLightObject2 = *Honeycomb::Object::Builder::getBuilder()->
			newAmbientLight();
		//////////////////////////////////////

		/// TEMPORARY LIGHT CUSTOMIZATION ///
		this->ambientLightObject1.getComponentOfType<AmbientLight>("AmbientLight")->
			setColor(Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
		this->ambientLightObject2.getComponentOfType<AmbientLight>("AmbientLight")->
			setColor(Vector4f(0.0F, 0.0F, 1.0F, 1.0F));
		/////////////////////////////////////
	}

	ForwardRendererMulti::~ForwardRendererMulti() {

	}
}