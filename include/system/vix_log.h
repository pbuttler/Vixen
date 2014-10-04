#ifndef VIX_LOG_H
#define VIX_LOG_H

#include <vix_platform.h>

namespace Vixen {

	namespace System {

		class VIX_API Logger
		{
			static Logger* m_instance;
		public:
			static Logger* Instance();
			static void    Log();
		};

	}
}

#endif