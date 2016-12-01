#include "..\..\include\file\FileIO.h"

#include <SOIL.h>

#include <iostream>
#include <fstream>
#include <string>

namespace Honeycomb::File {
	unsigned char* readImageToUChar(const std::string &img, int &w, int &h) {
		// Use the SOIL library to load in the image and return its data
		return SOIL_load_image(img.c_str(), &w, &h, 0, SOIL_LOAD_AUTO);
	}

	std::string* readFileToStr(const std::string &file) {
		// Variable to store the content and a stream to read it in
		std::string *content = new std::string();
		std::ifstream ifs(file);

		if (ifs) { // If the file has been found and is good -> Read in
			// Read in line by line, adding the new line character at the end
			// of each line to go on to the next.
			std::string curLine = "";
			while (std::getline(ifs, curLine)) content->append(curLine + '\n');
		}
		
		// Close stream & return the code (or empty if it couldn't be read).
		ifs.close();
		return content;
	}
}