#ifndef VIX_EVENT_MANAGER_H
#define VIX_EVENT_MANAGER_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <vix_singleton.h>

namespace Vixen {

	class VIX_API EventManager : public Singleton < EventManager >, IManager
	{
		friend class Singleton < EventManager > ;
	public:



		//VIRTUAL OVERRIDES
		void VStartUp()  override;
		void VShutDown() override;
	};

}

#endif