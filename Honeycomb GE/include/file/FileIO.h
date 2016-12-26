#pragma once
#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>

namespace Honeycomb::File {
	typedef void(*lineOperatorFunc)(std::string&, const std::string&);

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
	/// const string &file : The path to the file which is to be read in.
	/// return : The pointer to the contents of the file.
	std::string* readFileToStr(const std::string &file);

	/// Reads in the file from the specified file path and returns a pointer to
	/// its contents. As each line is read in, the line is passed to all of the
	/// line functions, after which the line is appended to the file contents.
	/// Do note that the line passed to the line functions may have been
	/// modified by previous line functions, therefore order matters. The 
	/// contents of the return variable are dynamically allocated and should be
	/// deleted after being used. If the file was not found, a nullptr is 
	/// returned instead.
	/// const string &file : The path to the file which is to be read in.
	/// const vector<lineOperatorFunc> &lnFs : 
	///		The functions which are to be called per each line in the file. The
	///		first argument is the line currently being processed, and the
	///		second argument is the directory of the file currently being
	///		processed.
	/// return : The pointer to the contents of the file.
	std::string* readFileToStr(const std::string &file,
			const std::vector<lineOperatorFunc> &lnFs);
}

#endif