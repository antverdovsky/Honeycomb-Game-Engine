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
		/// Render the scene with the Ambient Light Shader
		CameraController::getActiveCamera()->toShader(*this->ambientShader);
		for (AmbientLight *aL : scene.getAmbientLights()) {
			aL->toShader(*this->ambientShader, "ambientLight");
			scene.render(*this->ambientShader);
		}

		glEnable(GL_BLEND); // Blend light contributions from various sources
		glBlendFunc(GL_ONE, GL_ONE); // Blend full contribution of both sources
		glDepthMask(GL_FALSE); // Disable Rendering to Depth Buffer
		glDepthFunc(GL_EQUAL); // Only render if same depth

		/// Render the scene with the Directional Light Shader
		CameraController::getActiveCamera()->toShader(*this->
			directionalShader);
		for (DirectionalLight *dL : scene.getDirectionalLights()) {
			dL->toShader(*this->directionalShader, "directionalLight");
			scene.render(*this->directionalShader);
		}

		/// Render the scene with the Point Light Shader
		CameraController::getActiveCamera()->toShader(*this->pointShader);
		for (PointLight *pL : scene.getPointLights()) {
			pL->toShader(*this->pointShader, "pointLight");
			scene.render(*this->pointShader);
		}

		/// Render the scene with the Point Light Shader
		CameraController::getActiveCamera()->toShader(*this->spotShader);
		for (SpotLight *sL : scene.getSpotLights()) {
			sL->toShader(*this->spotShader, "spotLight");
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
		this->pointShader = PhongPointShader::getPhongPointShader();
		this->spotShader = PhongSpotShader::getPhongSpotShader();
		this->directionalShader = 
			PhongDirectionalShader::getPhongDirectionalShader();
	}

	ForwardRendererMulti::~ForwardRendererMulti() {

	}
}