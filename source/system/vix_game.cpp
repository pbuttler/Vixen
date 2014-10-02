#include <vix_game.h>
#include <vix_gl.h>
#include <stdio.h>

#include <vix_SDL2application.h>


namespace Vixen {

	namespace System {

		Game::Game(const std::string& configPath)
		{
			m_config = Config::fromFile(configPath);
			m_title  = m_config.title();
			m_clientW = m_config.clientW();
			m_clientH = m_config.clientH();

#ifdef _DEBUG
			//output config
			printf("Config: \n");
			printf("\t [PLATFORM] \t%s\n", m_config.platform().c_str());
			printf("\t [TITLE] \t%s\n", m_config.title().c_str());
			printf("\t [CLIENTW] \t%i\n", m_config.clientW());
			printf("\t [CLIENTH] \t%i\n", m_config.clientH());
#endif
		}

		Game::Game(const Config& config)
			: m_config(config)
		{
			m_title = config.title();
			m_clientW = config.clientW();
			m_clientH = config.clientH();

#ifdef _DEBUG
			//output config
			printf("Config: \n");
			printf("\t%s\n", m_config.platform().c_str());
			printf("\t%s\n", m_config.title().c_str());
			printf("\t%i\n", m_config.clientW());
			printf("\t%i\n", m_config.clientH());
#endif
		}

		Game::~Game()
		{
			delete m_app;
		}

		int Game::run()
		{
			SDLSettings settings;
			settings.config = m_config;
			settings.flags = SDL_WINDOW_OPENGL;
			m_app = new SDLApplication(settings);
			if (!m_app || !m_app->initialized())
				return EXIT_FAILURE;

			GLenum err = glewInit();
			if (err != GLEW_OK) {
				printf("GLEW Error: %s\n", glewGetErrorString(err));
				
				return EXIT_FAILURE;
			}

			if (!init()) {
				printf("Error occured during init, exiting...\n");
				return EXIT_FAILURE;
			}

			return m_app->run();
		}
	}
}