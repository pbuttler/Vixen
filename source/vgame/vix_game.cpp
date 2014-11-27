#include <vix_game.h>
#include <vix_sdlwindow.h>
#include <vix_debugutil.h>

namespace Vixen {

	Game::Game()
	{
		m_config = new GameConfig(VTEXT("D:\\devenv\\vixenv\\test.config"));
		m_window = new SDLGameWindow(m_config->WindowArgs());
	}

	int Game::run()
	{
		/*if application window exists*/
		if (m_window) {
			ErrCode error = m_window->VRun();
			if (CheckError(error)) {
				DebugPrintF(VTEXT("Application loop encountered error: %s\n"),
					ErrCodeString(error));
				return -1;
			}
		}

		return 0;
	}
	
}