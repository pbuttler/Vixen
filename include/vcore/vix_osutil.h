#ifndef VIX_OSUTIL_H
#define VIX_OSUTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>



namespace Vixen {

	static const char WIN_PATH_DELIM = '\\';
	static const char UNIX_PATH_DELIM = '/';

	VIX_API void        os_mkdir(const std::string& dir);
	VIX_API bool        os_isdir(const std::string& dir);
	VIX_API	std::string os_path(const std::string& path);
	VIX_API std::string os_dir(const std::string& path, bool wt = true);
}


#endif