#include <vix_log.h>
#include <vix_debugutil.h>

#include <chrono>

namespace Vixen {

	namespace System {

		Log::Log(const std::string& name, LogFrequency freq, bool noFile, bool timeStamp)
			: m_name(name),
			  m_timeStamp(timeStamp),
			  m_freq(freq),
			  m_noFile(noFile)
		{
			if (!m_noFile) {
				m_log.open(name);
			}
		}

		Log::~Log()
		{
			if (!m_noFile)
				m_log.close();
		}

		void Log::logMessage(const std::string& msg, LogPriority lp, bool outDebug)
		{
			using namespace Vixen::Util;

			if (msg.empty()) //don't record null messages
				return;

			if (lp + m_freq < LOG_THRESHOLD)
				return; //only record messages that meet threshold level

			std::stringstream output;
			if (m_timeStamp) {

				output << "TIME STAMP: " << vixDebugTimeStamp();
			}
			output << msg << "\n\n";

			if (outDebug)
				vixOutputDebugString(output.str());

			if (m_log.is_open())
				m_log << output.str();

		}
	}
}