#ifndef VIX_STRINGUTIL_H
#define VIX_STRINGUTIL_H

#include <vix_platform.h>
#include <string>

namespace Vixen {

	namespace Util {

		VIX_API void str_replaceAll(std::string& input, const std::string& from, const std::string& to);
	}
}



#endif