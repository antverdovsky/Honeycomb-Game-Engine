#pragma once
#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>

namespace Honeycomb::File {
	/// Reads in the file from the specified file path and returns its contents
	/// as a string. If the file does not exist, an empty string ("") will be
	/// returned instead.
	/// std::string file : The path to the file which is to be read in.
	/// return : The contents of the file.
	std::string readFileToStr(std::string file);
}

#endif