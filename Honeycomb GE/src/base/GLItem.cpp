#include "../../include/base/GLItem.h"

namespace Honeycomb { namespace Base {
	const bool& GLItem::getIsInitialized() const {
		return this->isInitialized;
	}

	bool GLItem::initialize() {
		return false;
	}

	void GLItem::destroy() {

	}
	
	GLItem::GLItem() {
		this->isInitialized = false;
	}

	GLItem::~GLItem() {

	}
} }
