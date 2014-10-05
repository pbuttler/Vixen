#ifndef VIX_LOG_MANAGER_H
#define VIX_LOG_MANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_log.h>
#include <map>

namespace Vixen {

	namespace System {

		class VIX_API LogManager : public Singleton < LogManager >
		{
			typedef std::map<std::string, Log*> LogList;

			static std::string  _LogDirectory;
		public:

			static void        CreateLog(const std::string& name, bool noFile);
			static void        SetLogDirectory(const std::string& path);
			static LogManager* instancePtr();
			static LogManager& instance();
		protected:
			LogList   m_logs;
			Log*      m_default;
		};

	}
}

#endif