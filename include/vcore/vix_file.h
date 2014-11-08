#ifndef VIX_FILE_H
#define VIX_FILE_H

#include <vix_platform.h>
#include <vix_stringutil.h>

namespace Vixen {

	/*
	* Retrieves extension for file.
	* @param file
	* Path or Name of file
	* @param wd 
	* Flag determines if user wants (.) included in extension
	*/
	VIX_API std::string	getFileExtension(const std::string& file, bool wd = true);

}


#endif