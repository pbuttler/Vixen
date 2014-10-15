#ifndef VIX_STRINGUTIL_H
#define VIX_STRINGUTIL_H

#include <vix_platform.h>
#include <string>
#include <sstream>

#ifndef VIX_BUFSIZE
#define VIX_BUFSIZE 1024
#endif

namespace Vixen {

		VIX_API void str_replaceAll(std::string& input,
			                        const std::string& from, 
			                        const std::string& to);
}



#endif