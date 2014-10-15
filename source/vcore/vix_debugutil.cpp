#include <vix_debugutil.h>

namespace Vixen {

	std::string DebugTimeStamp()
	{
		using namespace std::chrono;
		std::stringstream ss;

		system_clock::time_point now_point = system_clock::now();
		std::time_t now_time = system_clock::to_time_t(now_point);
		tm pTime;

#ifdef VIX_SYS_WINDOWS
		localtime_s(&pTime, &now_time);
		char buffer[VIX_BUFSIZE];
		asctime_s(buffer, &pTime);
#else
		ss << asctime(localtime(&pTime));
#endif
		ss << buffer;
		return ss.str();
	}
}