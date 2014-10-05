#include <vix_log.h>

namespace Vixen {

	namespace System {

		LoggerPtr Logger::m_instance;

		Logger* Logger::Instance()
		{
			if (!m_instance)
				m_instance = std::make_unique<Logger>();

			return m_instance.get();
		}



	}
}