#pragma once
#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>

namespace Honeycomb::File {
	/// Reads in the image from the specified file path into an unsigned char
	/// array. If the file does not exist, NULL will be returned instead. The
	/// data array will be dynamically allocated and should therefore be
	/// deleted after being used.
	/// const string &img : The path of the image which is to be read in.
	/// int &w : The reference for where to store the width of the image.
	/// int &h : The reference for where to store the height of the image.
	/// return : The pointer to the contents of the file.
	unsigned char* readImageToUChar(const std::string &img, int &w, int &h);
	
	/// Reads in the file from the specified file path and returns a pointer to
	/// its contents. The contents are dynamically allocated and should be
	/// deleted after being used. If the file was not found, a nullptr is
	/// returned instead.
	/// const std::string &file : The path to the file which is to be read in.
	/// return : The pointer to the contents of the file.
	std::string* readFileToStr(const std::string &file);
}

#endif