#include "../../include/base/GLItem.h"

#include <sstream>

namespace Honeycomb { namespace Base {
	const bool& GLItem::getIsInitialized() const {
		return this->isInitialized;
	}

	void GLItem::initialize() {
		if (this->isInitialized) throw GLItemAlreadyInitializedException(this);
		this->isInitialized = true;
	}

	void GLItem::destroy() {

	}
	
	GLItem::GLItem() {
		this->isInitialized = false;
	}

	GLItem::~GLItem() {

	}

	GLItemNotInitializedException::GLItemNotInitializedException(
			const GLItem *item) : 
			std::runtime_error("GL Item not initialized") {
		this->item = item;
	}

	const char* GLItemNotInitializedException::what() const throw() {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << " at address " << this->item;
		return oss.str().c_str();
	}

	GLItemAlreadyInitializedException::GLItemAlreadyInitializedException(
			const GLItem *item) : 
			std::runtime_error("GL Item already initialized") {
		this->item = item;
	}

	const char* GLItemAlreadyInitializedException::what() const throw() {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << " at address " << this->item;
		return oss.str().c_str();
	}
} }
