#pragma once
#ifndef LINE_OPERATION_H
#define LINE_OPERATION_H

#include <string>

namespace Honeycomb { namespace File {
	class LineOperation {
	public:
		/// Function which should be overriden to perform some sort of
		/// operation on the line argument. This function will be called for
		/// each line which the FileIO method reads in from some file.
		/// const string &file : The directory of the file which is being read 
		///						 in.
		/// string &line : The line of the file which is to be modified by this
		///				   line operation method.
		virtual void lineOperation(const std::string &file, std::string &line) 
            const;
	};
} }

#endif
