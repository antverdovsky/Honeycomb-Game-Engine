#pragma once
#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <string>

namespace Honeycomb::Graphics {
	class Texture2D {
	public:
		/// Creates an empty Texture instance.
		Texture2D();

		/// Binds this texture to OpenGL.
		void bind() const;

		/// Destroys this 2D texture from OpenGL. This method should only be
		/// called when any copies of this texture are no longer being used.
		void destroy();

		/// Generates a MipMap for the texture.
		void genMipMap();

		/// Initializes this 2D Texture using the specified file directory. If
		/// the file string is empty, this texture will be instead initialized
		/// to a 1x1 white RGBA bitmap (default "non-texture).
		/// const string &file : The file with which to initialize the texture,
		///						 or empty for non-texture.
		///	return : True if this texture was successfully initialized. False,
		///			 otherwise.
		bool initialize(const std::string &file = "");

		/// Gets the image data from the specified image file and passes it to
		/// OpenGL, using the GL_RGB formats.
		/// const string &file : The file path to the image file.
		void setImageData(const std::string &file);

		/// Gets the image data from the specified image file and passes it to
		/// OpenGL, using the specified internal and external formats.
		/// const string &file : The file path to the image file.
		/// const int &in : The internal format with which to store the image.
		/// const int &ex : The external format of the data passed in.
		void setImageData(const std::string &file, const int &in, 
			const int &ex);

		/// Passes the specified image data to OpenGL.
		/// unsigned char *data : The image data to be sent to OpenGL.
		/// const int &in : The internal format with which to store the image.
		/// const int &ex : The external format of the data passed in.
		/// const int &w : The width of the image.
		/// const int &h : The height of the image.
		void setImageData(unsigned char *data, const int &in, const int &ex,
			const int &w, const int &h);

		/// Sets the texture filtering for minifying and magnifying operations.
		/// const int &min : The filtering when minifying.
		/// const int &mag : The filtering when magnifying.
		void setTextureFiltering(const int &min, const int &mag);

		/// Sets the texture wrapping on the s and t coordinate axes.
		/// const int &s : The wrapping on the s coordinate axis.
		/// const int &t : The wrapping on the t coordinate axis.
		void setTextureWrap(const int &s, const int &t);

		/// Unbinds this (and any other) texture from OpenGL.
		static void unbind();
	private:
		bool isInitialized; // Has the texture been initialized?
		
		int textureID; // The texture "pointer"
		std::string directory; // The file from which the texture was loaded
	};
}

#endif