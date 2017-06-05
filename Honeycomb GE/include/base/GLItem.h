#pragma once
#ifndef GL_ITEM_H
#define GL_ITEM_H

#include <stdexcept>

namespace Honeycomb { namespace Base {
	class GLItem {
	public:
		/// <summary>
		/// Returns the boolean representation of the initialization of this
		/// OpenGL item.
		/// </summary>
		/// <returns>
		/// True if this item has been initialized; false otherwise.
		/// </returns>
		const bool& getIsInitialized() const;

		/// <summary>
		/// Attempts to initialize this item to OpenGL. If this item is already
		/// initialized, a GLItemAlreadyInitializedException is thrown.
		/// </summary>
		/// <exception cref="GLItemAlreadyInitializedException">
		/// If the item is already initialized when the method is called.
		/// </exception>
		virtual void initialize();

		/// <summary>
		/// Destroys this item from OpenGL. If this item was being used by some
		/// other class when it was destroyed, undefined behavior will occur.
		/// </summary>
		virtual void destroy();
	protected:
		bool isInitialized; // Has this OpenGL Item been initialized?

		/// <summary>
		/// Instantiates a new OpenGL Item. Note that the 
		/// <see cref="initialize"/> method is not called by this constructor
		/// and must be called manually after the constructor.
		/// </summary>
		GLItem();

		/// <summary>
		/// Destroys this OpenGL Item. Note that the <see cref="destroy"/>
		/// method is not called by this destructor and must be called manually
		/// before the destructor.
		/// </summary>
		virtual ~GLItem();
	};

	/// <summary>
	/// Exception which is to be thrown when a GLItem is already initialized,
	/// but a method is invoked to reinitialize it.
	/// </summary>
	class GLItemAlreadyInitializedException : public std::runtime_error {
	public:
		/// <summary>
		/// Creates a new already initialized exception with the specified
		/// OpenGL item.
		/// </summary>
		/// <param name="item">
		/// The item for which the exception was created.
		/// </param>
		GLItemAlreadyInitializedException(const GLItem *item);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info.
		/// </returns>
		virtual const char* what() const throw();
	private:
		const GLItem *item;
	};

	/// <summary>
	/// Exception which is to be thrown when a GLItem is used without being
	/// initialized first.
	/// </summary>
	class GLItemNotInitializedException : public std::runtime_error {
	public:
		/// <summary>
		/// Creates a new not initialized exception with the specified OpenGL
		/// item.
		/// </summary>
		/// <param name="item">
		/// The item for which the exception was created.
		/// </param>
		GLItemNotInitializedException(const GLItem *item);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info.
		/// </returns>
		virtual const char* what() const throw();
	private:
		const GLItem *item;
	};
} }

#endif