#pragma once
#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <string>

namespace Honeycomb::Graphics {
	class Texture2D {
	public:
		/// Generates an empty texture from OpenGL.
		Texture2D();

		/// Generates a texture using the specified image file, using GL_RGB
		/// for both the internal and external format. The filtering of the 
		/// texture will be set to GL_NEAREST for minifying and magnifying. The
		/// wrap of the texture will be set to GL_REPEAT for both S, and T 
		/// coordinates. Mip Maps will also be generated for the texture.
		Texture2D(std::string file);

		/// Destroys this texture from OpenGL.
		~Texture2D();

		/// Binds this texture to OpenGL.
		void bind();

		/// Generates a MipMap for the texture.
		void genMipMap();

		/// Gets the image data from the specified image file and passes it to
		/// OpenGL, using the GL_RGB formats.
		/// string file : The file path to the image file.
		void setImageData(std::string file);

		/// Gets the image data from the specified image file and passes it to
		/// OpenGL, using the specified internal and external formats.
		/// string file : The file path to the image file.
		/// int inForm : The internal format with which to store the image.
		/// int exForm : The external format with which the data is passed in.
		void setImageData(std::string file, int inForm, int exForm);

		/// Passes the specified image data to OpenGL.
		/// unsigned char *data : The image data to be sent to OpenGL.
		/// int inForm : The internal format with which to store the image.
		/// int exForm : The external format with which the data is passed in.
		/// int w : The width of the image.
		/// int h : The height of the image.
		void setImageData(unsigned char *data, int inForm, int exForm,
			int w, int h);

		/// Sets the texture filtering for minifying and magnifying operations.
		/// int min : The filtering for the texture when minifying.
		/// int mag : The filtering for the texture when magnifying.
		void setTextureFiltering(int min, int mag);

		/// Sets the texture wrapping on the s and t coordinate axes.
		/// int s : The wrapping for the texture on the s coordinate axis.
		/// int t : The wrapping for the texture on the t coordinate axis.
		void setTextureWrap(int s, int t);

		/// Unbinds this (and any other) texture from OpenGL.
		static void unbind();
	private:
		int textureID; // The texture "pointer"
	};
}

#endif