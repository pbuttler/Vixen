#ifndef VIX_DEBUG_UTIL_H
#define VIX_DEBUG_UTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <chrono>
#include <ctime>

namespace Vixen {

	namespace System {





		inline void vixOutputDebugString(const std::string& msg)
		{
			if (msg.empty()) return;

#ifdef VIX_SYS_WINDOWS
				OutputDebugStringA(msg.c_str());
#else
			std::cerr << msg << std::endl;
#endif
		}

		inline std::string vixDebugTimeStamp()
		{
			using namespace std::chrono;
			std::stringstream ss;

			high_resolution_clock::time_point now_point = high_resolution_clock::now();
			milliseconds ms = duration_cast<milliseconds>(now_point.time_since_epoch());
			std::time_t  t = ms.count();

			ss << t;

			return ss.str();
		}

	}
}

#endif