#include "..\..\include\render\ForwardRendererMulti.h"

#include <GL\glew.h>

using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;

/// TEMPORARY ///
#include <cmath>

#include "..\..\include\shader\phong\PhongAmbientShader.h"
using Honeycomb::Shader::Phong::PhongAmbientShader;
#include "..\..\include\shader\phong\PhongDirectionalShader.h"
using Honeycomb::Shader::Phong::PhongDirectionalShader;
#include "..\..\include\shader\phong\PhongPointShader.h"
using Honeycomb::Shader::Phong::PhongPointShader;
#include "..\..\include\shader\phong\PhongSpotShader.h"
using Honeycomb::Shader::Phong::PhongSpotShader;

#include "..\..\include\component\render\CameraController.h"
using Honeycomb::Component::Render::CameraController;
#include "..\..\include\component\light\PointLight.h"
using Honeycomb::Component::Light::PointLight;
#include "..\..\include\component\light\SpotLight.h"
using Honeycomb::Component::Light::SpotLight;
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
#include <ctime>
#include <stdlib.h>


namespace Honeycomb::Render {
	ForwardRendererMulti* ForwardRendererMulti::forwardRendererMulti = nullptr;

	ForwardRendererMulti* ForwardRendererMulti::getForwardRendererMulti() {
		if (forwardRendererMulti == nullptr)
			forwardRendererMulti = new ForwardRendererMulti();

		return forwardRendererMulti;
	}

	void ForwardRendererMulti::render(GameScene &scene) {
		//glDisable(GL_BLEND);
		
		CameraController::getActiveCamera()->toShader(*this->ambientShader);
		this->ambientLightObject1.getComponentOfType<AmbientLight>("AmbientLight")->
			toShader(*this->ambientShader, "ambientLight");
		scene.render(*this->ambientShader);

		glEnable(GL_BLEND); // Blend light contributions from various sources
		glBlendFunc(GL_ONE, GL_ONE); // Blend full contribution of both sources
		glDepthMask(GL_FALSE); // Disable Rendering to Depth Buffer
		glDepthFunc(GL_EQUAL); // Only render if same depth

		CameraController::getActiveCamera()->toShader(*this->directionalShader);
		this->directionalLightObject1.getComponentOfType<DirectionalLight>("DirectionalLight")->
			toShader(*this->directionalShader, "directionalLight");
		scene.render(*this->directionalShader);

		for (int i = 0; i < 12; i++) {
			CameraController::getActiveCamera()->toShader(*this->pointShader);
			this->pointLights[i].getComponentOfType<PointLight>("PointLight")->
				toShader(*this->pointShader, "pointLight");

			scene.render(*this->pointShader);
		}

		for (int i = 0; i < 8; i++) {
			CameraController::getActiveCamera()->toShader(*this->spotShader);
			this->spotLights[i].getComponentOfType<SpotLight>("SpotLight")->
				toShader(*this->spotShader, "spotLight");

			scene.render(*this->spotShader);
		}
		
		// Re-enable regular settings
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	void ForwardRendererMulti::setAmbientLightShader(ShaderProgram *shader) {
		this->ambientShader = shader;
	}

	ForwardRendererMulti::ForwardRendererMulti() : Renderer() {
		srand(time(NULL));
		
		this->ambientShader = PhongAmbientShader::getPhongAmbientShader();
		this->directionalShader = PhongDirectionalShader::getPhongDirectionalShader();
		this->pointShader = PhongPointShader::getPhongPointShader();
		this->spotShader = PhongSpotShader::getPhongSpotShader();

		/// TEMPORARY LIGHT INITIALIZATION ///
		this->ambientLightObject1 = *Honeycomb::Object::Builder::getBuilder()->
			newAmbientLight();
		this->ambientLightObject1.start();
		this->ambientLightObject2 = *Honeycomb::Object::Builder::getBuilder()->
			newAmbientLight();
		this->ambientLightObject2.start();
		this->directionalLightObject1 = *Honeycomb::Object::Builder::getBuilder()->
			newDirectionalLight();
		this->directionalLightObject1.start();
		this->directionalLightObject2 = *Honeycomb::Object::Builder::getBuilder()->
			newDirectionalLight();
		this->directionalLightObject2.start();
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

		for (int i = 0; i < 12; i++) {
			this->pointLights[i] = *Honeycomb::Object::Builder::getBuilder()->
				newPointLight();

			this->pointLights[i].getComponentOfType<Transform>("Transform")->
				translate(Vector3f(25 * cos(i), 2.5F, 25 * sin(i)));
			this->pointLights[i].getComponentOfType<PointLight>("PointLight")->
				setIntensity(2.5F);
			this->pointLights[i].getComponentOfType<PointLight>("PointLight")->
				setColor(Vector4f(sin(i), 1.0F, cos(i), 1.0F));

			this->pointLights[i].start();
		}

		for (int i = 0; i < 8; i++) {
			this->spotLights[i] = *Honeycomb::Object::Builder::getBuilder()->
				newSpotLight();

			this->spotLights[i].getComponentOfType<Transform>("Transform")->
				translate(Vector3f(25 * cos(i), 1.5F, 25 * sin(i)));
			this->spotLights[i].getComponentOfType<SpotLight>("SpotLight")->
				setIntensity(20.0F);
			this->spotLights[i].getComponentOfType<SpotLight>("SpotLight")->
				setRange(10.0F);
			this->spotLights[i].getComponentOfType<SpotLight>("SpotLight")->
				setColor(Vector4f(sin(i), 1.0F, cos(i), 1.0F));

			this->spotLights[i].start();
		}
		/////////////////////////////////////
	}

	ForwardRendererMulti::~ForwardRendererMulti() {

	}
}