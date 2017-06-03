#include "../../include/file/ImageIO.h"

#include <SOIL.h>
#include <sstream>

namespace Honeycomb { namespace File {
	ImageIO::ImageIO(const std::string &dir) {
		// Read in the image from the file directory
		this->directory = dir;
		this->data = SOIL_load_image(
			dir.c_str(), &(this->width), &(this->height), 0, SOIL_LOAD_AUTO);

		// If the data is null, an error occured, throw an ImageIOLoadException
		if (this->data == nullptr) 
			throw ImageIOLoadException(this->directory, SOIL_last_result());
	}

	void ImageIO::cleanup() {
		if (this->data == nullptr) return;

		SOIL_free_image_data(this->data);
		this->data = nullptr;
	}

	const unsigned char* ImageIO::getData() const {
		return this->data;
	}

	const std::string& ImageIO::getDirectory() const {
		return this->directory;
	}

	const int& ImageIO::getWidth() const {
		return this->width;
	}

	const int& ImageIO::getHeight() const {
		return this->height;
	}

	ImageIOLoadException::ImageIOLoadException(const std::string &dir, 
			const std::string &soil) : 
			std::runtime_error("Failed to Load Image") {
		this->directory = dir;
		this->soilError = soil;
	}

	const char* ImageIOLoadException::what() const throw() {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << " from directory " << 
				this->directory << " | " << this->soilError;
		return oss.str().c_str();
	}
} }