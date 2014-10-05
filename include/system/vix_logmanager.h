#ifndef VIX_LOG_MANAGER_H
#define VIX_LOG_MANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>

namespace Vixen {

	namespace System {

		class VIX_API LogManager : public Singleton < LogManager >
		{
		public:


			static LogManager* instancePtr();
			static LogManager& instance();
		};

	}
}

#endif