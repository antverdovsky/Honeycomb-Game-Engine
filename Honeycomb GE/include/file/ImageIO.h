#pragma once
#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <string>
#include <stdexcept>
#include <memory>

namespace Honeycomb { namespace File {
	/// <summary>
	/// Class which is used to load in images using the SOIL library.
	/// </summary>
	class ImageIO {
	public:
		/// <summary>
		/// Loads in the image from the specified directory. If the image could
		/// not be loaded, an ImageIOLoadException is thrown. The image should
		/// be a BMP, PNG, JPG, TGA, DDS, PSD, or HDR image (see SOIL library
		/// for details).
		/// </summary>
		/// <param name="dir">
		/// The directory from which the image is to be loaded.
		/// </param>
		ImageIO(const std::string &dir);

		/// <summary>
		/// Returns the data of the image, loaded in through the SOIL library.
		/// </summary>
		/// <returns>
		/// The pointer to the data of the image.
		/// </returns>
		const unsigned char* getData() const;

		/// <summary>
		/// Returns the directory from which the image was loaded.
		/// </summary>
		/// <returns>
		/// The directory string.
		/// </returns>
		const std::string& getDirectory() const;

		/// <summary>
		/// Returns the width of the image (read only).
		/// </summary>
		/// <returns>
		/// The width of the image, as an integer.
		/// </returns>
		const int& getWidth() const;

		/// <summary>
		/// Returns the height of the image (read only).
		/// </summary>
		/// <returns>
		/// The height of the image, as an integer.
		/// </returns>
		const int& getHeight() const;
	private:
		/// <summary>
		/// Deletes the specified image data from memory.
		/// </summary>
		static void deleteImage(unsigned char *data);

		/// <summary>
		/// Loads the image from the specified directory and returns its raw
		/// unsigned char pixel data. The width and height parameters also have
		/// the width and height of the image written to them. If the image
		/// could not be loaded, an ImageIOLoadException is thrown.
		/// </summary>
		/// <param name="dir">
		/// The directory of the image on the disk.
		/// </param>
		/// <param name="width">
		/// The integer reference to which the width of the image is to be
		/// written.
		/// </param>
		/// <param name="height">
		/// The integer reference to which the height of the image is to be
		/// written.
		/// </param>
		/// <exception cref="ImageIOLoadException">
		/// Thrown if the Image could not be loaded to due to some SOIL error.
		/// </exception>
		static unsigned char* loadImage(const std::string &dir,
				int &width, int &height);

		std::string directory;               // The file directory of the image

		int width;                           // The width of the image
		int height;                          // The height of the image
		
		std::unique_ptr<unsigned char, 
			decltype(&deleteImage)> data;    // The data of the image
	};

	/// <summary>
	/// Image IO Load Exception which is thrown when an image cannot be loaded.
	/// </summary>
	class ImageIOLoadException : std::runtime_error {
	public:
		/// <summary>
		/// Creates a new Image IO Load Exception.
		/// </summary>
		/// <param name="dir">
		/// The file directory from which the image could not be loaded.
		/// </param>
		/// <param name="soil">
		/// The SOIL last result string.
		/// </param>
		ImageIOLoadException(const std::string &dir, const std::string &soil);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info containing the
		/// directory of the image which could not be loaded and the error
		/// returned by the SOIL library.
		/// </returns>
		virtual const char* what() const throw();
	private:
		std::string directory;              // Directory of failed ImageIO
		std::string soilError;              // Error returned by SOIL
	};
} }

#endif