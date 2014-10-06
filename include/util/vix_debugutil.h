#ifndef VIX_DEBUG_UTIL_H
#define VIX_DEBUG_UTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <iostream>
#include <iomanip>
#include <chrono>

#ifdef VIX_SYS_WINDOWS
#include <time.h>
#endif
#include <ctime>

#ifndef VIX_STRINGIFY(x)
#define VIX_STRINGIFY(x) #x
#endif

#ifndef VIX_SFY_(x)
#define VIX_SFY_(x) VIX_STRINGIFY(x)
#endif

#ifndef VIX_SFY_LINE
#define VIX_SFY_LINE VIX_SFY_(__LINE__)
#endif
#ifndef VIX_SFY_FILE
#define VIX_SFY_FILE VIX_SFY_(__FILE__)
#endif

namespace Vixen {

	namespace Util {

		VIX_API void        vixOutputDebugString(const std::string& msg);
		VIX_API std::string vixDebugTimeStamp();
		
	}
}

#endif