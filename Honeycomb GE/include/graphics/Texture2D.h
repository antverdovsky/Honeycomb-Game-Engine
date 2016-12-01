#pragma once
#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <string>

namespace Honeycomb::Graphics {
	class Texture2D {
	public:
		/// Generates a texture using the specified image file, using GL_RGB
		/// for both the internal and external format. The filtering of the 
		/// texture will be set to GL_NEAREST for minifying and magnifying. The
		/// wrap of the texture will be set to GL_REPEAT for both S, and T 
		/// coordinates. Mip Maps will also be generated for the texture.
		/// const std::string &file : The file from which to load the texture.
		Texture2D(const std::string &file);

		/// Destroys this texture from OpenGL.
		~Texture2D();

		/// Binds this texture to OpenGL.
		void bind() const;

		/// Generates a MipMap for the texture.
		void genMipMap();

		/// Returns a constant reference to the non-texture. The non-texture
		/// is a 2 x 2 sized white texture which should be used instead of a
		/// nullptr if some material does not have a texture.
		/// return : The constant reference to the non-texture.
		static const Texture2D& getNonTexture();

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
		// The non-texture (2x2 white texture which is used when a material
		// does not have a texture).
		static Texture2D *nonTexture;
		
		int textureID; // The texture "pointer"
		std::string directory; // The file from which the texture was loaded
	};
}

#endif