#include "..\..\include\render\Renderer.h"

#include <GL\glew.h>

#include "..\..\include\render\RenderingEngine.h"

using Honeycomb::Scene::GameScene;
using Honeycomb::Shader::ShaderProgram;

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

	Renderer::Renderer() {
		this->doPostProcess = true;

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

	void Renderer::setBoolSettingGL(const int &cap, const bool &val) {
		if (val)	glEnable((GLenum)cap);
		else		glDisable((GLenum)cap);
	}
}