#include "..\..\include\file\FileIO.h"

#include <SOIL.h>

#include <iostream>
#include <fstream>
#include <string>

#include "..\..\include\debug\Logger.h"

using Honeycomb::Debug::Logger;

namespace Honeycomb::File {
	unsigned char* readImageToUChar(const std::string &img, int &w, int &h) {
		// Use the SOIL library to load in the image and return its data
		return SOIL_load_image(img.c_str(), &w, &h, 0, SOIL_LOAD_AUTO);
	}

	std::string* readFileToStr(const std::string &file) {
		// Read the file to string with no line modifications (empty vector).
		return readFileToStr(file, std::vector<lineOperatorFunc>());
	}

	std::string* readFileToStr(const std::string &file, 
			const std::vector<lineOperatorFunc> &lnFs) {
		// Variable to store the content and a stream to read it in
		std::string *content = new std::string();
		std::ifstream ifs(file);

		if (!ifs) { // If not found -> Print error and return.
			Logger::getLogger().logError(__FUNCTION__, __LINE__,
				"Unable to read in file contents from " + file + "!");

			return nullptr;
		}

		std::string line = ""; // The current line which was read in
		while (std::getline(ifs, line)) {
			// Call the line operation functions passed in, allowing them to
			// modify or process the line as they wish.
			for (int i = 0; i < lnFs.size(); i++)
				(*lnFs.at(i))(line, file);

			// Append the final result to the content
			content->append(line + '\n');
		}

		// Close stream & return the contents
		ifs.close();
		return content;
	}
}