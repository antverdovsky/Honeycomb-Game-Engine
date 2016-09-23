#include "..\..\include\file\FileIO.h"

#include <iostream>
#include <fstream>
#include <string>

namespace Honeycomb::File {
	std::string readFileToStr(std::string file) {
		// Variable to store the content and a stream to read it in
		std::string content = "";
		std::ifstream ifs(file);

		if (ifs) { // If the file has been found and is good -> Read in
			// Read in line by line, adding the new line character at the end
			// of each line to go on to the next.
			std::string curLine = "";
			while (std::getline(ifs, curLine)) content += curLine + '\n';
		}
		
		// Close stream & return the code (or empty if it couldn't be read).
		ifs.close();
		return content;
	}
}