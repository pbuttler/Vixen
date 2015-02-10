#ifndef VIX_SDLCONSOLE_H
#define VIX_SDLCONSOLE_H

#include <vix_platform.h>
#include <vix_console.h>

namespace Vixen {

	class VIX_API SDLConsole : public IConsole
	{
	public:
		SDLConsole();

		~SDLConsole();

		UString Buffer();
		void	Write(const char* text, size_t len);
		void	Erase(size_t len);

	private:

	};
}

#endif
