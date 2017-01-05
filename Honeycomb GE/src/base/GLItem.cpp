#include "..\..\include\base\GLItem.h"

namespace Honeycomb::Base {
	const bool& GLItem::getIsInitialized() const {
		return this->isInitialized;
	}

	bool GLItem::initialize() {
		return false;
	}

	void GLItem::destroy() {

	}
	
	GLItem::GLItem() {

	}

	GLItem::~GLItem() {

	}
}