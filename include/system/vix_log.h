#ifndef VIX_LOG_H
#define VIX_LOG_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <memory>

namespace Vixen {

	namespace System {

		class Logger;

		typedef std::unique_ptr<Logger> LoggerPtr;

		class VIX_API Logger : INonCopyable
		{
			static LoggerPtr m_instance;
		public:
			static Logger* Instance();

			static void    Log();
		};

	}
}

#endif