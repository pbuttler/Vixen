#include <vix_logmanager.h>

namespace Vixen {

	namespace System {

		template<>
		LogManager* Singleton<LogManager>::_data = nullptr;

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