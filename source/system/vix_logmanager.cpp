#include <vix_logmanager.h>
#include <vix_osutil.h>

namespace Vixen {

	namespace System {

		void Logger::DebugLog(const std::string& msg, LogPriority priority, bool debugOut)
		{
			if (LogManager::HasDefaultLog()) {
				Log* default = LogManager::DefaultLog();

				default->logMessage(msg, priority, debugOut);
			}
			else {
				LogManager::SetDefaultLog("untitled");
				Log* default = LogManager::DefaultLog();
				if (default)
					default->logMessage(msg, priority, debugOut);
			}
		}

		void Logger::DebugLog(const std::string& name, const std::string& msg, LogPriority priority, bool debugOut)
		{
			if (name.empty()) //must have name for new log file
				return;

			LogManager& manager = LogManager::instance();
			if (!LogManager::LogExists(name)) {
				LogManager::CreateLog(name, LLF_NORMAL, false);
				Log* log = LogManager::GrabLog(name);
				if (log)
					log->logMessage(msg, priority, debugOut);
			}
			else {
				Log* log = LogManager::GrabLog(name);
				if (log)
					log->logMessage(msg, priority, debugOut);
			}
		}



		std::string LogManager::_LogDirectory = "";
		std::string LogManager::_LogExtension = ".log";

		bool LogManager::HasDefaultLog()
		{
			LogManager& manager = instance();

			return manager.m_default != nullptr;
		}
		
		bool LogManager::LogExists(const std::string& name)
		{
			LogManager& manager = instance();
			
			LogList::iterator it = manager.m_logs.find(name);
			if (it != manager.m_logs.end())
				return true;
			else
				return false;
		}

		Log* LogManager::GrabLog(const std::string& name)
		{
			LogManager& manager = instance();
			
			LogList::iterator it = manager.m_logs.find(name);
			if (it != manager.m_logs.end()) 
				return it->second;
			
			return nullptr;
		}

		Log* LogManager::DefaultLog()
		{
			LogManager& manager = instance();
			
			if (manager.m_default)
				return manager.m_default;
			else 
				return nullptr;
		}

		void LogManager::SetDefaultLog(const std::string& name)
		{
			LogManager& manager = instance();
				
			LogList::iterator it = manager.m_logs.find(name);
			if (it != manager.m_logs.end()) {
				manager.m_default = it->second;
			}
			else {
				//log doesn't already exist so we need to create a new one
				CreateLog(name, LLF_NORMAL, false);
				manager.m_default = manager.m_logs[name];
			}
			
		}

		void LogManager::CreateLog(const std::string& name,
								   LogFrequency freq,
			                       bool  noFile)
		{
			LogManager& manager = instance();
			
			//create path
			std::string log_path = _LogDirectory + name + _LogExtension;

			Log* log = new Log(log_path, freq, noFile);
			if (log)
				manager.m_logs.insert(LogList::value_type(name, log));
			
		}

		void LogManager::SetLogDirectory(const std::string& dir)
		{
			using namespace Util;

			if (os_isdir(dir)) {
				_LogDirectory = dir;
			}
			else {
				os_mkdir(dir);
				_LogDirectory = dir;
			}
		}

	}

}