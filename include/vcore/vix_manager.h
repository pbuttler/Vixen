#ifndef VIX_MANAGER_H
#define VIX_MANAGER_H

#include <vix_platform.h>
#include <vix_errglobals.h>

namespace Vixen {

	class VIX_API IManager
	{
	public:
		virtual ErrCode VStartUp()  = 0;
		virtual ErrCode VShutDown() = 0;
	};

}

#endif