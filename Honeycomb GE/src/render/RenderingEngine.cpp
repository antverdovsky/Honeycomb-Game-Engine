#include "../../include/render/RenderingEngine.h"

#include "../../include/render/deferred/DeferredRenderer.h"

using Honeycomb::Scene::GameScene;
using Honeycomb::Render::Deferred::DeferredRenderer;

namespace Honeycomb { namespace Render {
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
		case RenderingType::TYPE_DEFERRED_RENDERER:
			this->renderer = DeferredRenderer::getDeferredRenderer();
			break;
		}
	}
	
	RenderingEngine::RenderingEngine() {
		this->setRenderingType(RenderingType::TYPE_DEFERRED_RENDERER);
	}

	RenderingEngine::~RenderingEngine() {

	}
} }
