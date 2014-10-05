#include <vix_config.h>
#include <vix_game.h>
#include <vix_osutil.h>
#include <tinyxml2.h>



namespace Vixen {

	namespace System {

		

		Config::Config()
			: m_title(""),
			  m_clientW(Game::DEFAULT_CLIENTW),
			  m_clientH(Game::DEFAULT_CLIENTH),
			  m_fullscreen(false)

		{
			
		}

		void Config::setTitle(const std::string& title)
		{
			m_title = title;
		}

		void Config::setClientW(size_t clientW)
		{
			m_clientW = clientW;
		}

		void Config::setClientH(size_t clientH)
		{
			m_clientH = clientH;
		}

		void Config::setFullscreen(bool fullscreen)
		{
			m_fullscreen = fullscreen;
		}

		void Config::setPlatform(PLATFORM platform)
		{
			m_platform = platform;
		}

		void Config::setPlatformName(const std::string& name)
		{
			m_platformName = name;
		}

		const std::string& Config::title() const
		{
			return m_title;
		}

		size_t Config::clientW() const
		{
			return m_clientW;
		}

		size_t Config::clientH() const
		{
			return m_clientH;
		}

		bool Config::fullscreen() const
		{
			return m_fullscreen;
		}

		const std::string& Config::platform() const
		{
			return m_platformName;
		}

		Config::PLATFORM Config::fromPlatformString(const std::string& platform)
		{
			if (platform == "WINDOWS")
				return PLATFORM::WINDOWS;
			else if (platform == "LINUX")
				return PLATFORM::LINUX;
			else if (platform == "MAC")
				return PLATFORM::MAC;
			else 
				return PLATFORM::UNKNOWN;
		}

		Config Config::fromFile(const std::string& path)
		{
			using namespace Vixen::Util;
			

			Config config;
			
			//load xml config file
			tinyxml2::XMLDocument doc;
			tinyxml2::XMLError    error = doc.LoadFile(os_path(path).c_str());
			if (error != tinyxml2::XML_NO_ERROR) {
				//output debug that config file failed to load
				printf("Config file: %s failed to load", path.c_str());
				return config;
			}
			
			//now read data from config
			tinyxml2::XMLElement* game = doc.FirstChildElement("game");
			//read platform
			tinyxml2::XMLElement* platform = game->FirstChildElement("platform");
			config.setPlatformName(platform->Attribute("title"));
			config.setPlatform(Config::fromPlatformString(platform->Attribute("title")));
			//read settings
			tinyxml2::XMLElement* settings = game->FirstChildElement("settings");
			config.setTitle(settings->Attribute("title"));
			config.setClientW(settings->IntAttribute("clientW"));
			config.setClientH(settings->IntAttribute("clientH"));
			config.setFullscreen(settings->BoolAttribute("fullscreen"));

			return config;
		}

	}
}