#include "../../include/render/Renderer.h"

#include <GL/glew.h>

#include "../../include/component/render/MeshRenderer.h"
#include "../../include/object/GameObjectFactory.h"
#include "../../include/object/GameObject.h"
#include "../../include/render/RenderingEngine.h"

using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Graphics::Cubemap;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Graphics::TextureFilterMagMode;
using Honeycomb::Graphics::TextureDataFormat;
using Honeycomb::Graphics::TextureDataInternalFormat;
using Honeycomb::Graphics::TextureDataType;
using Honeycomb::Graphics::TextureWrapMode;
using Honeycomb::Object::GameObjectFactory;
using Honeycomb::Math::Vector4f;
using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderType;

namespace Honeycomb { namespace Render {
	Renderer* Renderer::renderer = nullptr;

	const int Renderer::SHADOW_MAP_WIDTH = 1024;
	const int Renderer::SHADOW_MAP_HEIGHT = 1024;

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

	const int& Renderer::getShadowMapHeight() const {
		return this->SHADOW_MAP_HEIGHT;
	}

	const int& Renderer::getShadowMapWidth() const {
		return this->SHADOW_MAP_WIDTH;
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

	void Renderer::setSkybox(const std::shared_ptr<Cubemap> &sky) {
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
		this->setSkybox(Cubemap::newCubemapShared());
		this->setSolidColor(Vector4f(0.0F, 0.0F, 0.0F, 0.0F));

		this->initializeShadowMapDependencies();

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
		auto cube = GameObjectFactory::getFactory().newCube();
		this->cubemapMesh = cube->getComponent<MeshRenderer>().getMeshes()[0];
	
		// Initialize Skybox Shader
		this->skyboxShader.initialize();
		this->skyboxShader.addShader("../Honeycomb GE/res/shaders"
			"/cubemap/skyboxVS.glsl", ShaderType::VERTEX_SHADER);
		this->skyboxShader.addShader("../Honeycomb GE/res/shaders"
			"/cubemap/texturedSkyboxFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->skyboxShader.finalizeShaderProgram();

		// Initialize Solid Color Shader
		this->solidColorShader.initialize();
		this->solidColorShader.addShader("../Honeycomb GE/res/shaders"
			"/cubemap/skyboxVS.glsl", ShaderType::VERTEX_SHADER);
		this->solidColorShader.addShader("../Honeycomb GE/res/shaders"
			"/cubemap/solidColorSkyboxFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->solidColorShader.finalizeShaderProgram();
	}

	void Renderer::initializeFXAAShader() {
		this->fxaaShader.initialize();
		this->fxaaShader.addShader("../Honeycomb GE/res/shaders/render/"
			"antialiasing/fxaa/fxaaVS.glsl", ShaderType::VERTEX_SHADER);
		this->fxaaShader.addShader("../Honeycomb GE/res/shaders/render/"
			"antialiasing/fxaa/fxaaFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->fxaaShader.finalizeShaderProgram();

		this->fxaaShader.setUniform_f("spanMax", 8.0F);
		this->fxaaShader.setUniform_f("reduceMin", 1.0F / 128.0F);
		this->fxaaShader.setUniform_f("reduceMul", 1.0F / 8.0F);
	}

	void Renderer::initializeGammaShader() {
		this->gammaShader.initialize();
		this->gammaShader.addShader("../Honeycomb GE/res/shaders/render/"
			"gamma/gammaVS.glsl", ShaderType::VERTEX_SHADER);
		this->gammaShader.addShader("../Honeycomb GE/res/shaders/render/"
			"gamma/gammaFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->gammaShader.finalizeShaderProgram();

		this->gammaShader.setUniform_f("gamma", 2.2F);
	}

	void Renderer::initializeShadowMapDependencies() {
		// Initialize the Classic Shadow Map Texture (simple depth texture)
		this->cShadowMapTexture = Texture2D::newTexture2DUnique();
		this->cShadowMapTexture->setImageDataManual(
			nullptr, TextureDataType::DATA_FLOAT,
			TextureDataInternalFormat::INTERNAL_FORMAT_DEPTH_COMPONENT,
			TextureDataFormat::FORMAT_DEPTH_COMPONENT,
			Renderer::SHADOW_MAP_WIDTH, Renderer::SHADOW_MAP_HEIGHT);
		this->cShadowMapTexture->setFiltering(
			TextureFilterMagMode::FILTER_MAG_NEAREST);
		this->cShadowMapTexture->setWrap(TextureWrapMode::WRAP_REPEAT);

		// Initialize the Classic Shadow Map Buffer
		GLuint cBF;
		glGenFramebuffers(1, &cBF);
		this->cShadowMapBuffer = cBF;
		glBindFramebuffer(GL_FRAMEBUFFER, this->cShadowMapBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D, this->cShadowMapTexture->getTextureID(), 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Initialize the Classic Shadow Map Shader (note: this should be used
		// for orthographic lights such as the Directional Light).
		this->cShadowMapShader.initialize();
		this->cShadowMapShader.addShader("../Honeycomb GE/res/shaders/render/"
			"shadow/classic/cShadowMapVS.glsl", ShaderType::VERTEX_SHADER);
		this->cShadowMapShader.addShader("../Honeycomb GE/res/shaders/render/"
			"shadow/classic/cShadowMapFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->cShadowMapShader.finalizeShaderProgram();

		// Initialize the Classic Shadow Map Linear Shader (note: this should
		// be used for perspective lights such as the Point Light or the Spot
		// Light).
		this->cShadowMapLinearShader.initialize();
		this->cShadowMapLinearShader.addShader("../Honeycomb GE/res/shaders/"
			"render/shadow/classic/cShadowMapVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->cShadowMapLinearShader.addShader("../Honeycomb GE/res/shaders/"
			"render/shadow/classic/cShadowMapLinearFS.glsl", 
			ShaderType::FRAGMENT_SHADER);
		this->cShadowMapLinearShader.finalizeShaderProgram();

		// Initialize the Variance Shadow Map Texture (32 bit Red & Green
		// channels texture).
		this->vShadowMapTexture = Texture2D::newTexture2DUnique();
		this->vShadowMapTexture->setImageDataManual(
			nullptr, TextureDataType::DATA_FLOAT,
			TextureDataInternalFormat::INTERNAL_FORMAT_RG32F,
			TextureDataFormat::FORMAT_RG,
			Renderer::SHADOW_MAP_WIDTH, Renderer::SHADOW_MAP_HEIGHT);
		this->vShadowMapTexture->setFiltering(
			TextureFilterMagMode::FILTER_MAG_LINEAR);
		this->vShadowMapTexture->setWrap(TextureWrapMode::WRAP_REPEAT);

		// Initialize the Anti Aliased Variance Shadow Map Texture (32 bit Red
		// & Green channels texture).
		this->vShadowMapTextureAA = Texture2D::newTexture2DUnique();
		this->vShadowMapTextureAA->setImageDataManual(
			nullptr, TextureDataType::DATA_FLOAT,
			TextureDataInternalFormat::INTERNAL_FORMAT_RG32F,
			TextureDataFormat::FORMAT_RG,
			Renderer::SHADOW_MAP_WIDTH, Renderer::SHADOW_MAP_HEIGHT);
		this->vShadowMapTextureAA->setFiltering(
			TextureFilterMagMode::FILTER_MAG_NEAREST);
		this->vShadowMapTextureAA->setWrap(TextureWrapMode::WRAP_REPEAT);

		// Initialize the Variance Shadow Map Buffer (for the depth component,
		// we borrow the depth buffer from the Classic Shadow Map Buffer). Also
		// set the Color Attachment 1 texture to the Antialiased Shadow Map
		// texture, so that we may antialias the standard VSM.
		GLuint vBF;
		glGenFramebuffers(1, &vBF);
		this->vShadowMapBuffer = vBF;
		glBindFramebuffer(GL_FRAMEBUFFER, this->vShadowMapBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, this->vShadowMapTexture->getTextureID(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
			GL_TEXTURE_2D, this->vShadowMapTextureAA->getTextureID(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D, this->cShadowMapTexture->getTextureID(), 0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Initialize the Variance Shadow Map Shader (used for orthographic
		// projection lights).
		this->vShadowMapShader.initialize();
		this->vShadowMapShader.addShader("../Honeycomb GE/res/shaders/render/"
			"shadow/variance/vShadowMapVS.glsl", ShaderType::VERTEX_SHADER);
		this->vShadowMapShader.addShader("../Honeycomb GE/res/shaders/render/"
			"shadow/variance/vShadowMapFS.glsl", ShaderType::FRAGMENT_SHADER);
		this->vShadowMapShader.finalizeShaderProgram();

		// Initialize the Variance Shadow Map Linear Depth Shader (used for
		// perspective projection lights).
		this->vShadowMapLinearShader.initialize();
		this->vShadowMapLinearShader.addShader("../Honeycomb GE/res/shaders/"
			"render/shadow/variance/vShadowMapVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->vShadowMapLinearShader.addShader("../Honeycomb GE/res/shaders/"
			"render/shadow/variance/vShadowMapLinearFS.glsl",
			ShaderType::FRAGMENT_SHADER);
		this->vShadowMapLinearShader.finalizeShaderProgram();

		// Initialize the Gaussian Blur Post Processing Shader for VSM
		this->vsmGaussianBlurShader.initialize();
		this->vsmGaussianBlurShader.addShader("../Honeycomb GE/res/shaders/"
			"post-processing/postProcessingVS.glsl", 
			ShaderType::VERTEX_SHADER);
		this->vsmGaussianBlurShader.addShader("../Honeycomb GE/res/shaders/"
			"post-processing/gaussBlur7FS.glsl", ShaderType::FRAGMENT_SHADER);
		this->vsmGaussianBlurShader.finalizeShaderProgram();
	}

	void Renderer::setBoolSettingGL(const int &cap, const bool &val) {
		if (val)	glEnable((GLenum)cap);
		else		glDisable((GLenum)cap);
	}

	void Renderer::setGamma(const float &g) {
		this->gammaShader.setUniform_f("gamma", g);
	}
} }
