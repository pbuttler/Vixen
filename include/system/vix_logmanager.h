#ifndef VIX_LOG_MANAGER_H
#define VIX_LOG_MANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>

namespace Vixen {

	namespace System {

		class VIX_API LogManager : public Singleton < LogManager >
		{
			static std::string  _LogDirectory;
		public:


			static void        setLogDirectory(const std::string& path);
			static LogManager* instancePtr();
			static LogManager& instance();
		};

	}
}

#endif