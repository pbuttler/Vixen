#include <vix_log.h>
#include <vix_debugutil.h>

namespace Vixen {

	namespace System {

		Log::Log(const std::string& name, bool noFile)
			: m_name(name),
			  m_noFile(noFile)
		{
			if (!m_noFile) {
				m_log.open(name);
			}
		}
	}
}