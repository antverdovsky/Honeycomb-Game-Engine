#include "../../include/file/ImageIO.h"

#include <SOIL.h>
#include <sstream>

namespace Honeycomb { namespace File {
	ImageIO::ImageIO(const std::string &dir) : 
			data(loadImage(dir, this->width, this->height), deleteImage) {
		
	}

	const unsigned char* ImageIO::getData() const {
		return this->data.get();
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

	void ImageIO::deleteImage(unsigned char *data) {
		if (data == nullptr) return;

		SOIL_free_image_data(data);
	}

	unsigned char* ImageIO::loadImage(const std::string &dir, 
			int &width, int &height) {
		unsigned char *raw = SOIL_load_image(
			dir.c_str(), &width, &height, 0, SOIL_LOAD_AUTO);

		if (raw == nullptr)
			throw ImageIOLoadException(dir, SOIL_last_result());

		return raw;
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