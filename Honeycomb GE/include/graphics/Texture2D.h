#pragma once
#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <string>

#include "../base/GLItem.h"
#include "../file/ImageIO.h"

namespace Honeycomb { namespace Graphics {
	class Texture2D : public Honeycomb::Base::GLItem {
	public:
		/// Creates an empty Texture instance.
		Texture2D();

		/// Binds this texture to OpenGL at GL_TEXTURE0.
		void bind() const;

		/// Binds this texture to OpenGL at the specified location. 
		/// const int &loc : The location of the texture in memory. This is
		///					 treated as the displacement from GL_TEXTURE0.
		void bind(const int &loc) const;

		/// Generates a MipMap for the texture.
		void genMipMap();

		/// Returns the directory of this 2D Texture.
		/// return : The system directory.
		const std::string& getDirectory() const;

		/// Returns the texture ID of this 2D Texture.
		/// return : The Texture ID.
		const int& getTextureID() const;

		/// Initializes this 2D Texture instance by generating the appropriate
		/// texture buffer to store the texture data.
		void initialize();
		
		/// Destroys this 2D Texture instance by destroying the appropriate
		/// texture buffer.
		void destroy();

		/// Creates a 1x1 pixel of the specified color and sets it data to this
		/// Texture's data.
		/// const int &r : The red component of the color [0, 255].
		/// const int &g : The green component of the color [0, 255].
		/// const int &b : The blue component of the color [0, 255].
		void setImageData(const int &r = 255, const int &g = 255,
			const int &b = 255);

		/// <summary>
		/// Sets this texture data to the data of the specified IO image. If
		/// the image has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown. If this image has already had its data
		/// set, the previous data will be lost and replaced with the new image
		/// data.
		/// </summary>
		/// <param name="image">
		/// The image which is to be stored in this Texture.
		/// </param>
		void setImageData(const Honeycomb::File::ImageIO &image);

		/// Passes the specified image data to OpenGL.
		/// unsigned char *data : The image data to be sent to OpenGL.
		/// const int &type : The type of data being passed in.
		/// const int &in : The internal format with which to store the image.
		/// const int &ex : The external format of the data passed in.
		/// const int &w : The width of the image.
		/// const int &h : The height of the image.
		void setImageData(const unsigned char *data, const int &type, 
			const int &in, const int &ex, const int &w, const int &h);

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
		int textureID; // The texture "pointer"
		std::string directory; // The file from which the texture was loaded
	};
} }

#endif
