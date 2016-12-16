#include "..\..\include\render\ForwardRendererMulti.h"

#include <GL\glew.h>

using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;

/// TEMPORARY ///
#include "..\..\include\shader\phong\PhongAmbientShader.h"
using Honeycomb::Shader::Phong::PhongAmbientShader;
#include "..\..\include\shader\phong\PhongDirectionalShader.h"
using Honeycomb::Shader::Phong::PhongDirectionalShader;

#include "..\..\include\component\render\CameraController.h"
using Honeycomb::Component::Render::CameraController;
#include "..\..\include\component\light\DirectionalLight.h"
using Honeycomb::Component::Light::DirectionalLight;
#include "..\..\include\math\Vector3f.h";
using Honeycomb::Math::Vector3f;
#include "..\..\include\math\Vector4f.h";
using Honeycomb::Math::Vector4f;
#include "..\..\include\math\Quaternion.h";
using Honeycomb::Math::Quaternion;
#include "..\..\include\component\light\AmbientLight.h"
using Honeycomb::Component::Light::AmbientLight;
#include "..\..\include\component\physics\Transform.h"
using Honeycomb::Component::Physics::Transform;

namespace Honeycomb::Render {
	ForwardRendererMulti* ForwardRendererMulti::forwardRendererMulti = nullptr;

	ForwardRendererMulti* ForwardRendererMulti::getForwardRendererMulti() {
		if (forwardRendererMulti == nullptr)
			forwardRendererMulti = new ForwardRendererMulti();

		return forwardRendererMulti;
	}

	void ForwardRendererMulti::render(GameScene &scene) {
		//glDisable(GL_BLEND);
		
		this->ambientShader->setUniform_mat4("camProjection",
			CameraController::getActiveCamera()->getProjection());
		this->directionalShader->setUniform_mat4("camProjection",
			CameraController::getActiveCamera()->getProjection());
		
		/// TEMPORARY TODO: SOME METHOD TO MAKE THIS EASIER ///
		this->ambientShader->setUniform_vec4("ambientLight.base.color",
			ambientLightObject1.getComponentOfType<AmbientLight>("AmbientLight")->
			getColor());
		this->ambientShader->setUniform_f("ambientLight.base.intensity",
			ambientLightObject1.getComponentOfType<AmbientLight>("AmbientLight")->
			getIntensity());
		scene.render(*this->ambientShader);

	
		this->directionalShader->setUniform_vec3("cameraPos",
			CameraController::getActiveCamera()->getAttached()->
			getComponentOfType<Transform>("Transform")->getTranslation());

		glEnable(GL_BLEND); // Blend light contributions from various sources
		glBlendFunc(GL_ONE, GL_ONE); // Blend full contribution of both sources
		glDepthMask(GL_FALSE); // Disable Rendering to Depth Buffer
		glDepthFunc(GL_EQUAL); // Only render if same depth

		this->directionalShader->setUniform_vec4("directionalLight.base.color",
			directionalLightObject1.getComponentOfType<DirectionalLight>("DirectionalLight")->
			getColor());
		this->directionalShader->setUniform_f("directionalLight.base.intensity",
			directionalLightObject1.getComponentOfType<DirectionalLight>("DirectionalLight")->
			getIntensity());
		this->directionalShader->setUniform_vec3("directionalLight.direction",
			directionalLightObject1.getComponentOfType<Transform>("Transform")->
			getLocalForward());
		scene.render(*this->directionalShader);

		this->directionalShader->setUniform_vec4("directionalLight.base.color",
			directionalLightObject2.getComponentOfType<DirectionalLight>("DirectionalLight")->
			getColor());
		this->directionalShader->setUniform_f("directionalLight.base.intensity",
			directionalLightObject2.getComponentOfType<DirectionalLight>("DirectionalLight")->
			getIntensity());
		this->directionalShader->setUniform_vec3("directionalLight.direction",
			directionalLightObject2.getComponentOfType<Transform>("Transform")->
			getLocalForward());
		scene.render(*this->directionalShader);
		
		// Re-enable regular settings
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	void ForwardRendererMulti::setAmbientLightShader(ShaderProgram *shader) {
		this->ambientShader = shader;
	}

	ForwardRendererMulti::ForwardRendererMulti() : Renderer() {
		this->ambientShader = PhongAmbientShader::getPhongAmbientShader();
		this->directionalShader = PhongDirectionalShader::getPhongDirectionalShader();

		/// TEMPORARY LIGHT INITIALIZATION ///
		this->ambientLightObject1 = *Honeycomb::Object::Builder::getBuilder()->
			newAmbientLight();
		this->ambientLightObject2 = *Honeycomb::Object::Builder::getBuilder()->
			newAmbientLight();
		this->directionalLightObject1 = *Honeycomb::Object::Builder::getBuilder()->
			newDirectionalLight();
		this->directionalLightObject2 = *Honeycomb::Object::Builder::getBuilder()->
			newDirectionalLight();
		//////////////////////////////////////

		/// TEMPORARY LIGHT CUSTOMIZATION ///
		this->ambientLightObject1.getComponentOfType<AmbientLight>("AmbientLight")->
			setColor(Vector4f(1.0F, 1.0F, 1.0F, 1.0F));
		this->ambientLightObject1.getComponentOfType<AmbientLight>("AmbientLight")->
			setIntensity(0.1F);
		this->ambientLightObject2.getComponentOfType<AmbientLight>("AmbientLight")->
			setColor(Vector4f(0.0F, 0.0F, 1.0F, 1.0F));
		this->ambientLightObject2.getComponentOfType<AmbientLight>("AmbientLight")->
			setIntensity(0.1F);
		this->directionalLightObject2.getComponentOfType<Transform>("Transform")->
			rotate(Quaternion(Vector3f::getGlobalRight(), -3.1415926 / 2.0F));
		this->directionalLightObject2.getComponentOfType<DirectionalLight>("DirectionalLight")->
			setColor(Vector4f(0.0F, 1.0F, 0.0F, 1.0F));
		/////////////////////////////////////
	}

	ForwardRendererMulti::~ForwardRendererMulti() {

	}
}