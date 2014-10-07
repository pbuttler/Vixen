#include <vix_SDL2application.h>
#include <vix_logmanager.h>

namespace Vixen {

	namespace System {

		SDLApplication::SDLApplication(const SDLSettings& settings)
			: m_initialized(false)
		{
			

			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
				
				return;
			}
			
			Config config = settings.config;
			int    flags = settings.flags;
			m_window = SDL_CreateWindow(config.title().c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				config.clientW(),
				config.clientH(),
				flags);

			if (!m_window) {
				//eventually this will be written out to logger
				printf("Failed to create window: %s\n", SDL_GetError());
				SDL_Quit();
				return;
			}

			m_context = SDL_GL_CreateContext(m_window);
			if (!m_context) {
				//eventually this will be written out to logger
				printf("Failed to create context: %s\n", SDL_GetError());
				SDL_Quit();
				return;
			}

			m_initialized = true;
		}

		SDLApplication::~SDLApplication()
		{
			SDL_GL_DeleteContext(m_context);

			SDL_Quit();
		}

		bool SDLApplication::initialized()
		{
			return m_initialized;
		}

		int SDLApplication::run()
		{
			//some basic timing, should be done in Timer class
			int prevTime = 0;
			int curTime = 0;
			float deltaTime = 0.0f;

			m_running = true;
			while (m_running) {

				curTime = SDL_GetTicks();
				deltaTime = (float)(curTime - prevTime);
				prevTime = curTime;

				//basic event polling, should be more robust to handle
				//input managers
				SDL_Event event;
				while (SDL_PollEvent(&event)) {

					switch (event.type)
					{
					case SDL_QUIT:
						m_running = false;
						break;
					}
				}

				SDL_GL_SwapWindow(m_window);
			}
			
			return EXIT_SUCCESS;
		}

	}
}