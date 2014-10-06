#ifndef VIX_LOG_MANAGER_H
#define VIX_LOG_MANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_log.h>
#include <map>

namespace Vixen {

	namespace System {

		class VIX_API Logger
		{
		public:
			static void DebugLog(const std::string& msg, LogPriority priority, bool debugOut = false);
		};

		class VIX_API LogManager : public Singleton < LogManager >
		{
			typedef std::map<std::string, Log*> LogList;

			static std::string  _LogDirectory;
		public:

			static Log*        DefaultLog();
			static void        CreateLog(const std::string& name, LogFrequency freq, bool noFile);
			static void        SetDefaultLog(const std::string& name);
			static void        SetLogDirectory(const std::string& path);
			static bool        HasDefaultLog();
			static LogManager* instancePtr();
			static LogManager& instance();
		protected:
			LogList   m_logs;
			Log*      m_default;
		};

	}
}

#endif