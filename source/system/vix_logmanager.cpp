#include <vix_logmanager.h>
#include <vix_osutil.h>

namespace Vixen {

	namespace System {

		void Logger::DebugLog(const std::string& msg, LogPriority priority, bool debugOut)
		{
			LogManager* manager = LogManager::instancePtr();
			if (manager) {
				if (LogManager::HasDefaultLog()) {
					Log* default = LogManager::DefaultLog();

					default->logMessage(msg, priority, debugOut);
				}
				else {
					LogManager::SetDefaultLog("untitled");
					Log* default = LogManager::DefaultLog();
					default->logMessage(msg, priority, debugOut);
				}
			}
		}

		template<>
		LogManager* Singleton<LogManager>::_data = nullptr;

		std::string LogManager::_LogDirectory = "";

		bool LogManager::HasDefaultLog()
		{
			LogManager* manager = instancePtr();
			if (manager) {
				return manager->m_default != nullptr;
			}
			else
				return false;
		}

		Log* LogManager::DefaultLog()
		{
			LogManager* manager = instancePtr();
			if (manager) {
				return manager->m_default;
			}
			return nullptr;
		}

		void LogManager::SetDefaultLog(const std::string& name)
		{
			LogManager* manager = instancePtr();
			if (manager) {
				
				LogList::iterator it = manager->m_logs.find(name);
				if (it != manager->m_logs.end()) {
					manager->m_default = it->second;
				}
				else {
					//log doesn't already exist so we need to create a new one
					CreateLog(name, LLF_NORMAL, false);
					manager->m_default = manager->m_logs[name];
				}
			}
		}

		void LogManager::CreateLog(const std::string& name,
								   LogFrequency freq,
			                       bool  noFile)
		{
			LogManager* manager = instancePtr();
			if (manager) {

				std::string log_path = _LogDirectory + name;

				Log* log = new Log(log_path, freq, noFile);
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