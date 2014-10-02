#ifndef VIX_CONFIG_H
#define VIX_CONFIG_H

#include <vix_platform.h>
#include <string>

namespace Vixen {

	namespace System {

		class VIX_API Config
		{
			enum class PLATFORM {
				UNKNOWN,
				WINDOWS,
				LINUX,
				MAC
			};

			std::string  m_title;
			size_t       m_clientW;
			size_t       m_clientH;
			bool         m_fullscreen;
			PLATFORM     m_platform;
			std::string  m_platformName;
		public:
			Config();

			void setTitle(const std::string& title);
			void setClientW(size_t width);
			void setClientH(size_t height);
			void setFullscreen(bool fullscreen);
			void setPlatformName(const std::string& name);
			void setPlatform(PLATFORM platform);

			const std::string& title()      const;
			size_t             clientW()    const;
			size_t             clientH()    const;
			bool               fullscreen() const;
			const std::string& platform()   const;

			static Config		fromFile(const std::string& path);
			static PLATFORM	    fromPlatformString(const std::string& platform);
		};

	}
}

#endif