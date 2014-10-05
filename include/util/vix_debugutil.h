#ifndef VIX_DEBUG_UTIL_H
#define VIX_DEBUG_UTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>

namespace Vixen {

	namespace System {

		inline void vixOutputDebugString(const std::string& msg)
		{
			if (msg.empty()) return;

#ifdef VIX_SYS_WINDOWS
				OutputDebugString((WCHAR*)msg.c_str());
#else
			std::cerr << msg << std::endl;
#endif
		}

	}
}

#endif