#pragma once
#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <string>
#include <unordered_map>

#define MAX_NUM_TEXTURES 64

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

		/// Copy Constructor for the Texture.
		Texture2D(const Texture2D &tex);

		/// Destroys this texture from OpenGL.
		~Texture2D();

		/// Binds this texture to OpenGL.
		void bind() const;

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

		Texture2D& operator=(const Texture2D &tex);
	private:
		// The non-texture (2x2 white texture which is used when a material
		// does not have a texture).
		static Texture2D *nonTexture;

		// The counter for how many Texture2D instances exist for some texture
		// pointer. NOTE: counter[0] refers to texture pointer 1, counter[1]
		// refers to 2, etc.
		static int instanceCount[MAX_NUM_TEXTURES];

		// HashMap linking the directory of a texture to its ID.
		static std::unordered_map<std::string, int> dirToID;

		int textureID; // The texture "pointer"
		std::string directory; // The file from which the texture was loaded

		/// Returns a pointer to the Non-Texture Texture.
		/// return : The Non-Texture Texture.
		static Texture2D* getNonTexture();

		/// Returns the texture ID of the texture with the specified directory,
		/// or a negative one if it does not exist.
		/// string dir : The directory of the texture.
		/// return : The OpenGL texture ID.
		static int textureIdFromDirectory(std::string dir);
	};
}

#endif