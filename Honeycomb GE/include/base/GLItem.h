#pragma once
#ifndef GL_ITEM_H
#define GL_ITEM_H

namespace Honeycomb::Base {
	class GLItem {
	public:
		/// Returns the boolean representation of the initialization of this
		/// OpenGL item.
		/// return : True if this item has been initialized; false otherwise.
		const bool& getIsInitialized() const;

		/// Initializes this item and returns true, if this item has not yet
		/// been initialized. Otherwise, false is returned.
		/// return : True if initialized is false; false otherwise.
		virtual bool initialize();

		/// Destroys this item from OpenGL. Note that if any other instance is
		/// using this item, undefined behavior may occur. Initialized will be
		/// set to false, allowing the reinitializing of this item, though it
		/// is not guaranteed to be the same as it was before.
		virtual void destroy();
	protected:
		bool isInitialized; // Has this OpenGL Item been initialized?

		/// Instantiates a new OpenGL Item. Note that the initialize() method
		/// is not called by this constructor.
		GLItem();

		/// Deinstantiates this OpenGL Item. Note that the destroy() method is
		/// not by this destructor.
		virtual ~GLItem();
	};
}

#endif