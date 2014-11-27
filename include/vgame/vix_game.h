#ifndef VIX_GAME_H
#define VIX_GAME_H

#include <vix_platform.h>
#include <vix_gamewindow.h>
#include <vix_gameconfig.h>

namespace Vixen {

	class VIX_API Game
	{
	public:
		Game();

		int run();

	private:
		GameConfig*  m_config;
		IGameWindow* m_window;
	};

}

#endif