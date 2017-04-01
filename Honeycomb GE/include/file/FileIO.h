#pragma once
#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>

#include "LineOperation.h"

namespace Honeycomb { namespace File {
	/// Reads in the image from the specified file path into an unsigned char
	/// array. If the file does not exist, NULL will be returned instead. The
	/// data array will be dynamically allocated and should therefore be
	/// deleted after being used.
	/// const string &img : The path of the image which is to be read in.
	/// int &w : The reference for where to store the width of the image.
	/// int &h : The reference for where to store the height of the image.
	/// const bool &err : Should a warning be logged to the Honeycomb Logger if
	///					  an error occurs?
	/// return : The pointer to the contents of the file, or a nullptr if the
	///			 file cannot be read in.
	unsigned char* readImageToUChar(const std::string &img, int &w, int &h,
			const bool &err = true);
	
	/// Reads in the file from the specified file path and returns a pointer to
	/// its contents. The contents are dynamically allocated and should be
	/// deleted after being used. If the file was not found, a nullptr is
	/// returned instead.
	/// const string &file : The path to the file which is to be read in.
	/// return : The pointer to the contents of the file.
	std::string* readFileToStr(const std::string &file);

	/// Reads in the file from the specified file path and returns a pointer to
	/// its contents. As each line is read in, the line is passed to the line
	/// operator argument to be processed. The contents of the return variable 
	/// are dynamically allocated and should be deleted after being used. If 
	/// the file was not found, a nullptr is  returned instead.
	/// const string &file : The path to the file which is to be read in.
	/// LineOperation &lnOp : The instance of the line operation which is to be
	///						  called for each line.
	/// return : The pointer to the contents of the file.
	std::string* readFileToStr(const std::string &file, const LineOperation 
        &lnOp);
} }

#endif
