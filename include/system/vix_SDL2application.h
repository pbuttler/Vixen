#ifndef VIX_SDL2APPLICATION_H
#define VIX_SDL2APPLICATION_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <vix_config.h>

#include <SDL.h>

namespace Vixen {

	namespace System {

		struct VIX_API SDLSettings
		{
			Config config;
			int    flags;
		};

		class VIX_API SDLApplication : public IApplication
		{
		public:
			SDLApplication(const SDLSettings& settings);
			~SDLApplication();

			bool initialized() override;
			int  run()		   override;

		private:
			SDL_Window*    m_window;
			SDL_GLContext  m_context;
			bool           m_initialized;
			bool           m_running;
		};
	}
}

#endif