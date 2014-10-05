#ifndef VIX_LOG_H
#define VIX_LOG_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <vix_stringutil.h>
#include <fstream>

namespace Vixen {

	namespace System {

		class Logger;


		enum LogFrequency
		{
			LL_LOW = 1,
			LL_NORMAL = 2,
			LL_HIGH = 3
		};

		enum LogPriority
		{
			LP_TRIVIAL = 1,
			LP_STANDARD = 2,
			LP_CRITICAL = 3
		};

		class VIX_API Log
		{
		protected:
			std::ofstream  m_log;
			LogFrequency   m_freq;
			bool           m_debugOut;
			bool           m_noFile;
			bool           m_timeStamp;
			std::string    m_name;

		public:
			Log(const std::string& name, bool noFile);

			void logMessage(const std::string& message,
				            LogPriority lp,
							bool outDebug = false);

			static const size_t LOG_THRESHOLD = 4;
		};

	}
}

#endif