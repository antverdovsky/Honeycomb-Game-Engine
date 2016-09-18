#include "..\..\include\io\FileIO.h";

#include <iostream>
#include <fstream>
#include <string>

std::string FileIO::readFileToStr(std::string file) {
	// Create the variable to store the content and the stream to read it in
	std::string content = "";
	std::ifstream ifs(file, std::ios::in);

	// If the file has been found and is good -> Read in; Otherwise, report
	// that the file is unreadable.
	if (ifs.good()) {
		// Read in line by line, adding the new line character at the end
		// of each line to go on to the next.
		std::string curLine = "";
		while (std::getline(ifs, curLine)) content += curLine + '\n';
	}
	else {
#if _DEBUG
		std::cout << "UNABLE TO READ FILE: " << file << std::endl;
#endif
	}

	// Close stream & return the code (or empty if it couldn't be read).
	ifs.close();
	return content;
}