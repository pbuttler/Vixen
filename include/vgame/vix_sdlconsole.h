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

		bool    IsActive();
		void    Toggle();
		void    Show();
		void    Hide();
		UString Buffer();
		void	Write(const char* text, size_t len);
		void	Erase(size_t len);
		void    Render(IRenderer* renderer, int x, int y);
		void    SetFont(BMFont* font);
		void    SetTexture(Texture* tex);

	};
}

#endif
