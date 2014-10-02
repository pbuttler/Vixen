#ifndef VIX_GAME_H
#define VIX_GAME_H

//vixen incl.
#include <vix_platform.h>
#include <vix_interfaces.h>
#include <vix_config.h>

//other incl.
#include <string>

namespace Vixen {

	namespace System {

		class VIX_API Game
		{
		public:

			static const size_t DEFAULT_CLIENTW = 800;
			static const size_t DEFAULT_CLIENTH = 600;

			Game(const std::string& configPath);

			Game(const Config& config);

			virtual ~Game();

			//main application loop
			int run();

		protected:
			virtual bool init() = 0;
			virtual void update(float delta) = 0; //eventually will take Timer obj
			virtual void render(float delta) = 0; //eventually will take Timer obj

		private:
			std::string      m_title;
			size_t           m_clientH;
			size_t           m_clientW;
			bool             m_running;
			Config           m_config;

			IApplication*    m_app;
		};

	}
}



#endif