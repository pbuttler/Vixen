#ifndef VIX_SDL_WINDOW_H
#define VIX_SDL_WINDOW_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <vix_stringutil.h>
#include <vix_rect.h>
#include <SDL.h>

namespace Vixen {

	enum class SDL_GW_Flags
	{
		SDL_GW_CENTERED,
	};

	struct VIX_API SDL_GWParams
	{
		const char* title;
		int         x;
		int         y;
		int         w;
		int         h;
		Uint32      flags;
	};

	class VIX_API SDL_GameWindow : public IGameWindow
	{
	public:
		SDL_GameWindow();

		~SDL_GameWindow();

		//VIRTUAL OVERRIDES
		ErrCode             VInit()                                override;
		void                VSetVisible(bool flag)                 override;
		void                VSetFullscreen(bool flag, 
			                               bool keep_res = false)  override;
		void                VSwapBuffers()                         override;
		const std::string&  VGetTitle()                            override;
		const Rect&         VGetClientBounds()                     override;

	private:
		std::string   m_WindowTitle;
		bool          m_IsHidden;
		Rect          m_ClientBounds;
		SDL_Window*   m_WindowHandle;
		SDL_GLContext m_GLContext;
	};
}

#endif