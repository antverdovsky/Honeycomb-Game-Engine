#include "..\..\include\render\Renderer.h"

#include <GL\glew.h>

#include "..\..\include\component\render\MeshRenderer.h"
#include "..\..\include\object\Builder.h"
#include "..\..\include\object\GameObject.h"
#include "..\..\include\render\RenderingEngine.h"

using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Graphics::Cubemap;
using Honeycomb::Object::Builder;
using Honeycomb::Math::Vector4f;
using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderType;

namespace Honeycomb::Render {
	Renderer* Renderer::renderer = nullptr;

	Renderer* Renderer::getRenderer() {
		// Since the RenderingEngine is the component which determines which
		// Renderer is to be used, it makes more sense to fetch the Renderer
		// from the Rendering Engine.
		if (renderer == nullptr)
			renderer = RenderingEngine::getRenderingEngine()->renderer;

		return renderer;
	}

	std::vector<ShaderProgram>& Renderer::getPostShaders() {
		return this->postShaders;
	}

	void Renderer::render(GameScene &scene) {

	}

	void Renderer::setAntiAliasing(const AntiAliasing &aa) {
		this->antiAliasing = aa;
	}

	void Renderer::setBackgroundMode(const BackgroundMode &m) {
		this->backgroundMode = m;
	}

	void Renderer::setColorSpace(const ColorSpace &cs) {
		this->colorSpace = cs;

		// If gamma is enabled, set it to some value; else, keep gamma at 1.
		if (cs == ColorSpace::GAMMA_POST) this->setGamma(2.2F);
		else this->setGamma(1.0F);
	}

	void Renderer::setCullingFace(const PolygonFace &f) {
		this->cullingFace = f;
		glCullFace((GLenum)f);
	}

	void Renderer::setDepthFunction(const TestFunction &f) {
		this->depthFunction = f;
		glDepthFunc((GLenum)f);
	}

	void Renderer::setDoCullFaces(const bool &b) {
		this->doCullFaces = b;
		this->setBoolSettingGL(GL_CULL_FACE, b);
	}

	void Renderer::setDoDepthTest(const bool &b) {
		this->doDepthTest = b;
		this->setBoolSettingGL(GL_DEPTH_TEST, b);
	}

	void Renderer::setDoPostProcess(const bool &b) {
		this->doPostProcess = b;
	}

	void Renderer::setFrontFace(const WindingOrder &w) {
		this->frontFace = w;
		glFrontFace((GLenum)w);
	}

	void Renderer::setPolygonMode(const PolygonFace &f, const PolygonMode &m) {
		switch (f) {
		case PolygonFace::BACK:
			this->polygonModeBack = m;
			break;
		case PolygonFace::FRONT:
			this->polygonModeFront = m;
			break;
		case PolygonFace::FRONT_AND_BACK:
			this->polygonModeBack = m;
			this->polygonModeFront = m;
			break;
		}

		glPolygonMode((GLenum)f, (GLenum)m);
	}

	void Renderer::setSkybox(const Honeycomb::Graphics::Cubemap &sky) {
		this->skybox = sky;
	}

	void Renderer::setSolidColor(const Honeycomb::Math::Vector4f &col) {
		this->solidColor = col;
	}

	Renderer::Renderer() {
		this->initializeFXAAShader();
		this->setAntiAliasing(AntiAliasing::FXAA);

		this->initializeGammaShader();
		this->setColorSpace(ColorSpace::GAMMA_POST);

		this->initializeCubemapDependencies();
		this->setBackgroundMode(BackgroundMode::SKYBOX);
		this->setSkybox(Cubemap());
		this->setSolidColor(Vector4f(0.0F, 0.0F, 0.0F, 0.0F));

		this->setDoPostProcess(true);

		this->setFrontFace(WindingOrder::COUNTER_CLOCKWISE);
		this->setCullingFace(PolygonFace::BACK);
		this->setDoCullFaces(true);

		this->setDoDepthTest(true);
		this->setDepthFunction(TestFunction::LESS);
		
		this->setPolygonMode(PolygonFace::FRONT, PolygonMode::FILL);
		this->setPolygonMode(PolygonFace::BACK, PolygonMode::FILL);
	}

	Renderer::~Renderer() {

	}

	void Renderer::initializeCubemapDependencies() {
		// Initialize Skybox Mesh (steal it from a Cube)
		auto cube = Builder::getBuilder()->newCube();
		this->cubemapMesh = cube->getComponent<MeshRenderer>()->getMesh();
		delete cube;

		// Initialize Skybox Shader
		this->skyboxShader.initialize();
		this->skyboxShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\cubemap\\skyboxVS.glsl", ShaderType::VERTEX_SHADER);
		this->skyboxShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\cubemap\\texturedSkyboxFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->skyboxShader.finalizeShaderProgram();

		// Initialize Solid Color Shader
		this->solidColorShader.initialize();
		this->solidColorShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\cubemap\\skyboxVS.glsl", ShaderType::VERTEX_SHADER);
		this->solidColorShader.addShader("..\\Honeycomb GE\\res\\shaders"
			"\\cubemap\\solidColorSkyboxFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->solidColorShader.finalizeShaderProgram();
	}

	void Renderer::initializeFXAAShader() {
		this->fxaaShader.initialize();
		this->fxaaShader.addShader("..\\Honeycomb GE\\res\\shaders\\render\\"
			"antialiasing\\fxaa\\fxaaVS.glsl", ShaderType::VERTEX_SHADER);
		this->fxaaShader.addShader("..\\Honeycomb GE\\res\\shaders\\render\\"
			"antialiasing\\fxaa\\fxaaFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->fxaaShader.finalizeShaderProgram();

		this->fxaaShader.setUniform_f("spanMax", 8.0F);
		this->fxaaShader.setUniform_f("reduceMin", 1.0F / 128.0F);
		this->fxaaShader.setUniform_f("reduceMul", 1.0F / 8.0F);
	}

	void Renderer::initializeGammaShader() {
		this->gammaShader.initialize();
		this->gammaShader.addShader("..\\Honeycomb GE\\res\\shaders\\render\\"
			"gamma\\gammaVS.glsl", ShaderType::VERTEX_SHADER);
		this->gammaShader.addShader("..\\Honeycomb GE\\res\\shaders\\render\\"
			"gamma\\gammaFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->gammaShader.finalizeShaderProgram();

		this->gammaShader.setUniform_f("gamma", 2.2F);
	}

	void Renderer::setBoolSettingGL(const int &cap, const bool &val) {
		if (val)	glEnable((GLenum)cap);
		else		glDisable((GLenum)cap);
	}

	void Renderer::setGamma(const float &g) {
		this->gammaShader.setUniform_f("gamma", g);
	}
}