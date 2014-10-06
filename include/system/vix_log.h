#ifndef VIX_LOG_H
#define VIX_LOG_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <vix_stringutil.h>
#include <vix_debugutil.h>
#include <fstream>

namespace Vixen {

	namespace System {

		class Logger;


		enum LogFrequency
		{
			LLF_LOW = 1,
			LLF_NORMAL = 2,
			LLF_HIGH = 3
		};

		enum LogPriority
		{
			LLP_TRIVIAL = 1,
			LLP_STANDARD = 2,
			LLP_CRITICAL = 3
		};

		class VIX_API Log
		{
		protected:
			std::ofstream  m_log;
			LogFrequency   m_freq;
			bool           m_noFile;
			bool           m_timeStamp;
			std::string    m_name;

		public:
			Log(const std::string& name, 
				LogFrequency freq = LLF_NORMAL, 
				bool noFile = false,
				bool timeStamp = true);
			~Log();

			void logMessage(const std::string& message,
				            LogPriority lp,
							bool outDebug = false);

			static const int LOG_THRESHOLD = 4;
		};

	}
}

#endif