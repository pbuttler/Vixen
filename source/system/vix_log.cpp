#include <vix_log.h>
#include <vix_debugutil.h>

#include <chrono>

namespace Vixen {

	namespace System {

		Log::Log(const std::string& name, bool noFile, bool timeStamp)
			: m_name(name),
			  m_timeStamp(timeStamp),
			  m_noFile(noFile)
		{
			if (!m_noFile) {
				m_log.open(name);
			}
		}

		void Log::logMessage(const std::string& msg, LogPriority lp, bool outDebug)
		{
			if (msg.empty()) //don't record null messages
				return;

			if (lp + m_freq < LOG_THRESHOLD)
				return; //only record messages that meet threshold level

			std::stringstream output;
			if (m_timeStamp) {

				output << vixDebugTimeStamp() << "    : ";
			}
			output << msg << "\n";

			if (outDebug)
				vixOutputDebugString(output.str());

			if (!m_noFile) {
				m_log << output.str();
			}

		}
	}
}