#include "..\..\include\render\RenderingEngine.h"

//#include "..\..\include\render\ForwardRendererSingle.h"
#include "..\..\include\render\ForwardRendererMulti.h"
#include "..\..\include\render\deferred\DeferredRenderer.h"

using Honeycomb::Scene::GameScene;
//using Honeycomb::Render::ForwardRendererSingle;
using Honeycomb::Render::ForwardRendererMulti;
using Honeycomb::Render::Deferred::DeferredRenderer;

namespace Honeycomb::Render {
	RenderingEngine *RenderingEngine::renderingEngine = nullptr;

	RenderingEngine* RenderingEngine::getRenderingEngine() {
		if (renderingEngine == nullptr)
			renderingEngine = new RenderingEngine();

		return renderingEngine;
	}

	void RenderingEngine::render(GameScene &scene) {
		this->renderer->render(scene);
	}

	void RenderingEngine::setRenderingType(const RenderingType &type) {
		switch (type) {
		case RenderingType::TYPE_FORWARD_RENDERER_SINGLE:
//			this->renderer = ForwardRendererSingle::getLegacyForwardRenderer();
			break;
		case RenderingType::TYPE_FORWARD_RENDERER_MULTI:
			this->renderer = ForwardRendererMulti::getForwardRendererMulti();
			break;
		case RenderingType::TYPE_DEFERRED_RENDERER:
			this->renderer = DeferredRenderer::getDeferredRenderer();
			break;
		}
	}
	
	RenderingEngine::RenderingEngine() {
		//this->setRenderingType(RenderingType::TYPE_FORWARD_RENDERER_SINGLE);
	}

	RenderingEngine::~RenderingEngine() {

	}
}