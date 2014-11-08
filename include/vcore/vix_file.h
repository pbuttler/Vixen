#ifndef VIX_FILE_H
#define VIX_FILE_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_osutil.h>

namespace Vixen {

	/*
	* Retrieves extension for file.
	* @param filePath
	* Path or Name of file
	* @param wd 
	* Flag determines if user wants (.) included in extension
	*/
	VIX_API std::string	getFileExtension(const std::string& filePath, bool wd = true);

	/*
	* Retrieves filename with extension.
	* @param filePath
	* Path of file
	*/
	VIX_API std::string getFileName(const std::string& filePath);

}


#endif