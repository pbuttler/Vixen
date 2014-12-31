/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_game.h>
#include <vix_sdlwindow.h>
#include <vix_debugutil.h>
#include <vix_audiomanager.h>
#include <vix_contentmanager.h>
#include <vix_luascriptmanager.h>

namespace Vixen {

	AudioManager&     g_AudioManager   = AudioManager::instance();
	ContentManager&   g_ContentManager = ContentManager::instance();
	LuaScriptManager& g_ScriptManager = LuaScriptManager::instance();

	Game::Game()
	{
		m_config = new GameConfig(VTEXT("D:\\devenv\\vixenv\\test.config"));
		m_window = new SDLGameWindow(m_config->WindowArgs());
	}

	int Game::run()
	{
		/*if application window exists*/
		if (m_window) {
			g_AudioManager.VStartUp();
			g_ContentManager.VStartUp();
			g_ScriptManager.VStartUp();
			ErrCode error = m_window->VRun();
			g_AudioManager.VShutDown();
			g_ContentManager.VShutDown();
			g_ScriptManager.VShutDown();
			if (CheckError(error)) {
				DebugPrintF(VTEXT("Application loop encountered error: %s\n"),
					ErrCodeString(error));
				return -1;
			}
		}

		return 0;
	}
	
}