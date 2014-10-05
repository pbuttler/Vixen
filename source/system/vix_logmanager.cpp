#include <vix_logmanager.h>
#include <vix_osutil.h>

namespace Vixen {

	namespace System {

		template<>
		LogManager* Singleton<LogManager>::_data = nullptr;

		std::string LogManager::_LogDirectory = "";

		void LogManager::CreateLog(const std::string& name,
			                       bool noFile)
		{
			LogManager* manager = instancePtr();
			if (manager) {

				std::string log_path = _LogDirectory + name;

				Log* log = new Log(log_path, noFile);
				if (log)
					manager->m_logs.insert(LogList::value_type(log_path, log));
			}
		}

		void LogManager::SetLogDirectory(const std::string& dir)
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