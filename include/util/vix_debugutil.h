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

#ifndef VIX_SFY_FUNC
#define VIX_SFY_FUNC VIX_SFY_(__FUNCTION__)
#endif

#ifndef VIX_SFY_LINE
#define VIX_SFY_LINE VIX_SFY_(__LINE__)
#endif
#ifndef VIX_SFY_FILE
#define VIX_SFY_FILE VIX_SFY_(__FILE__)
#endif

#ifndef VIX_LOG_FILE
#define VIX_LOG_FILE "FILE: " VIX_SFY_FILE
#endif
#ifndef VIX_LOG_LINE
#define VIX_LOG_LINE "LINE: " VIX_SFY_LINE
#endif

#ifndef VIX_LOG_FUNC
#define VIX_LOG_FUNC "FUNC: " __FUNCTION__
#endif

#ifndef VIX_LOG_PREFIX
#define VIX_LOG_PREFIX VIX_LOG_FILE "\n" VIX_LOG_FUNC "\n" VIX_LOG_LINE "\n"
#endif
#ifndef VIX_LOG_STRING(x)
#define VIX_LOG_STRING(x) VIX_LOG_PREFIX x
#endif

namespace Vixen {

	namespace Util {

		VIX_API void        vixOutputDebugString(const std::string& msg);
		VIX_API std::string vixDebugTimeStamp();
		
	}
}

#endif