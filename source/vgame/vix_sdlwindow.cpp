#include <vix_sdlwindow.h>
#include <vix_debugutil.h>

namespace Vixen {

	SDLGameWindow::SDLGameWindow()
	{

	}

	SDLGameWindow::~SDLGameWindow()
	{

	}

	ErrCode SDLGameWindow::VInit()
	{
		/* Initialize SDL
		*/
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			DebugPrintF(VTEXT("SDL Failed to Initialize: %s\n"),
				        ErrCodeString(ErrCode::ERR_SDL_INIT_FAIL));
			return ErrCode::ERR_SDL_INIT_FAIL;
		}

		/*Create the SDL_Window handle*/
		return ErrCode::ERR_SUCCESS;
	}

	void SDLGameWindow::VSetFullscreen(bool flag)
	{
		
	}

	void SDLGameWindow::VSetVisible(bool flag)
	{
		

	}

	void SDLGameWindow::VSwapBuffers()
	{
		

	
	}

	const UString& SDLGameWindow::VGetTitle()
	{
		return VTEXT("");
	}

	const Rect& SDLGameWindow::VGetClientBounds()
	{
		return Rect();
	}

}