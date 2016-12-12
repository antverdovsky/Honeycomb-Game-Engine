#include "..\..\include\render\RenderingEngine.h"

#include "..\..\include\render\LegacyForwardRenderer.h"

using Honeycomb::Scene::GameScene;
using Honeycomb::Render::LegacyForwardRenderer;

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
		case RenderingType::TYPE_LEGACY_FORWARD_RENDERER:
			this->renderer = LegacyForwardRenderer::getLegacyForwardRenderer();
		}
	}
	
	RenderingEngine::RenderingEngine() {
		this->setRenderingType(RenderingType::TYPE_LEGACY_FORWARD_RENDERER);
	}

	RenderingEngine::~RenderingEngine() {

	}
}