#ifndef VIX_SDLWINDOW_H
#define VIX_SDLWINDOW_H

#include <vix_platform.h>
#include <vix_gamewindow.h>
#include <SDL.h>

namespace Vixen {

	enum class SDL_GW_Flags
	{
		SDL_GW_FULLSCREEN,
		SDL_GW_FULLSCREEN_DESKTOP,
		SDL_GW_OPENGL,
		SDL_GW_HIDDEN,
		SDL_GW_BORDERLESS,
		SDL_GW_RESIZEABLE,
		SDL_GW_MINIMIZED,
		SDL_GW_INPUT_GRABBED,
		SDL_GW_ALLOW_HIGHDPI
	};

	struct VIX_API SDL_GW_Params
	{
		UString title;
		int x;
		int y;
		int width;
		int height;
		Uint32 flags;
	};

	class VIX_API SDLGameWindow : public IGameWindow
	{
	public:
		SDLGameWindow(const SDL_GW_Params& params);

		~SDLGameWindow();

		ErrCode             VInit()                                override;
		ErrCode             VRun()                                 override;
		void                VSetVisible(bool flag)                 override;
		void                VSetFullscreen(bool flag)              override;
		void                VSwapBuffers()                         override;
		const UString&      VGetTitle()                            override;
		const Rect&         VGetClientBounds()                     override;
		bool                VIsRunning()                           override;
		bool                VIsHidden()                            override;
		bool                VIsPaused()                            override;
		void                VClose()                               override;

	private:
		UString       m_title;
		bool          m_hidden;
		bool          m_running;
		bool          m_paused;
		Rect          m_clientRect;
		SDL_Window*   m_windowHandle;
		SDL_GLContext m_context;
		SDL_GW_Params m_params;
	};

}

#endif