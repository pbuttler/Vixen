#include <vix_gameapp.h>

namespace Vixen {

	GameApplication::GameApplication(const std::string& configPath)
	{
		//NOTE:
		//
		//	Here is where configuration loading code would generally go,
		//  for application level configuration settings. Other settings,
		//  for other subsystems will be handled in their own init startup
		//  functions
		//
	}

	ErrCode GameApplication::VInit()
	{
		ErrCode err = ErrCode::ERR_SUCCESS;

		//initialize log system
		g_LogManager.VStartUp();

		//try and create window
		m_window = new SDL_GameWindow;
		err = m_window->VInit();
		if (!CheckError(err))
			return ErrCode::ERR_FAILURE;

		//initialize event system
		//initialize resource system
		//initialize render system
	
		return err;
	}

	int GameApplication::VRun()
	{
		m_running = true;
		while (m_running)
		{
			//poll events from event manager
			//Example:
			// 
			// g_EventManager->Poll();
			//
			//
			//    within this poll function, subsystems such as the input
			//    manager, will be updated from the event hook that corresponds
			//    to the type of window system we are currently using
			//	  e.g SDL_GameWindow, Win32_GameWindow, etc. etc.
			//
			//    This is a synchronous implementation, so it is possible for
			//    hanging cpu cycles to occur during polling.
			//
			

			//For now...just use the SDL poll event
			SDL_Event event;
			bool visible = true;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					m_running = false;
					break;

				case SDL_MOUSEBUTTONDOWN:
					visible = !visible;
					m_window->VSetVisible(visible);
					break;
				}
			}

		}

		//shutdown subsystems
		g_LogManager.VShutDown();

		return EXIT_SUCCESS;
	}
}