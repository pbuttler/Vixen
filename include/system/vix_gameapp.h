#ifndef VIX_GAME_APP_H
#define VIX_GAME_APP_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <vix_sdlwindow.h>
#include <vix_logmanager.h>
#include <vix_eventmanager.h>

namespace Vixen {

	class VIX_API GameApplication : public IApplication
	{
	public:
		GameApplication(const std::string& configPath);

		ErrCode  VInit() override;
	    int      VRun()  override;

	private:
		IGameWindow*  m_window;
		bool          m_running;
	};
}

#endif