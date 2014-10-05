#include <vix_logmanager.h>
#include <vix_osutil.h>

namespace Vixen {

	namespace System {

		template<>
		LogManager* Singleton<LogManager>::_data = nullptr;

		std::string LogManager::_LogDirectory = "";

		void LogManager::setLogDirectory(const std::string& dir)
		{
			using namespace Util;
			
			if (os_isdir(dir)) {
				_LogDirectory = dir;
			}
		}

		LogManager& LogManager::instance()
		{
			return Singleton<LogManager>::instance();
		}

		LogManager* LogManager::instancePtr()
		{
			return Singleton<LogManager>::instancePtr();
		}

	}

}