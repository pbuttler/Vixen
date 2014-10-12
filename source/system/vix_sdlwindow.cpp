#include <vix_sdlwindow.h>

namespace Vixen {

	SDL_GameWindow::SDL_GameWindow()
	{
		m_WindowTitle = "Hello, World";
	}

	SDL_GameWindow::~SDL_GameWindow()
	{

	}

	ErrCode SDL_GameWindow::VInit()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			//of course, we should also Log this
			return ErrCode::ERR_SDL_INIT;
		}

		//create and initialize the window handle
		m_WindowHandle = SDL_CreateWindow(m_WindowTitle.c_str(),
										  SDL_WINDOWPOS_CENTERED, //force centered (for now..)
										  SDL_WINDOWPOS_CENTERED, //force centered (for now..)
										  DEF_WINDOW_WIDTH,
										  DEF_WINDOW_HEIGHT,
										  SDL_WINDOW_OPENGL |
										  SDL_WINDOW_RESIZABLE);
		if (!m_WindowHandle) {
			SDL_Quit(); //shut down SDL
			return ErrCode::ERR_SDL_INIT;
		}

		//create and initialize the opengl context
		m_GLContext = SDL_GL_CreateContext(m_WindowHandle);
		if (!m_GLContext) {
			SDL_Quit();
			return ErrCode::ERR_SDL_INIT;
		}

		
		//everything succeeded
		return ErrCode::ERR_SUCCESS; 
	}

	void SDL_GameWindow::VSetFullscreen(bool flag, bool keepResolution)
	{
		if (!m_WindowHandle) //should log message
			return;

		//if set fullscreen true
		if (flag) {
			if (keepResolution)
				SDL_SetWindowFullscreen(m_WindowHandle, SDL_WINDOW_FULLSCREEN);
			else 
				SDL_SetWindowFullscreen(m_WindowHandle, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		//we will change it back to windowed, with original resolution
		else {
			SDL_SetWindowFullscreen(m_WindowHandle, NULL);
		}
	}

	void SDL_GameWindow::VSetVisible(bool flag)
	{
		if (!m_WindowHandle)
			return;

		if (flag) {
			if (m_IsHidden)
				SDL_ShowWindow(m_WindowHandle);
		}
		else {
			if (!m_IsHidden)
				SDL_HideWindow(m_WindowHandle);
		}
			
	}

	void SDL_GameWindow::VSwapBuffers()
	{
		if (!m_WindowHandle) //obv, log error message
			return;

		//swap buffers on OpenGL window for double buffering.
		//NOTE:
		//
		//	We assume double buffering is available, as all current
		//  hardware, including integrated chipsets support this
		//
		SDL_GL_SwapWindow(m_WindowHandle);
	}

	const std::string& SDL_GameWindow::VGetTitle()
	{
		if (m_WindowHandle) {
			const char* title = SDL_GetWindowTitle(m_WindowHandle);
			if (title)
				m_WindowTitle = std::string(title);
			else
				m_WindowTitle = std::string("");
		}

		return m_WindowTitle;
	}

	const Rect& SDL_GameWindow::VGetClientBounds()
	{
		if (m_WindowHandle) {
			SDL_GetWindowPosition(m_WindowHandle,
				&m_ClientBounds.x,
				&m_ClientBounds.y);
			SDL_GetWindowSize(m_WindowHandle,
				&m_ClientBounds.width,
				&m_ClientBounds.height);
		}

		return m_ClientBounds;
	}

}