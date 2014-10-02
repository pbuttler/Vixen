#ifndef VIX_OSUTIL_H
#define VIX_OSUTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>

namespace Vixen {

	namespace Util {

		VIX_API	std::string os_path(const std::string& path);
		VIX_API std::string os_dir(const std::string& path, bool wt = true);
	}
}


#endif